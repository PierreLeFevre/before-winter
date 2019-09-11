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
    Draw(g);
    EndFrame(&g->gfx);
}

void UpdateLogic(Game *g){



}

void Draw(Game *g){




}