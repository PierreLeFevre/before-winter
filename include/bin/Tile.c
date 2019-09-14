#include "Tile.h"
#include <stdio.h>

void ConstructTile(Tile* t, Drawable* d, SDL_Rect hitbox){
    t->d = *d;
    t->hitbox = hitbox;
    t->z_index = 0;
}