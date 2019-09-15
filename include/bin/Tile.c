#include "Tile.h"
#include <stdio.h>

void ConstructTile(Tile* t){
    t->currentDrawables = 0;
    t->currentHitboxes = 0;
}

void TileAddDrawable(Tile* t, Drawable d){
    if(t->currentDrawables != 3){
        t->ds[t->currentDrawables] = d;
        t->currentDrawables++;
    }
}
void TileAddHitbox(Tile* t, SDL_Rect hitbox){
    if(t->currentHitboxes != 3){
        t->hitboxes[t->currentHitboxes] = hitbox;
        t->currentHitboxes++;
    }
}