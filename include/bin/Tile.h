#ifndef TILE_H
#define TILE_H
#include "Drawable.h"

typedef enum TileEdges{
    tile_overlay_left,
    tile_overlay_top_left,
    tile_overlay_top,
    tile_overlay_top_right,
    tile_overlay_right,
    tile_overlay_bottom_right,
    tile_overlay_bottom,
    tile_overlay_bottom_left,
    tile_overlay_enumsize
}TileEdges;

typedef struct Tile{
    Drawable overlays[tile_overlay_enumsize];

    Drawable drawables[3];
    SDL_Rect hitboxes[3];
    int currentSpriteAmmount;
}Tile;

void ConstructTile(Tile* t);

void TileAddSprite(Tile* tile, Drawable drawable, SDL_Rect hitbox, int z_index);

#endif