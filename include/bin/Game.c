#include "Game.h"
#include <stdio.h>
#include "FuncLib.h"

void ConstructGame(Game *g, int* noExit){
    
    ConstructGraphics(&g->gfx);
    ConstructTileMap(&g->tileMap, &g->gfx, 30, 30, 0, 0, "./TileMap.txt");
    ConstructPlayer(&g->player, &g->gfx);
    ConstructCamera(&g->cam, &g->gfx, &g->player.d.srcrect);
    //printf("THE THICK BOI x:%d y:%d w:%d h:%d\n", g->player.hitbox.x, g->player.hitbox.y, g->player.hitbox.w, g->player.hitbox.h);

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
    UpdateEntity(&g->entities[0]);
    UpdateCamera(&g->cam);
    
    //TEMP
    if(SDL_HasIntersection(&g->player.hitbox, &g->tileMap.tiles[154].hitboxes[1])){
        printf("HIT A TREE!\n");
    }
}
void Render(Game *g){ 
    g->nToRender = 0;
    AddTileMapToRenderList(g);
    AddToRenderList(g, &g->player.d);
    
    SortRenderList(g);
    RenderList(g);

    //TEMP
    SDL_Rect playerHitbox = g->player.hitbox;
    playerHitbox.x -= g->cam.camRectVirtual.x;
    playerHitbox.y -= g->cam.camRectVirtual.y;
    SDL_Rect treeHitbox = g->tileMap.tiles[154].hitboxes[1];
    treeHitbox.x -= g->cam.camRectVirtual.x;
    treeHitbox.y -= g->cam.camRectVirtual.y;
    SDL_RenderDrawRect(g->tileMap.gfx->rend, &playerHitbox);
    SDL_RenderDrawRect(g->tileMap.gfx->rend, &treeHitbox);
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