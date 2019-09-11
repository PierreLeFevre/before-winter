#include "Graphics.h"

typedef struct Drawable{
    Graphics* gfx;
    SDL_Surface* surf;
    SDL_Texture* tex;
    float x_pos;
    float y_pos;
}Drawable;

void ConstructDrawable(Drawable* db, Graphics* gfx, const char* IMG_PATH);
void Draw(Drawable* db);