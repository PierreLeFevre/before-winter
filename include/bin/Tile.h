#ifndef TILE_H
#define TILE_H
#include "Drawable.h"

typedef enum TileEdges{
    tile_overlay_left,
    tile_overlay_top_left_inner,
    tile_overlay_top_left_outer,
    tile_overlay_top,
    tile_overlay_top_right_inner,
    tile_overlay_top_right_outer,
    tile_overlay_right,
    tile_overlay_bottom_right_inner,
    tile_overlay_bottom_right_outer,
    tile_overlay_bottom,
    tile_overlay_bottom_left_inner,
    tile_overlay_bottom_left_outer,
    tile_overlay_enumsize
}TileEdges;

typedef enum TileOverlayTypes{
    tile_overlay_grass_to_dirt,
    tile_overlay_anything_to_water,
    tile_overlay_types_enumsize
}TileOverlayTypes;

typedef struct Tile{
    Drawable overlays[tile_overlay_types_enumsize][tile_overlay_enumsize];
    int overlays_used[tile_overlay_types_enumsize][tile_overlay_enumsize];

    Drawable drawables[3];
    SDL_Rect hitboxes[3];
    int currentSpriteAmmount;
}Tile;

void ConstructTile(Tile* t);

void TileAddSprite(Tile* tile, Drawable drawable, SDL_Rect hitbox, int z_index);

#endif