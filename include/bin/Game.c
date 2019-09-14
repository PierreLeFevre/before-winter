#include "Game.h"
#include <stdio.h>
#include "Animal.h"

void ConstructGame(Game *g, int* noExit){
    
    ConstructGraphics(&g->gfx);
    ConstructTileMap(&g->tileMap, &g->gfx, 30, 30, 0, 0, "./TileMap.txt");
    ConstructPlayer(&g->player, &g->gfx);
    ConstructAnimal(&g->animal, &g->gfx);
    ConstructCamera(&g->cam, &g->gfx, &g->player.d.srcrect);

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
    //UpdateAnimal(&g->animal);
    UpdateCamera(&g->cam);
    SDL_Rect playerPos = {g->player.d.srcrect.x + 30, g->player.d.srcrect.y + 65, 15, 5};
    for(int i = 0; i < g->tileMap.nTiles_x * g->tileMap.nTiles_y; i++){
        if(SDL_HasIntersection(&playerPos, &g->tileMap.tiles[i].hitbox)){
            ChangeImagePath(&g->tileMap.tiles[i].d, "include/assets/grass.jpg");
        }
    }
}
void Render(Game *g){ 
    int nToRender = 0;
    for(int i = 0; i < g->tileMap.nTiles_x * g->tileMap.nTiles_y; i++){
        if(SDL_HasIntersection(&g->tileMap.tiles[i].d.srcrect, &g->cam.camRectVirtual)){
            AddToRenderList(g, &g->tileMap.tiles[i].d, &nToRender);
        }
    }
    AddToRenderList(g, &g->animal.d, &nToRender);
    AddToRenderList(g, &g->player.d, &nToRender);
    
    SortRenderList(g, &nToRender);
    RenderList(g, &nToRender);
}

void HandleEvents(Game* g){
    while(SDL_PollEvent(&g->event)){
        if(g->event.type == SDL_QUIT){
            *g->noExit = 0;
        }
    }
}

void AddToRenderList(Game* g, Drawable* d, int* nToRender){
    g->RenderList[*nToRender] = d;
    (*nToRender)++;
}
void RenderList(Game* g, int* nToRender){
    for(int i = 0; i < *nToRender; i++){
        CamDraw(&g->cam, *g->RenderList[i]);
    }
}
void SortRenderList(Game* g, int* nToRender){
    for (int i = 0; i < (*nToRender) - 1; ++i)
    {
        for (int j = 0; j < (*nToRender) - 1 - i; ++j )
        {
            if (g->RenderList[j]->z_index > g->RenderList[j+1]->z_index)
            {
                Drawable* temp = g->RenderList[j+1];
                g->RenderList[j+1] = g->RenderList[j];
                g->RenderList[j] = temp;
            }
        }
    }
}