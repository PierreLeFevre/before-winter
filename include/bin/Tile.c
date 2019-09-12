#include "Tile.h"
#include <stdio.h>

void ConstructTile(Tile* t, Graphics* gfx, SDL_Rect srcrect){
    t->d.gfx = gfx;
    ConstructDrawable(&(t->d), t->d.gfx, "./include/assets/grass_squared_compressed.jpg", srcrect);
    t->z_index = 0;
}