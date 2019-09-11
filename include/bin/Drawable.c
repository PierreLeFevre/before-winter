#include "Drawable.h"
#include "include/SDL2/SDL_image.h"
#include "stdio.h"
#include <string.h>

// void ConstructDrawable(Drawable* db, Graphics* gfx, const char* IMG_PATH){
//     ConstructDrawable(db, gfx, IMG_PATH, 0.0f, 0.0f, WINDOW_WIDTH, WINDOW_HEIGHT);
// }
// void ConstructDrawable(Drawable* db, Graphics* gfx, const char* IMG_PATH, float x_pos, float y_pos, float w, float h){
//     SDL_Rect srcrect;
//     srcrect.x = x_pos;
//     srcrect.y = y_pos;
//     srcrect.w = w;
//     srcrect.h = h;
//     ConstructDrawable(db, gfx, IMG_PATH, srcrect);
// }
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