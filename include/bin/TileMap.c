#include "TileMap.h"
#include <stdio.h>
#include <math.h>
#include "../SDL2/SDL_image.h"
#include <string.h>
#include "FuncLib.h"

void ConstructTileMap(TileMap* tm, Graphics* gfx, const int nTiles_x, const int nTiles_y, const int topleft_x, const int topleft_y, char* mapFile){
    tm->tiles = (Tile*) malloc(sizeof(Tile) * nTiles_x * nTiles_y);
    tm->nTiles_x = nTiles_x;
    tm->nTiles_y = nTiles_y;
    tm->tile_width = TILE_WIDTH;
    tm->tile_height = TILE_HEIGHT;
    tm->topleft_x = topleft_x;
    tm->topleft_y = topleft_y;
    tm->mapFile = mapFile;
    
	FILE* fileIO = fopen(mapFile, "rb");
	fseek(fileIO, 0L, SEEK_END);
	long int numbytes = ftell(fileIO);
	fseek(fileIO, 0L, SEEK_SET);
    char* mapDataRaw = malloc(numbytes + 1);
	fread(mapDataRaw, 1, numbytes, fileIO);
    mapDataRaw[numbytes] = 0;
    fixArrayBug(mapDataRaw);
    fclose(fileIO);

    for(int i = 0; i < tm->nTiles_x * tm->nTiles_y; i++){
            SDL_Rect srcrect = {
            tm->topleft_x + (int)(i % tm->nTiles_x) * tm->tile_width
            ,tm->topleft_y + (int)(i / tm->nTiles_x) * tm->tile_height
            ,tm->tile_width
            ,tm->tile_height
            };
            SDL_Rect hitbox = srcrect;
            Drawable d;
            while(*mapDataRaw != '\0' && (*mapDataRaw == '\n' || *mapDataRaw == ',' || *mapDataRaw == ' ')){
                mapDataRaw++;
            }
            if(*mapDataRaw != '*'){
                TileImage td = GetTileImageData(*mapDataRaw - '0');
                srcrect.h = td.height;
                srcrect.y += td.y_offset;
                ConstructDrawable(&d, gfx, td.filePath, srcrect);
                mapDataRaw++;
            }
            Tile t;
            ConstructTile(&t, &d, hitbox);
            tm->tiles[i] = t;
    }
    free(mapDataRaw);
}

TileImage GetTileImageData(const MapDataConverter mdc){
    TileImage im;
    im.height = TILE_HEIGHT; //Default
    switch(mdc){
        case MUD:
        im.filePath = "include/assets/mud.jpg";
        im.height = 200;
        break;
        case GRASS:
        im.filePath = "include/assets/grass.jpg";
        break;
        default:
        im.filePath = "include/assets/Question_mark.jpg";
        break;
    }
    im.y_offset = TILE_HEIGHT - im.height;
    return im;
}