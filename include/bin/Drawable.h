#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Graphics.h"

typedef enum DrawableType{
    DT_Player,
    DT_Player_Home,
    DT_GUI,
    DT_Other,
    DT_Plant,
    DT_Item,
    DT_Grass,
    DT_Dirt
}DrawableType;

typedef struct Drawable{
    DrawableType type;
    Graphics* gfx;
    SpriteSheet spritesheet;
    SDL_Texture* tex;
    SDL_Rect srcrect;
    SDL_Rect destrect;
    int z_index;
}Drawable;

void ConstructDrawable(Drawable* d, DrawableType type, Graphics* gfx, SpriteSheet spritesheet, SDL_Rect srcrect, SDL_Rect destrect, int z_index);
void Draw(Drawable* d);

void DrawableChangeSpriteSheet(Drawable *d, SpriteSheet spritesheet);

#endif