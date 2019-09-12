#include "TileMap.h"
#include <stdio.h>

void ConstructTileMap(TileMap* tm, Graphics* gfx){
    for(int x = 0; x < TILES_X; x++){
        for(int y = 0; y < TILES_Y; y++){
            SDL_Rect srcrect;
            srcrect.x = x * TILE_WIDTH;
            srcrect.y = y * TILE_HEIGHT;
            srcrect.w = TILE_WIDTH;
            srcrect.h = TILE_HEIGHT;
            Tile t;
            ConstructTile(&t, gfx, srcrect);
            tm->tiles[x][y] = t;
        }
    }
}

void DrawTileMap(TileMap* tm){
    for(int x = 0; x < TILES_X; x++){
        for(int y = 0; y < TILES_Y; y++){
            Draw(&tm->tiles[x][y].d);
        }
    }
}