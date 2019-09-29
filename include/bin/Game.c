#include "Game.h"
#include <stdio.h>
#include "FuncLib.h"
#include <string.h>

//#define DEBUG

void ConstructGame(Game *g, int *noExit)
{
    
    ConstructGraphics(&g->gfx);
    ConstructTileMap(&g->tileMap, &g->gfx, 30, 30, 0, 0, "./TileMap.txt");
    ConstructPlayer(&g->player, &g->gfx);
    ConstructCamera(&g->cam, &g->gfx, &g->player.ent.d.destrect);    
    ConstructGui(&g->gui, &g->gfx, &g->player);
    ConstructAnimal(&g->animals[0], &g->gfx,"./include/assets/cow_set.png");

    //TMP items*************
    CreateAllStandardItems(g);
    //TMP items****************

    g->RenderList = (Drawable**) malloc(sizeof(Drawable*) * 5000);
    g->GoodTiles = (Tile**) malloc(sizeof(Tile*) * 5000);
    g->noExit = noExit;
}
void DestroyGame(Game *g)
{
    free(g->RenderList);
    g->RenderList = NULL;
    free(g->GoodTiles);
    g->GoodTiles = NULL;
    DestroyTileMap(&g->tileMap);
    DestroyGraphics(&g->gfx);
}

void Go(Game *g)
{
    
    BeginFrame(&g->gfx);
    UpdateLogic(g);
    Render(g);
    EndFrame(&g->gfx);
}

void UpdateLogic(Game *g)
{
    CalculateGoodTiles(g);
    HandleEvents(g);
    UpdateAnimal(&g->animals[0]);
    UpdatePlayer(&g->player);
    //TEMP --
    const Uint8 *Keys = SDL_GetKeyboardState(NULL);
    //-------
    for(int i = 0; i < g->nGoodTiles; i++){
        CheckEntityCollision(&g->player.ent, g->GoodTiles[i]->hitboxes[1]);
        
        //TEMP -----
        if (Keys[SDL_SCANCODE_SPACE]) {
            if(SDL_HasIntersection(&g->player.ent.interaction_hitbox, &g->GoodTiles[i]->hitboxes[0]) ){
                if(!strcmp(g->GoodTiles[i]->ds[0].filePath, "include/assets/mud-new.jpg")){
                    ChangeImagePath(&g->GoodTiles[i]->ds[0], "include/assets/mud-new_seeded.jpg");
                }
            }
        }
        //-----------
    }

    g->BuyItemCooldown++;
    if (Keys[SDL_SCANCODE_Q] && g->BuyItemCooldown > 50){
        g->BuyItemCooldown = 0;
        BuyItem(&g->player.ent, &g->CoreItems[0]);

        char buffer[1000];
        sprintf(buffer, "Bought item: %s", g->CoreItems[0].Name);
        guiPingToggler(&g->gui, 3, buffer);
    }
    if (Keys[SDL_SCANCODE_R] && g->BuyItemCooldown > 50){
        g->BuyItemCooldown = 0;
        BuyItem(&g->player.ent, &g->CoreItems[1]);

        char buffer[1000];
        sprintf(buffer, "Bought item: %s", g->CoreItems[1].Name);
        guiPingToggler(&g->gui, 3, buffer);

    }
    if (Keys[SDL_SCANCODE_T] && g->BuyItemCooldown > 50){
        g->BuyItemCooldown = 0;
        BuyItem(&g->player.ent, &g->CoreItems[2]);

        char buffer[1000];
        sprintf(buffer, "Bought item: %s", g->CoreItems[2].Name);
        guiPingToggler(&g->gui, 3, buffer);
    }

    //DISPLAY ITEMS****************************
    if (Keys[SDL_SCANCODE_1]){
        g->player.ent.items[0].d.destrect.x = g->player.activeItem.d.destrect.x;
        g->player.ent.items[0].d.destrect.y = g->player.activeItem.d.destrect.y;
        g->player.activeItem = g->player.ent.items[0];
        g->player.activeItemIndex = 0;
    }
    if (Keys[SDL_SCANCODE_2]){
        g->player.ent.items[1].d.destrect.x = g->player.activeItem.d.destrect.x;
        g->player.ent.items[1].d.destrect.y = g->player.activeItem.d.destrect.y;
        g->player.activeItem = g->player.ent.items[1];
        g->player.activeItemIndex = 1;
    }
    if (Keys[SDL_SCANCODE_3]){
        g->player.ent.items[2].d.destrect.x = g->player.activeItem.d.destrect.x;
        g->player.ent.items[2].d.destrect.y = g->player.activeItem.d.destrect.y;
        g->player.activeItem = g->player.ent.items[2];
        g->player.activeItemIndex = 2;
    }
    //DISPLAY ITEMS****************************
    for(int i; i < g->n_animals;i++){
        EntityDeathEvent(g, &g->animals[i].ent);
    }
    UpdateCamera(&g->cam);
}

