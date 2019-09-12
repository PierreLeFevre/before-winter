#include "Game.h"
#include <stdio.h>
void ConstructGame(Game *g){
    ConstructGraphics(&g->gfx);
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
    SDL_Rect *r;
    r->x = 10;
    r->y = 10;
    r->w = 10;
    r->h = 10;
    DrawFilledRectangle(g->gfx.rend, r);
}