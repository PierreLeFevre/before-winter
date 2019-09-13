#include "Tile.h"
#include <stdio.h>

void ConstructTile(Tile* t, Drawable* d){
    t->d = *d;
    t->z_index = 0;
}