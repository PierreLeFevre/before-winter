#ifndef CAMERA_H
#define CAMERA_H

#include "Drawable.h"

typedef struct Camera{
    Graphics* gfx;
    SDL_Rect camRect;
    SDL_Rect camRectVirtual;
    SDL_Rect* follow;
}Camera;

void ConstructCamera(Camera* cam, Graphics* gfx, SDL_Rect* follow);
void UpdateCamera(Camera* cam);
void CamDraw(Camera* cam, Drawable d);

#endif