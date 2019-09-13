#include "TileMap.h"
#include <stdio.h>
#include <math.h>
#include "../SDL2/SDL_image.h"

void ConstructTileMap(TileMap* tm, Graphics* gfx, const int nTiles_x, const int nTiles_y, const int topleft_x, const int topleft_y, char* fullBackground){
    tm->tiles = (Tile*) malloc(sizeof(Tile) * nTiles_x * nTiles_y);
    tm->nTiles_x = nTiles_x;
    tm->nTiles_y = nTiles_y;
    tm->tile_width = TILE_WIDTH;
    tm->tile_height = TILE_HEIGHT;
    tm->topleft_x = topleft_x;
    tm->topleft_y = topleft_y;
    for(int i = 0; i < tm->nTiles_x * tm->nTiles_y; i++){
            SDL_Rect srcrect = {
            tm->topleft_x + (int)(i % tm->nTiles_x) * tm->tile_width
            ,tm->topleft_y + (int)(i / tm->nTiles_x) * tm->tile_height
            ,tm->tile_width
            ,tm->tile_height
            };
            Drawable d;
            ConstructDrawable(&d, gfx, "include/assets/mud.jpg", srcrect);
            Tile t;
            ConstructTile(&t, &d);
            tm->tiles[i] = t;
    }
}

void DrawTileMap(TileMap* tm){
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