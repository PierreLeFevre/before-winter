#include "Drawable.h"

typedef struct Tile{
    Drawable d;
    int z_index;
}Tile;

void ConstructTile(Tile* t, Graphics* gfx, SDL_Rect srcrect);