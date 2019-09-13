#include "Camera.h"

void ConstructCamera(Camera* cam, Graphics* gfx, int* x_follow, int* y_follow){
    cam->camRect.x = 0;
    cam->camRect.y = 0;
    cam->camRect.w = WINDOW_WIDTH;
    cam->camRect.h = WINDOW_HEIGHT;
    cam->gfx = gfx;
    ConstructDrawable(&cam->background, cam->gfx, "./include/assets/background.jpg", cam->camRect);
    cam->x_follow = x_follow;
    cam->y_follow = y_follow;
}

void UpdateCamera(Camera* cam){    
    cam->background.destrect.x = *(cam->x_follow) - WINDOW_WIDTH / 2;
    cam->background.destrect.y = *(cam->y_follow) - WINDOW_HEIGHT / 2;
    if(cam->camRect.x < 0){
        cam->camRect.x = 0;
    }
    if(cam->camRect.y < 0){
        cam->camRect.y = 0;
    }
}

void CamDraw(Camera* cam, Drawable d){
    SDL_Rect srcrectAdjustedToCamera = {d.srcrect.x - cam->background.destrect.x, d.srcrect.y - cam->background.destrect.y, d.srcrect.w, d.srcrect.h};
    d.srcrect = srcrectAdjustedToCamera;
    Draw(&d);
}