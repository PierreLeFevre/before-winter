#include "TileMap.h"
#include <stdio.h>
#include <math.h>

void ConstructTileMap(TileMap* tm, Graphics* gfx, const int nTiles_x, const int nTiles_y, const int topleft_x, const int topleft_y){
    tm->tiles = (Tile*) malloc(sizeof(Tile) * nTiles_x * nTiles_y);
    tm->nTiles_x = nTiles_x;
    tm->nTiles_y = nTiles_y;
    tm->tile_width = TILE_WIDTH;
    tm->tile_height = TILE_HEIGHT;
    tm->topleft_x = topleft_x;
    tm->topleft_y = topleft_y;
    tm->angle = 0;
    for(int i = 0; i < tm->nTiles_x * tm->nTiles_y; i++){
            SDL_Rect srcrect;
            srcrect.x = tm->topleft_x + (int)(i % tm->nTiles_x) * tm->tile_width;
            srcrect.y = tm->topleft_y + (int)(i / tm->nTiles_x) * tm->tile_height;
            srcrect.w = tm->tile_width;
            srcrect.h = tm->tile_height;
            Tile t;
            ConstructTile(&t, gfx, srcrect);
            tm->tiles[i] = t;
    }
}

void DrawTileMap(TileMap* tm){
    for(int i = 0; i < tm->nTiles_x * tm->nTiles_y; i++){
        Draw(&tm->tiles[i].d);
    }
}
void ChangeTileMapImage(TileMap* tm, const char* IMG_PATH){
    for(int i = 0; i < tm->nTiles_x * tm->nTiles_y; i++){
        ChangeImagePath(&tm->tiles[i].d, IMG_PATH);
    }
}

void UpdateTileMap(TileMap* tm){
    for(int i = 0; i < tm->nTiles_x * tm->nTiles_y; i++){
            tm->tiles[i].d.srcrect.x = tm->topleft_x + (int)(i % tm->nTiles_x) * tm->tile_width;
            tm->tiles[i].d.srcrect.y = tm->topleft_y + (int)(i / tm->nTiles_x) * tm->tile_height;
    }
}