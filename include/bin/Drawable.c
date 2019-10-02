#include "Drawable.h"
#include "../SDL2/SDL_image.h"
#include <stdio.h>
#include <string.h>

void ConstructDrawable(Drawable* d, DrawableType type, Graphics* gfx, SpriteSheet spritesheet, SDL_Rect srcrect, SDL_Rect destrect, int z_index){
    d->type = type;
    d->gfx = gfx;
    d->spritesheet = spritesheet;
    d->tex = d->gfx->textures[spritesheet];
    d->srcrect = srcrect;
    d->destrect = destrect;
    d->z_index = z_index;
}

void Draw(Drawable* d){
    SDL_RenderCopy(d->gfx->rend, d->tex, &d->srcrect, &d->destrect);
}