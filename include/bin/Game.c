#include "Game.h"
#include <stdio.h>
void ConstructGame(Game *g, int* noExit){
    ConstructGraphics(&g->gfx);
    SDL_Rect sr;
    sr.x = 10;
    sr.y = 10;
    sr.w = 200;
    sr.h = 200;
    ConstructTileMap(&g->tm, &g->gfx, 6, 6, 40, 40);
    ConstructPlayer(&g->player, &g->gfx);

    g->noExit = noExit;
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
    HandleEvents(g);
}
void Render(Game *g){
    DrawTileMap(&g->tm);
    DrawPlayer(&g->player);
}

void HandleEvents(Game* g){
    while(SDL_PollEvent(&g->event)){
        switch(g->event.type){
            case SDL_QUIT:
                *g->noExit = 0;
                break;
        }
    }
}