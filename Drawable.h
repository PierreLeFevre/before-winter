#include "Graphics.h"

typedef struct Drawable{
    Graphics* gfx;
    SDL_Surface* surf;
    SDL_Texture* tex;
    SDL_Rect srcrect;
}Drawable;

// void ConstructDrawable(Drawable* db, Graphics* gfx, const char* IMG_PATH);
// void ConstructDrawable(Drawable* db, Graphics* gfx, const char* IMG_PATH, float x_pos, float y_pos);
void ConstructDrawable(Drawable* db, Graphics* gfx, const char* IMG_PATH, SDL_Rect srcrect);
void Draw(Drawable* db);