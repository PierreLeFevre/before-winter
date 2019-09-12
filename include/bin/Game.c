#include "Game.h"
#include <stdio.h>
void ConstructGame(Game *g){
    ConstructGraphics(&g->gfx);
    SDL_Rect sr;
    sr.x = 10;
    sr.y = 10;
    sr.w = 200;
    sr.h = 200;
    ConstructTileMap(&g->tm, &g->gfx, 6, 6, 40, 40);
    ConstructPlayer(&g->player);
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
    DrawTileMap(&g->tm);
}