#include "Drawable.h"
#include "include/SDL2/SDL_image.h"
#include "stdio.h"

void ConstructDrawable(Drawable* db, Graphics* gfx, const char* IMG_PATH){
    db->gfx = gfx;
    db->surf = IMG_Load(IMG_PATH);
    db->tex = SDL_CreateTextureFromSurface(db->gfx->rend, db->surf);
    SDL_FreeSurface(db->surf);
    float x_pos = 0.0f;
    float y_pos = 0.0f;
}

void Draw(Drawable* db){
    SDL_RenderCopy(db->gfx->rend, db->tex, NULL, NULL);
}