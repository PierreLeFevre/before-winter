#include "Drawable.h"
#include "../SDL2/SDL_image.h"
#include <stdio.h>
#include <string.h>

void ConstructDrawable(Drawable* db, Graphics* gfx, const char* IMG_PATH, SDL_Rect srcrect){
    db->gfx = gfx;
    strcpy(db->filename, IMG_PATH);
    db->surf = IMG_Load(db->filename);
    db->tex = SDL_CreateTextureFromSurface(db->gfx->rend, db->surf);
    SDL_FreeSurface(db->surf);
    db->destrect.x = 0;
    db->destrect.y = 0;
    db->destrect.w = WINDOW_WIDTH;
    db->destrect.h = WINDOW_HEIGHT;
    db->srcrect = srcrect;
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
    d->x_pos = d->srcrect.x;
    d->y_pos = d->srcrect.y + d->srcrect.h;
}

void Draw(Drawable* d){
    SDL_RenderCopy(d->gfx->rend, d->tex, &d->destrect, &d->srcrect);
}

void ChangeImagePath(Drawable* d, const char* IMG_PATH){
    strcpy(d->filename, IMG_PATH);
    d->surf = IMG_Load(d->filename);
    d->tex = SDL_CreateTextureFromSurface(d->gfx->rend, d->surf);
    SDL_FreeSurface(d->surf);
}

void DrawableSetDestrect(Drawable* d, SDL_Rect destrect){
    d->destrect = destrect;
}