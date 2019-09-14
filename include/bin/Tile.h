#include "Drawable.h"

typedef struct Tile{
    Drawable d;
    SDL_Rect hitbox;
}Tile;

void ConstructTile(Tile* t, Drawable* d, SDL_Rect hitbox);