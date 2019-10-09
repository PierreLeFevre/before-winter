#include "TileMap.h"
#include "FuncLib.h"
#include "DateTime.h"

#include "../SDL2/SDL_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void ConstructTileMap(TileMap* tm, Graphics* gfx, const int nTiles_x, const int nTiles_y, const int topleft_x, const int topleft_y, char* map_file, DateTime* dT){
    tm->gfx = gfx;
    tm->tiles = (Tile*) malloc(sizeof(Tile) * nTiles_x * nTiles_y);
    tm->nTiles_x = nTiles_x;
    tm->nTiles_y = nTiles_y;
    tm->topleft_x = topleft_x;
    tm->topleft_y = topleft_y;
    tm->map_file = map_file;
    
	FILE* fileIO = fopen(map_file, "rb");
	fseek(fileIO, 0L, SEEK_END);
	long int numbytes = ftell(fileIO);
	fseek(fileIO, 0L, SEEK_SET);
    char* mapData = malloc(numbytes + 1);
	fread(mapData, 1, numbytes, fileIO);
    mapData[numbytes] = 0;
    RemoveCharacterFromArray(mapData, '\r', numbytes);
    RemoveCharacterFromArray(mapData, '\n', numbytes);
    RemoveCharacterFromArray(mapData, ' ', numbytes);
    fclose(fileIO);

    for(int i = 0; i < tm->nTiles_x * tm->nTiles_y;){
        //Beginning of new Tile
        if(*mapData == ','){
            mapData++;
            i++;
            continue;
        }
        // '*' is terminator
        if(*mapData == '*'){
            break;
        }

        // ----------------------------------
        // ----- DEFAULT TILEPROPERTIES -----
        // ----------------------------------

        //Srcrect is full texture size
        SDL_Rect srcrect = {0,0,gfx->wWidth, gfx->wHeight};

        //Marks where the current tile is drawn
        SDL_Rect destrect = {
        tm->topleft_x + (int)(i % tm->nTiles_x) * TILE_WIDTH
        ,tm->topleft_y + (int)(i / tm->nTiles_x) * TILE_HEIGHT
        ,TILE_WIDTH
        ,TILE_HEIGHT
        };

        //Hitbox is the drawn texture
        SDL_Rect hitbox = destrect;

        //Row 1 = 10, Row 2 = 20....
        int z_index = (tm->topleft_y + (int)(i / tm->nTiles_x) * TILE_Z_INDEX_MAX);
        
        Drawable drawable;

        switch (dT->season)
        {
        case Spring:
            ConstructDrawable(&drawable, DT_Other, tm->gfx, SS_TILEMAP_SPRING, srcrect, destrect, z_index);
            break;
        case Summer:
            ConstructDrawable(&drawable, DT_Other, tm->gfx, SS_TILEMAP_SUMMER, srcrect, destrect, z_index);
            break;
        case Fall:
            ConstructDrawable(&drawable, DT_Other, tm->gfx, SS_TILEMAP_FALL, srcrect, destrect, z_index);
            break;
        default:
            ConstructDrawable(&drawable, DT_Other, tm->gfx, SS_TILEMAP_SPRING, srcrect, destrect, z_index);
            break;
        }

        // ----------------------------------
        
        TileProperties tp = GetTilePropertiesData(*mapData - '0');
        ApplyTileProperties(tm, &tp, &drawable, &hitbox);

        Tile t;
        //"If new Tile"
        if(*(mapData - 1) == ','){
            ConstructTile(&t);
            tm->tiles[i] = t;
        }
        else{
            t = tm->tiles[i];
        }
        TileAddSprite(&t, drawable, hitbox, z_index);
        tm->tiles[i] = t;

        //Initiate every Drawable in overlays-array
        for(int j = 0; j < tile_overlay_enumsize; j++){
            Drawable overlay;
            ConstructDrawable(&overlay, DT_Other, tm->gfx, SS_NONE, srcrect, destrect, t.drawables[0].z_index + 1);
            t.overlays[j] = overlay;
        }

        mapData++;
    }
    FixTileTransistions(tm);
}

void DestroyTileMap(TileMap* tm){
    free(tm->tiles);
    tm->tiles = NULL;
}


