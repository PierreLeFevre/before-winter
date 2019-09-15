#include "Drawable.h"

typedef struct Tile{
    Drawable ds[3];
    int currentDrawables;
    SDL_Rect hitboxes[3];
    int currentHitboxes;
}Tile;

void ConstructTile(Tile* t);

void TileAddDrawable(Tile* t, Drawable d);
void TileAddHitbox(Tile* t, SDL_Rect hitbox);