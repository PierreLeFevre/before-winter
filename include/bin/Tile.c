#include "Tile.h"
void ConstructTile(Tile* tile){
    tile->currentSpriteAmmount = 0;
}

void TileAddSprite(Tile* tile, Drawable drawable, SDL_Rect hitbox, int z_index){
    if(tile->currentSpriteAmmount < 3){
        tile->drawables[tile->currentSpriteAmmount] = drawable;
        tile->hitboxes[tile->currentSpriteAmmount] = hitbox;
        tile->currentSpriteAmmount++;
    }
}