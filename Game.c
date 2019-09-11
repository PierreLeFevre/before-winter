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
    ConstructDrawable(&db, &g->gfx, "1.png");
    Draw(&db);
}