void FixTileTransistions(TileMap* tm){
    for(int i = tm->nTiles_x + 1; i < tm->nTiles_x * tm->nTiles_y - (tm->nTiles_x + 1); i++){   
        if(tm->tiles[i].drawables[0].type == DT_Dirt){
            if(tm->tiles[i-1].drawables[0].type == DT_Grass){
                DrawableChangeSpriteSheet(&tm->tiles[i].overlays[tile_overlay_left], SS_TILEMAP_SPRING);
            }
        }
    }
}


TileProperties GetTilePropertiesData(const MapDataConverter mdc){
    TileProperties tp;
     //--- Default ---
    tp.type = DT_Other;

    tp.destrect_offset.x = 0;
    tp.destrect_offset.y = 0;
    tp.drawable_x_correct = 0;
    tp.drawable_y_correct = 0;
    tp.destrect_offset.w = 0;
    tp.destrect_offset.h = 0;

    tp.srcrect.x = 0;
    tp.srcrect.y = 0;
    tp.srcrect.w = 10000;
    tp.srcrect.h = 10000;

    tp.hitbox_offset.x = 0;
    tp.hitbox_offset.y = 0;
    tp.hitbox_x_correct = 0;
    tp.hitbox_y_correct = 0;
    tp.hitbox_offset.w = 0;
    tp.hitbox_offset.h = 0;
    
    tp.z_index_offset = 0;
    //----------------
    switch(mdc){
        case DIRT:
            tp.type = DT_Dirt;
            tp.srcrect.x = 80;
            tp.srcrect.y = 400;
            tp.srcrect.w = 16;
            tp.srcrect.h = 16;
            break;
        case GRASS:
            tp.type = DT_Grass;
            tp.srcrect.x = 0;
            tp.srcrect.y = 112;
            tp.srcrect.w = 16;
            tp.srcrect.h = 16;
            break;
        case TREE:
            tp.destrect_offset.w += TILE_WIDTH * 2;
            tp.destrect_offset.h += TILE_HEIGHT * 4;
            tp.destrect_offset.x -= TILE_WIDTH;

            tp.hitbox_offset.w -= TILE_WIDTH * 2;
            tp.hitbox_offset.h -= TILE_HEIGHT * 4;
            tp.hitbox_offset.x += TILE_WIDTH;
            tp.z_index_offset += 90;

            tp.srcrect.x = 48;
            tp.srcrect.y = 0;
            tp.srcrect.w = 48;
            tp.srcrect.h = 96;
            break;
        case WATER_LAKE:
            tp.srcrect.x = 128;
            tp.srcrect.y = 208;
            tp.srcrect.w = 16;
            tp.srcrect.h = 16;
            break;
        case WATER_TOP:
            tp.srcrect.x = 144;
            tp.srcrect.y = 113;
            tp.srcrect.w = 16;
            tp.srcrect.h = 16;
            break;

        default:
            break;
    }
    //Because we inevitably draw from the top-left corner
    tp.drawable_y_correct -= tp.destrect_offset.h;
    tp.hitbox_y_correct -= tp.hitbox_offset.h;
    //--------------------------------------------------
    return tp;
}

void ApplyTileProperties(TileMap* tm, TileProperties* tp, Drawable* drawable, SDL_Rect* hitbox){
    drawable->type = tp->type;

    drawable->destrect.x += tp->drawable_x_correct + tp->destrect_offset.x;
    drawable->destrect.y += tp->drawable_y_correct + tp->destrect_offset.y;
    drawable->destrect.w += tp->destrect_offset.w;
    drawable->destrect.h += tp->destrect_offset.h;

    drawable->srcrect.x = tp->srcrect.x;
    drawable->srcrect.y = tp->srcrect.y;
    drawable->srcrect.w = tp->srcrect.w;
    drawable->srcrect.h = tp->srcrect.h;

    *hitbox = drawable->destrect;
    hitbox->x += tp->hitbox_x_correct + tp->hitbox_offset.x;
    hitbox->y += tp->hitbox_y_correct + tp->hitbox_offset.y;
    hitbox->w += tp->hitbox_offset.w;
    hitbox->h += tp->hitbox_offset.h;

    drawable->z_index += tp->z_index_offset + Map(tp->destrect_offset.y, 0, TILE_HEIGHT, 0, TILE_Z_INDEX_MAX); 
}