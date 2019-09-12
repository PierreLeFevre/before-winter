#include "TileMap.h"
#include <stdio.h>
#include <math.h>

void ConstructTileMap(TileMap* tm, Graphics* gfx, const int tiles_x, const int tiles_y, const int topleft_x, const int topleft_y){
    tm->tiles = (Tile*) malloc(sizeof(Tile) * tiles_x * tiles_y);
    tm->tiles_x = tiles_x;
    tm->tiles_y = tiles_y;
    tm->tile_width = TILE_WIDTH;
    tm->tile_height = TILE_HEIGHT;
    tm->topleft_x = topleft_x;
    tm->topleft_y = topleft_y;
    tm->angle = 0;
    for(int i = 0; i < tm->tiles_x * tm->tiles_y; i++){
            SDL_Rect srcrect;
            srcrect.x = tm->topleft_x + (int)(i % tm->tiles_x) * tm->tile_width;
            srcrect.y = tm->topleft_y + (int)(i / tm->tiles_x) * tm->tile_height;
            srcrect.w = tm->tile_width;
            srcrect.h = tm->tile_height;
            Tile t;
            ConstructTile(&t, gfx, srcrect);
            tm->tiles[i] = t;
    }
}

void DrawTileMap(TileMap* tm){
    for(int i = 0; i < tm->tiles_x * tm->tiles_y; i++){
        Draw(&tm->tiles[i].d);
    }
}