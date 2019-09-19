#include "Camera.h"
#include <stdio.h>

void ConstructCamera(Camera* cam, Graphics* gfx, SDL_Rect* follow){
    cam->gfx = gfx;
    cam->camRect.x = 0;
    cam->camRect.y = 0;
    cam->camRect.w = WINDOW_WIDTH;
    cam->camRect.h = WINDOW_HEIGHT;
    cam->camRectVirtual.x = 0;
    cam->camRectVirtual.y = 0;
    cam->camRectVirtual.w = WINDOW_WIDTH;
    cam->camRectVirtual.h = WINDOW_HEIGHT;
    cam->follow = follow;
}

void UpdateCamera(Camera* cam){    
    cam->camRectVirtual.x = cam->follow->x + cam->follow->w / 2 - cam->camRectVirtual.w / 2;
    cam->camRectVirtual.y = cam->follow->y + cam->follow->h / 2 - cam->camRectVirtual.h / 2;
    if(cam->camRectVirtual.x < 0){
        cam->camRectVirtual.x = 0;
    }
    if(cam->camRectVirtual.y < 0){
        cam->camRectVirtual.y = 0;
    }
}

void CamDraw(Camera* cam, Drawable d){
    if(SDL_HasIntersection(&cam->camRectVirtual, &d.destrect)){
    SDL_Rect destrectAdjustedToCamera = {d.destrect.x - cam->camRectVirtual.x, d.destrect.y - cam->camRectVirtual.y, d.destrect.w, d.destrect.h};
    d.destrect = destrectAdjustedToCamera;
    Draw(d);
    }
}