#ifndef CAMERA_H
#define CAMERA_H

#include "Drawable.h"

typedef struct Camera{
    Graphics* gfx;
    Drawable background;
    SDL_Rect camRect;
    int* x_follow;
    int* y_follow;
}Camera;

void ConstructCamera(Camera* cam, Graphics* gfx, int* x_follow, int* y_follow);
void UpdateCamera(Camera* cam);
void CamDraw(Camera* cam, Drawable d);

#endif