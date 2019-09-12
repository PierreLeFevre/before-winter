#include "Game.h"
#include <stdio.h>
void ConstructGame(Game *g){
    ConstructGraphics(&g->gfx);
    SDL_Rect sr;
    sr.x = 10;
    sr.y = 10;
    sr.w = 200;
    sr.h = 200;
    ConstructTileMap(&g->tm, &g->gfx);
}
void DestroyGame(Game *g){
    DestroyGraphics(&g->gfx);
}

void Go(Game *g){
    
    BeginFrame(&g->gfx);
    UpdateLogic(g);
    Render(g);
    EndFrame(&g->gfx);
}

void UpdateLogic(Game *g){

}
void Render(Game *g){
<<<<<<< HEAD
    Drawable db;
    SDL_Rect sr;
    sr.x = 10;
    sr.y = 10;
    sr.w = 200;
    sr.h = 200;
    ConstructDrawable(&db, &g->gfx, "./include/assets/1.png", sr);
    DrawTileMap(&g->tm);
=======
    SDL_Rect *r;
    r->x = 10;
    r->y = 10;
    r->w = 10;
    r->h = 10;
    DrawFilledRectangle(g->gfx.rend, r);
>>>>>>> c1966d529a67fba5c313a5fcab394f4a962b1ed5
}