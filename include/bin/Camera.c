#include "Camera.h"
#include <stdio.h>

void ConstructCamera(Camera* cam, Graphics* gfx, SDL_Rect* follow, TileMap* tilemap){
    cam->gfx = gfx;
    cam->tilemap = tilemap;
    cam->camRect.x = 0;
    cam->camRect.y = 0;
    cam->camRect.w = gfx->wWidth;
    cam->camRect.h = gfx->wHeight;
    cam->camRectVirtual.x = 0;
    cam->camRectVirtual.y = 0;
    cam->camRectVirtual.w = gfx->wWidth;
    cam->camRectVirtual.h = gfx->wHeight;
    cam->follow = follow;
}

void UpdateCamera(Camera* cam){   
    
    cam->camRect.w = cam->gfx->wWidth;
    cam->camRect.h = cam->gfx->wHeight;
    cam->camRectVirtual.w = cam->gfx->wWidth;
    cam->camRectVirtual.h = cam->gfx->wHeight;

    cam->camRectVirtual.x = cam->follow->x + cam->follow->w / 2 - cam->camRectVirtual.w / 2;
    cam->camRectVirtual.y = cam->follow->y + cam->follow->h / 2 - cam->camRectVirtual.h / 2;
    if(cam->camRectVirtual.x < 0){
        cam->camRectVirtual.x = 0;
    }
    if(cam->camRectVirtual.y < 0){
        cam->camRectVirtual.y = 0;
    }
    if(cam->camRectVirtual.x + cam->camRectVirtual.w > cam->tilemap->nTiles_x * TILE_WIDTH){
        cam->camRectVirtual.x = cam->tilemap->nTiles_x * TILE_WIDTH - cam->camRectVirtual.w;
    }
    if(cam->camRectVirtual.y + cam->camRectVirtual.h > cam->tilemap->nTiles_y * TILE_HEIGHT){
        cam->camRectVirtual.y = cam->tilemap->nTiles_y * TILE_HEIGHT - cam->camRectVirtual.h;
    }
}

void CamDraw(Camera* cam, Drawable d){
    if(SDL_HasIntersection(&cam->camRectVirtual, &d.destrect)){
    SDL_Rect destrectAdjustedToCamera = {d.destrect.x - cam->camRectVirtual.x, d.destrect.y - cam->camRectVirtual.y, d.destrect.w, d.destrect.h};
    d.destrect = destrectAdjustedToCamera;
    Draw(&d);
    }
}