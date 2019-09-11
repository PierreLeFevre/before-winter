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
    db->srcrect = srcrect;
}

void Draw(Drawable* db){
    SDL_RenderCopy(db->gfx->rend, db->tex, NULL, &db->srcrect);
}

void ChangeImagePath(Drawable* db, const char* IMG_PATH){
    strcpy(db->filename, IMG_PATH);
    db->surf = IMG_Load(db->filename);
    db->tex = SDL_CreateTextureFromSurface(db->gfx->rend, db->surf);
    SDL_FreeSurface(db->surf);
}