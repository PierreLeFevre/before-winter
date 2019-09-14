#include "TileMap.h"
#include <stdio.h>
#include <math.h>
#include "../SDL2/SDL_image.h"
#include <string.h>

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

    int nBytesToMove = 0;
	for (char* bufferP = mapDataRaw; *(bufferP - 1) != 0; bufferP++) {
		*(bufferP - nBytesToMove) = *bufferP;
		if (*bufferP == '\r') {
			nBytesToMove++;
		}
	}
    fclose(fileIO);
    for(int i = 0; i < tm->nTiles_x * tm->nTiles_y; i++){
            SDL_Rect srcrect = {
            tm->topleft_x + (int)(i % tm->nTiles_x) * tm->tile_width
            ,tm->topleft_y + (int)(i / tm->nTiles_x) * tm->tile_height
            ,tm->tile_width
            ,tm->tile_height
            };
            Drawable d;
            while(*mapDataRaw != '\0' && (*mapDataRaw == '\n' || *mapDataRaw == ',' || *mapDataRaw == ' ')){
                mapDataRaw++;
            }
            if(*mapDataRaw != '*'){
                ConstructDrawable(&d, gfx, GetFilepathToTile(*mapDataRaw - '0'), srcrect);
                mapDataRaw++;
            }
            Tile t;
            ConstructTile(&t, &d);
            tm->tiles[i] = t;
    }
    free(mapDataRaw);
}

const char* const GetFilepathToTile(const MapDataConverter mdc){

    switch(mdc){
        case MUD:
        return "include/assets/mud.jpg";
        break;
        case GRASS:
        return "include/assets/grass.jpg";
        break;
        default:
        return "include/assets/Question_mark.jpg";

    }
}