void Render(Game *g)
{
    g->nToRender = 0;
    AddTileMapToRenderList(g);
    AddToRenderList(g, &g->player.ent.d);
    AddToRenderList(g, &g->animals[0].ent.d);

    AddToRenderList(g, &g->player.activeItem.d);

    SortRenderList(g);

    RenderList(g);
    UpdateGui(&g->gui);
    
    SDL_Rect playerHitbox = g->player.ent.hitbox;
    playerHitbox.x -= g->cam.camRectVirtual.x;
    playerHitbox.y -= g->cam.camRectVirtual.y;
    SDL_RenderDrawRect(g->gfx.rend, &playerHitbox);
    SDL_Rect playerInteractionHitbox = g->player.ent.interaction_hitbox;
    playerInteractionHitbox.x -= g->cam.camRectVirtual.x;
    playerInteractionHitbox.y -= g->cam.camRectVirtual.y;
    SDL_RenderDrawRect(g->gfx.rend, &playerInteractionHitbox);
    for(int i = 0; i < g->nGoodTiles; i++){
        SDL_Rect treeHitbox = g->GoodTiles[i]->hitboxes[1];
        treeHitbox.x -= g->cam.camRectVirtual.x;
        treeHitbox.y -= g->cam.camRectVirtual.y;
        SDL_RenderDrawRect(g->gfx.rend, &treeHitbox);
    }
    #ifdef DEBUG
    
    #endif
}

void HandleEvents(Game *g)
{
    while (SDL_PollEvent(&g->event))
    {
        if (g->event.type == SDL_QUIT)
        {
            *g->noExit = 0;
        }
    }
}

void CalculateGoodTiles(Game *g)
{
    g->nGoodTiles = 0;
    for (int i = 0; i < g->tileMap.nTiles_x * g->tileMap.nTiles_y; i++)
    {
        SDL_Rect currTile = g->tileMap.tiles[i].ds[0].destrect;
        SDL_Rect camera = g->cam.camRectVirtual;
        if (currTile.x > camera.x + camera.w + TILE_WIDTH * 2)
        {
            i += (int)(abs(currTile.x - (g->tileMap.nTiles_x * TILE_WIDTH)) / TILE_WIDTH) - 1;
            continue;
        }
        if (currTile.x + currTile.w < camera.x - TILE_WIDTH * 2)
        {
            i += (int)(abs((currTile.x + currTile.w) - (camera.x - TILE_WIDTH * 2)) / TILE_WIDTH);
            continue;
        }
        if (currTile.y + currTile.h < camera.y - TILE_HEIGHT * 2)
        {
            i += (int)(abs(g->tileMap.nTiles_x * TILE_WIDTH) / TILE_WIDTH);
            continue;
        }
        if (currTile.y > camera.y + camera.h + TILE_HEIGHT * 2)
        {
            break;
        };
        for (int j = 0; j < g->tileMap.tiles[i].currentDrawables; j++)
        {
            if (SDL_HasIntersection(&g->tileMap.tiles[i].ds[j].destrect, &g->cam.camRectVirtual))
            {
                g->GoodTiles[g->nGoodTiles] = &g->tileMap.tiles[i];
                g->nGoodTiles++;
                break;
            }
        }
    }
}

void AddToRenderList(Game *g, Drawable *d)
{
    g->RenderList[g->nToRender] = d;
    g->nToRender++;
}
void AddTileMapToRenderList(Game *g)
{
    for (int i = 0; i < g->nGoodTiles; i++)
    {
        for (int j = 0; j < g->GoodTiles[i]->currentDrawables; j++)
        {
            AddToRenderList(g, &g->GoodTiles[i]->ds[j]);
        }
    }
}
void RenderList(Game *g)
{
    for (int i = 0; i < g->nToRender; i++)
    {
        CamDraw(&g->cam, *g->RenderList[i]);
    }
}
void SortRenderList(Game *g)
{
    for (int i = 0; i < g->nToRender - 1; ++i)
    {
        for (int j = 0; j < g->nToRender - 1 - i; ++j)
        {
            if (g->RenderList[j]->z_index > g->RenderList[j + 1]->z_index)
            {
                Drawable *temp = g->RenderList[j + 1];
                g->RenderList[j + 1] = g->RenderList[j];
                g->RenderList[j] = temp;
            }
        }
    }
}
void CreateAllStandardItems(Game *g){
    CreateItem(&g->CoreItems[0], &g->gfx, IronPickaxeEnum);
    CreateItem(&g->CoreItems[1], &g->gfx, IronAxeEnum);
    CreateItem(&g->CoreItems[2], &g->gfx, IronSwordEnum);
}
void EntityDeathEvent(Game *g, Entity *e){
    if (e->health <= 0 && !e->deadTrigger){
        e->deadTrigger = SDL_TRUE;
        //***********DEATH***************
        e->droppableItem.d.destrect.x = e->d.destrect.x;
        e->droppableItem.d.destrect.y = e->d.destrect.y;
        AddToRenderList(g, &e->droppableItem.d);
    }
}