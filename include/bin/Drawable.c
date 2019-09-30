#include "Drawable.h"
#include "../SDL2/SDL_image.h"
#include <stdio.h>
#include <string.h>

void ConstructDrawable(Drawable* d, Graphics* gfx, const char* filePath, SDL_Rect destrect, int z_index){
    strcpy(d->filePath, filePath);
    d->gfx = gfx;
    d->surf = IMG_Load(d->filePath);
    d->tex = SDL_CreateTextureFromSurface(d->gfx->rend, d->surf);
    SDL_FreeSurface(d->surf);
    d->srcrect.x = 0;
    d->srcrect.y = 0;
    d->srcrect.w = gfx->wWidth;
    d->srcrect.h = gfx->wHeight;
    d->destrect = destrect;
    d->z_index = z_index;
}

void Draw(Drawable d){
    SDL_RenderCopy(d.gfx->rend, d.tex, &d.srcrect, &d.destrect);
}

void ChangeImagePath(Drawable* d, const char* filePath){
    strcpy(d->filePath, filePath);
    d->surf = IMG_Load(d->filePath);
    d->tex = SDL_CreateTextureFromSurface(d->gfx->rend, d->surf);
    SDL_FreeSurface(d->surf);
}

void DrawableSetSrcRect(Drawable* d, SDL_Rect srcrect){
    d->srcrect = srcrect;
}