#include "Drawable.h"
#include "../SDL2/SDL_image.h"
#include <stdio.h>
#include <string.h>

void ConstructDrawable(Drawable* d, Graphics* gfx, const char* IMG_PATH, SDL_Rect srcrect){
    d->gfx = gfx;
    strcpy(d->filename, IMG_PATH);
    d->surf = IMG_Load(d->filename);
    d->tex = SDL_CreateTextureFromSurface(d->gfx->rend, d->surf);
    SDL_FreeSurface(d->surf);
    d->destrect.x = 0;
    d->destrect.y = 0;
    d->destrect.w = WINDOW_WIDTH;
    d->destrect.h = WINDOW_HEIGHT;
    d->srcrect = srcrect;
}

void Draw(Drawable d){
    d.srcrect.x -= d.srcrect.w / 2;
    d.srcrect.y -= d.srcrect.h / 2;
    SDL_RenderCopy(d.gfx->rend, d.tex, &d.destrect, &d.srcrect);
}

void ChangeImagePath(Drawable* d, const char* IMG_PATH){
    strcpy(d->filename, IMG_PATH);
    d->surf = IMG_Load(d->filename);
    d->tex = SDL_CreateTextureFromSurface(d->gfx->rend, d->surf);
    SDL_FreeSurface(d->surf);
}

void DrawableSetDestRect(Drawable* d, SDL_Rect destrect){
    d->destrect = destrect;
}