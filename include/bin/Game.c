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
    Drawable db;
    SDL_Rect sr;
    sr.x = 10;
    sr.y = 10;
    sr.w = 200;
    sr.h = 200;
    ConstructDrawable(&db, &g->gfx, "./include/assets/1.png", sr);
    ChangeImagePath(&db, "./include/assets/2.png");        
    Draw(&db);
}