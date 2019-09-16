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
    char* mapData = malloc(numbytes + 1);
	fread(mapData, 1, numbytes, fileIO);
    mapData[numbytes] = 0;
    RemoveCharacterFromArray(mapData, '\r');
    RemoveCharacterFromArray(mapData, '\n');
    RemoveCharacterFromArray(mapData, ' ');
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
            SDL_Rect srcrect = {
            tm->topleft_x + (int)(i % tm->nTiles_x) * tm->tile_width
            ,tm->topleft_y + (int)(i / tm->nTiles_x) * tm->tile_height
            ,tm->tile_width
            ,tm->tile_height
            };
            //Hitbox is set to tile dtpensions, DEFAULT
            SDL_Rect hitbox = srcrect;
            
            TileProperties tp = GetTilePropertiesData(*mapData - '0');
            srcrect.h = tp.drawable_height;
            srcrect.y += tp.drawable_y_offset; //Stpulates drawing from BOTTOM-LEFT

            Drawable d;
            int z_index = (tm->topleft_y + (int)(i / tm->nTiles_x) * TILE_Z_INDEX_MAX) + tp.z_index_offset; //Row 1 = 10, Row 2 = 20....

            ConstructDrawable(&d, gfx, tp.filePath, srcrect, z_index);

            if(*(mapData - 1) == ','){
                Tile t;
                ConstructTile(&t);
                tm->tiles[i] = t;
            }
            Tile t = tm->tiles[i];
            TileAddDrawable(&t, d);
            TileAddHitbox(&t, hitbox);
            tm->tiles[i] = t;

            mapData++;
    }
    free(mapData);
}

TileProperties GetTilePropertiesData(const MapDataConverter mdc){
    TileProperties tp;
     //--- Default ---
    tp.drawable_height = TILE_HEIGHT;
    tp.z_index_offset = 0;
    //----------------
    switch(mdc){
        case MUD:
        tp.filePath = "include/assets/mud.jpg";
        break;
        case GRASS:
        tp.filePath = "include/assets/grass.jpg";
        break;
        case TREE:
        tp.filePath = "include/assets/tree.png";
        tp.drawable_height = 150;
        tp.z_index_offset = 90;
        break;
        default:
        tp.filePath = "include/assets/Question_mark.jpg";
        break;
    }
    tp.drawable_y_offset = TILE_HEIGHT - tp.drawable_height;
    return tp;
}

void AddTileMapToRenderList(TileMap* tm, Camera* cam, Drawable** RenderList, int* nToRender){
    for(int i = 0; i < tm->nTiles_x * tm->nTiles_y; i++){
        SDL_Rect currTile = tm->tiles[i].ds[0].srcrect;
        SDL_Rect camera = cam->camRectVirtual;
        if(currTile.x > camera.x + camera.w + TILE_WIDTH * 2){
            i += (int)(abs(currTile.x-(tm->nTiles_x * TILE_WIDTH)) / TILE_WIDTH) - 1;
            continue;
        }
        if(currTile.x + currTile.w < camera.x - TILE_WIDTH * 2){
            i += (int)(abs((currTile.x + currTile.w)-(camera.x - TILE_WIDTH * 2)) / TILE_WIDTH);
            continue;
        }
        if(currTile.y + currTile.h < camera.y - TILE_HEIGHT * 2){
            i += (int)(abs(tm->nTiles_x * TILE_WIDTH) / TILE_WIDTH);
            continue;
        }
        if(currTile.y > camera.y + camera.h + TILE_HEIGHT * 2){
            break;
        };
        for(int j = 0; j < tm->tiles[i].currentDrawables; j++)
        if(SDL_HasIntersection(&tm->tiles[i].ds[j].srcrect, &cam->camRectVirtual)){
            RenderList[*nToRender] = &tm->tiles[i].ds[j];
            (*nToRender)++;            
        }
    }
}