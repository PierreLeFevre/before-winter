#ifndef TILE_H
#define TILE_H
#include "Drawable.h"

typedef struct Tile{
    Drawable drawables[3];
    SDL_Rect hitboxes[3];
    int currentSpriteAmmount;
}Tile;

void ConstructTile(Tile* t);

void TileAddSprite(Tile* tile, Drawable drawable, SDL_Rect hitbox, int z_index);

#endif