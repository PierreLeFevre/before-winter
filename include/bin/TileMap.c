#include "TileMap.h"
#include "FuncLib.h"

#include "../SDL2/SDL_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void ConstructTileMap(TileMap* tm, Graphics* gfx, const int nTiles_x, const int nTiles_y, const int topleft_x, const int topleft_y, char* mapFile){
    tm->gfx = gfx;
    tm->tiles = (Tile*) malloc(sizeof(Tile) * nTiles_x * nTiles_y);
    tm->nTiles_x = nTiles_x;
    tm->nTiles_y = nTiles_y;
    tm->topleft_x = topleft_x;
    tm->topleft_y = topleft_y;
    tm->mapFile = mapFile;
    
	FILE* fileIO = fopen(mapFile, "rb");
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

        //Marks where the current tiles Drawable is drawn, DEFAULT
        SDL_Rect destrect = {
        tm->topleft_x + (int)(i % tm->nTiles_x) * TILE_WIDTH
        ,tm->topleft_y + (int)(i / tm->nTiles_x) * TILE_HEIGHT
        ,TILE_WIDTH
        ,TILE_HEIGHT
        };

        //Default srcrect, if not set
        SDL_Rect srcrect = {0,0,gfx->wWidth, gfx->wHeight};
        
        TileProperties tp = GetTilePropertiesData(*mapData - '0');
        Drawable d;
        SDL_Rect hitbox = destrect;
        ApplyTileProperties(tm, &tp, &d, &destrect, &srcrect, &hitbox, i);

        Tile t;
        //"If new Tile"
        if(*(mapData - 1) == ','){
            ConstructTile(&t);
            tm->tiles[i] = t;
        }
        else{
            t = tm->tiles[i];
        }
        TileAddDrawable(&t, d);
        DrawableSetSrcRect(&t.ds[t.currentDrawables - 1], srcrect);
        hitbox.h = 59;
        TileAddHitbox(&t, hitbox);
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
            tp.filePath = "include/assets/unpacked/maps/spring_outdoorsTileSheet.png";
            tp.drawable_srcrect_x = 16;
            tp.drawable_srcrect_y = 112;
            tp.drawable_srcrect_width = 16;
            tp.drawable_srcrect_height = 16;
            break;
        case GRASS:
            tp.filePath = "include/assets/unpacked/maps/spring_outdoorsTileSheet.png";
            tp.drawable_srcrect_x = 0;
            tp.drawable_srcrect_y = 112;
            tp.drawable_srcrect_width = 16;
            tp.drawable_srcrect_height = 16;
            break;
        case TREE:
            tp.filePath = "include/assets/unpacked/maps/spring_outdoorsTileSheet.png";
            tp.drawable_height_offset += TILE_HEIGHT * 5;
            tp.drawable_width_offset += TILE_HEIGHT * 3;
            tp.drawable_x_offset -= TILE_HEIGHT;

            tp.hitbox_x_offset -= TILE_HEIGHT * 5;
            tp.hitbox_y_offset -= TILE_HEIGHT * 3;
            tp.z_index_offset += 90;

            tp.drawable_srcrect_x = 48;
            tp.drawable_srcrect_y = 0;
            tp.drawable_srcrect_width = 48;
            tp.drawable_srcrect_height = 96;
            break;
        default:
            tp.filePath = "include/assets/Question_mark.jpg";
            break;
    }
    //Because we inevitably draw from the top-left corner
    tp.drawable_y_correct -= tp.drawable_height_offset;
    tp.hitbox_y_correct -= tp.hitbox_height_offset;
    //--------------------------------------------------
    return tp;
}

void ApplyTileProperties(TileMap* tm, TileProperties* tp, Drawable* d, SDL_Rect* destrect, SDL_Rect* srcrect, SDL_Rect* hitbox, int index){
    destrect->x += tp->drawable_x_correct + tp->drawable_x_offset;
    destrect->y += tp->drawable_y_correct + tp->drawable_y_offset;
    destrect->w += tp->drawable_width_offset + tp->drawable_x_offset;
    destrect->h += tp->drawable_height_offset + tp->drawable_y_offset;

    srcrect->x = tp->drawable_srcrect_x;
    srcrect->y = tp->drawable_srcrect_y;
    srcrect->w = tp->drawable_srcrect_width;
    srcrect->h = tp->drawable_srcrect_height;

    *hitbox = *destrect;
    hitbox->x += tp->hitbox_x_correct + tp->hitbox_x_offset;
    hitbox->y += tp->hitbox_y_correct + tp->hitbox_y_offset;
    hitbox->w += tp->hitbox_width_offset + tp->hitbox_x_offset;
    hitbox->h += tp->hitbox_height_offset + tp->hitbox_y_offset;
    int z_index = (tm->topleft_y + (int)(index / tm->nTiles_x) * TILE_Z_INDEX_MAX) + tp->z_index_offset + Map(tp->drawable_y_offset, 0, TILE_HEIGHT, 0, TILE_Z_INDEX_MAX); //Row 1 = 10, Row 2 = 20....
    ConstructDrawable(d, tm->gfx, tp->filePath, *destrect, z_index);
}