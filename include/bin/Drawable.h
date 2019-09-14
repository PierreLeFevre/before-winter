#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Graphics.h"

typedef struct Drawable{
    Graphics* gfx;
    SDL_Surface* surf;
    SDL_Texture* tex;
    SDL_Rect destrect;
    SDL_Rect srcrect;
    char filePath[100];
    int z_index;
}Drawable;

void ConstructDrawable(Drawable* d, Graphics* gfx, const char* filePath, SDL_Rect srcrect, int z_index);
void Draw(Drawable d);

void ChangeImagePath(Drawable* d, const char* filePath);
void DrawableSetDestRect(Drawable* d, SDL_Rect destrect);

#endif