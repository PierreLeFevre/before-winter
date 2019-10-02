#include "TileMap.h"
#include "FuncLib.h"

#include "../SDL2/SDL_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void ConstructTileMap(TileMap* tm, Graphics* gfx, const int nTiles_x, const int nTiles_y, const int topleft_x, const int topleft_y, char* map_file){
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

        ////Row 1 = 10, Row 2 = 20....
        int z_index = (tm->topleft_y + (int)(i / tm->nTiles_x) * TILE_Z_INDEX_MAX);
        
        Drawable drawable;
        ConstructDrawable(&drawable, DT_Other, tm->gfx, SS_TILEMAP, srcrect, destrect, z_index);
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

        mapData++;
    }
}

void DestroyTileMap(TileMap* tm){
    free(tm->tiles);
    tm->tiles = NULL;
}

TileProperties GetTilePropertiesData(const MapDataConverter mdc){
    TileProperties tp;
     //--- Default ---
    tp.type = DT_Other;

    tp.drawable_x_offset = 0;
    tp.drawable_y_offset = 0;
    tp.drawable_x_correct = 0;
    tp.drawable_y_correct = 0;
    tp.drawable_width_offset = 0;
    tp.drawable_height_offset = 0;

    tp.drawable_srcrect_x = 0;
    tp.drawable_srcrect_y = 0;
    tp.drawable_srcrect_width = 10000;
    tp.drawable_srcrect_height = 10000;

    tp.hitbox_x_offset = 0;
    tp.hitbox_y_offset = 0;
    tp.hitbox_x_correct = 0;
    tp.hitbox_y_correct = 0;
    tp.hitbox_width_offset = 0;
    tp.hitbox_height_offset = 0;
    
    tp.z_index_offset = 0;
    //----------------
    switch(mdc){
        case MUD:
            tp.drawable_srcrect_x = 16;
            tp.drawable_srcrect_y = 112;
            tp.drawable_srcrect_width = 16;
            tp.drawable_srcrect_height = 16;
            break;
        case GRASS:
            tp.drawable_srcrect_x = 0;
            tp.drawable_srcrect_y = 112;
            tp.drawable_srcrect_width = 16;
            tp.drawable_srcrect_height = 16;
            break;
        case TREE:
            tp.drawable_height_offset += TILE_HEIGHT * 5;
            tp.drawable_width_offset += TILE_HEIGHT * 3;
            tp.drawable_x_offset -= TILE_HEIGHT;

            tp.hitbox_x_offset -= TILE_HEIGHT * 5;
            tp.hitbox_y_offset -= TILE_HEIGHT * 3;
            tp.z_index_offset += 90;
            break;
        default:
            break;
    }
    //Because we inevitably draw from the top-left corner
    tp.drawable_y_correct -= tp.drawable_height_offset;
    tp.hitbox_y_correct -= tp.hitbox_height_offset;
    //--------------------------------------------------
    return tp;
}

void ApplyTileProperties(TileMap* tm, TileProperties* tp, Drawable* drawable, SDL_Rect* hitbox){
    drawable->type = tp->type;

    drawable->destrect.x += tp->drawable_x_correct + tp->drawable_x_offset;
    drawable->destrect.y += tp->drawable_y_correct + tp->drawable_y_offset;
    drawable->destrect.w += tp->drawable_width_offset + tp->drawable_x_offset;
    drawable->destrect.h += tp->drawable_height_offset + tp->drawable_y_offset;

    drawable->srcrect.x = tp->drawable_srcrect_x;
    drawable->srcrect.y = tp->drawable_srcrect_y;
    drawable->srcrect.w = tp->drawable_srcrect_width;
    drawable->srcrect.h = tp->drawable_srcrect_height;

    *hitbox = drawable->destrect;
    hitbox->x += tp->hitbox_x_correct + tp->hitbox_x_offset;
    hitbox->y += tp->hitbox_y_correct + tp->hitbox_y_offset;
    hitbox->w += tp->hitbox_width_offset + tp->hitbox_x_offset;
    hitbox->h += tp->hitbox_height_offset + tp->hitbox_y_offset;

    drawable->z_index += tp->z_index_offset + Map(tp->drawable_y_offset, 0, TILE_HEIGHT, 0, TILE_Z_INDEX_MAX); 
}