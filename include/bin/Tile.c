#include "Tile.h"
void ConstructTile(Tile* tile){
    tile->currentSpriteAmmount = 0;
    for(int i = 0; i < tile_overlay_types_enumsize; i++){
        for(int j = 0; j < tile_overlay_enumsize; j++){
            tile->overlays_used[i][j] = 0;
        }
    }
}

void TileAddSprite(Tile* tile, Drawable drawable, SDL_Rect hitbox, int z_index){
    if(tile->currentSpriteAmmount < 3){
        tile->drawables[tile->currentSpriteAmmount] = drawable;
        tile->hitboxes[tile->currentSpriteAmmount] = hitbox;
        tile->currentSpriteAmmount++;
    }
}