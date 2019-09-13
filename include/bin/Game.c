#include "Game.h"
#include <stdio.h>
#include "Animal.h"

void ConstructGame(Game *g, int* noExit){
    
    ConstructGraphics(&g->gfx);
    ConstructTileMap(&g->tileMap, &g->gfx, 20, 20, 0, 0);
    ConstructPlayer(&g->player, &g->gfx);
    ConstructAnimal(&g->animal, &g->gfx);

    ConstructCamera(&g->cam, &g->gfx, &g->player.d.srcrect.x, &g->player.d.srcrect.y);
    
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
    UpdatePlayer(&g->player);
    UpdateAnimal(&g->animal);
    UpdateCamera(&g->cam);
}
void Render(Game *g){
    CamDraw(&g->cam, g->animal.d);    
    for(int i = 0; i < g->tileMap.nTiles_x * g->tileMap.nTiles_y; i++){
        CamDraw(&g->cam, g->tileMap.tiles[i].d);
    }
    CamDraw(&g->cam, g->player.d);
}

void HandleEvents(Game* g){
    while(SDL_PollEvent(&g->event)){
        if(g->event.type == SDL_QUIT){
            *g->noExit = 0;
        }
    }
}
