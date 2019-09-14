#include "Drawable.h"
#include "../SDL2/SDL_image.h"
#include <stdio.h>
#include <string.h>

void ConstructDrawable(Drawable* d, Graphics* gfx, const char* filePath, SDL_Rect srcrect){
    d->gfx = gfx;
    strcpy(d->filePath, filePath);
    d->surf = IMG_Load(d->filePath);
    d->tex = SDL_CreateTextureFromSurface(d->gfx->rend, d->surf);
    SDL_FreeSurface(d->surf);
    d->destrect.x = 0;
    d->destrect.y = 0;
    d->destrect.w = WINDOW_WIDTH;
    d->destrect.h = WINDOW_HEIGHT;
    d->srcrect = srcrect;
}

void Draw(Drawable d){
    SDL_RenderCopy(d.gfx->rend, d.tex, &d.destrect, &d.srcrect);
}

void ChangeImagePath(Drawable* d, const char* filePath){
    strcpy(d->filePath, filePath);
    d->surf = IMG_Load(d->filePath);
    d->tex = SDL_CreateTextureFromSurface(d->gfx->rend, d->surf);
    SDL_FreeSurface(d->surf);
}

void DrawableSetDestRect(Drawable* d, SDL_Rect destrect){
    d->destrect = destrect;
}