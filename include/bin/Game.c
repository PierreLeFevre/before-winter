#include "Game.h"
#include <stdio.h>
#include "FuncLib.h"

void ConstructGame(Game *g, int* noExit){    
    ConstructGraphics(&g->gfx);
    ConstructTileMap(&g->tileMap, &g->gfx, 30, 30, 0, 0, "./TileMap.txt");
    ConstructPlayer(&g->player, &g->gfx);
    ConstructCamera(&g->cam, &g->gfx, &g->player.d.srcrect);    
    ConstructEntity(&g->entities[0], &g->gfx, "./include/assets/cow_set.png");
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
    CalculateGoodTiles(g);
    HandleEvents(g);
    UpdateEntity(&g->entities[0]);    
    UpdatePlayer(&g->player);
    UpdateCamera(&g->cam);
    
    //TEMP ---------------------------
    if(SDL_HasIntersection(&g->player.hitbox, &g->tileMap.tiles[154].hitboxes[1])){
        printf("HIT A TREE!\n");
    }
    //TEMP ---------------------------
}
void Render(Game *g){ 
    g->nToRender = 0;
    AddTileMapToRenderList(g);
    AddToRenderList(g, &g->player.d);
    AddToRenderList(g, &g->entities[0].d);
    
    SortRenderList(g);
    RenderList(g);

    //TEMP ---------------------------
    SDL_Rect playerHitbox = g->player.hitbox;
    playerHitbox.x -= g->cam.camRectVirtual.x;
    playerHitbox.y -= g->cam.camRectVirtual.y;
    SDL_Rect treeHitbox = g->tileMap.tiles[154].hitboxes[1];
    treeHitbox.x -= g->cam.camRectVirtual.x;
    treeHitbox.y -= g->cam.camRectVirtual.y;
    SDL_RenderDrawRect(g->tileMap.gfx->rend, &playerHitbox);
    SDL_RenderDrawRect(g->tileMap.gfx->rend, &treeHitbox);
    //TEMP ---------------------------
}

void HandleEvents(Game* g){
    while(SDL_PollEvent(&g->event)){
        if(g->event.type == SDL_QUIT){
            *g->noExit = 0;
        }
    }
}

void CalculateGoodTiles(Game* g){
    g->nGoodTiles = 0;
    for(int i = 0; i < g->tileMap.nTiles_x * g->tileMap.nTiles_y; i++){
        SDL_Rect currTile = g->tileMap.tiles[i].ds[0].srcrect;
        SDL_Rect camera = g->cam.camRectVirtual;
        if(currTile.x > camera.x + camera.w + TILE_WIDTH * 2){
            i += (int)(abs(currTile.x-(g->tileMap.nTiles_x * TILE_WIDTH)) / TILE_WIDTH) - 1;
            continue;
        }
        if(currTile.x + currTile.w < camera.x - TILE_WIDTH * 2){
            i += (int)(abs((currTile.x + currTile.w)-(camera.x - TILE_WIDTH * 2)) / TILE_WIDTH);
            continue;
        }
        if(currTile.y + currTile.h < camera.y - TILE_HEIGHT * 2){
            i += (int)(abs(g->tileMap.nTiles_x * TILE_WIDTH) / TILE_WIDTH);
            continue;
        }
        if(currTile.y > camera.y + camera.h + TILE_HEIGHT * 2){
            break;
        };
        for(int j = 0; j < g->tileMap.tiles[i].currentDrawables; j++){
            if(SDL_HasIntersection(&g->tileMap.tiles[i].ds[j].srcrect, &g->cam.camRectVirtual)){
                g->GoodTiles[g->nGoodTiles] = &g->tileMap.tiles[i];
                g->nGoodTiles++;
                break;
            }
        }
    }
}


void AddToRenderList(Game* g, Drawable* d){
    g->RenderList[g->nToRender] = d;
    g->nToRender++;
}
void AddTileMapToRenderList(Game* g){
    for(int i = 0; i < g->nGoodTiles; i++){
        for(int j = 0; j < g->GoodTiles[i]->currentDrawables; j++){
            AddToRenderList(g, &g->GoodTiles[i]->ds[j]);
        }
    }
}
void RenderList(Game* g){
    for(int i = 0; i < g->nToRender; i++){
        CamDraw(&g->cam, *g->RenderList[i]);
    }
}
void SortRenderList(Game* g){
    for (int i = 0; i < g->nToRender - 1; ++i)
    {
        for (int j = 0; j < g->nToRender - 1 - i; ++j )
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