#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Graphics.h"

typedef struct Drawable{
    Graphics* gfx;
    SDL_Surface* surf;
    SDL_Texture* tex;
    SDL_Rect destrect;
    SDL_Rect srcrect;
    char filename[100];
}Drawable;

void ConstructDrawable(Drawable* d, Graphics* gfx, const char* IMG_PATH, SDL_Rect srcrect);
void Draw(Drawable d);

void ChangeImagePath(Drawable* d, const char* IMG_PATH);
void DrawableSetDestrect(Drawable* d, SDL_Rect destrect);

#endif