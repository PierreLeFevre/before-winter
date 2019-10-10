#ifndef CAMERA_H
#define CAMERA_H

#include "Drawable.h"
#include "TileMap.h"

typedef struct Camera{
    Graphics* gfx;
    TileMap* tilemap;
    SDL_Rect camRect;
    SDL_Rect camRectVirtual;
    SDL_Rect* follow;
}Camera;

void ConstructCamera(Camera* cam, Graphics* gfx, SDL_Rect* follow, TileMap* tilemap);
void UpdateCamera(Camera* cam);
void CamDraw(Camera* cam, Drawable d);

#endif