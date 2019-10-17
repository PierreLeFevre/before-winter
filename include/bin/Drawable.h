#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "Graphics.h"

typedef enum DrawableType{
    DT_Player,
    DT_Player_Home,
    DT_GUI,
    DT_Plant,
    DT_Item,
    DT_Grass,
    DT_Sand,
    DT_Dirt,
    DT_Water,
    DT_Pier,
    DT_Plank_Bridge,
    DT_Lighthouse,
    DT_Fence_Horizontal,
    DT_Fence_Vertical,
    DT_Transparent,
    DT_Other,
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