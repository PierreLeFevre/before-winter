#include "Game.h"
#include <stdio.h>
#include "FuncLib.h"
#include <string.h>
#include <stdlib.h>

//#define DEBUG

void ConstructGame(Game *g, int *noExit)
{
    Entity buildEntity;
    Drawable buildDrawable;
    SDL_Rect buildSrcrect = {272, 416, 16, 16};
    SDL_Rect buildDestrect = {300, 300, 16, 16};
    ConstructGraphics(&g->gfx);
    ConstructTileMap(&g->tileMap, &g->gfx, 60, 60, 0, 0, "./TileMap.txt");
    ConstructPlayer(&g->player, &g->gfx);
    ConstructCamera(&g->cam, &g->gfx, &g->player.ent.d.destrect);
    ConstructGui(&g->gui, &g->gfx, &g->player);

    ConstructDrawable(&buildDrawable, DT_Other, &g->gfx, SS_ITEM, buildSrcrect, buildDestrect, 10000);
    ConstructItem(&g->item, &buildDrawable);
    ConstructEntity(&buildEntity, &buildDrawable);
    ConstructDroppedItem(&g->d_item, &g->item, &buildEntity);
    ConstructTime(&g->dateTime);

    g->RenderList = (Drawable **)malloc(sizeof(Drawable *) * 5000);
    g->GoodTiles = (Tile **)malloc(sizeof(Tile *) * 5000);
    g->nPlants = 0;
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
    UpdateTime(SDL_GetTicks(), &g->dateTime);

    CalculateGoodTiles(g);
    HandleEvents(g);
    UpdatePlayer(&g->player);
    if (!g->gui.menuActive)
    {
        CheckEntityCollision(&g->player.ent, g->GoodTiles, g->nGoodTiles);
    }
    if (EventHandler("action="))
    {
        TryPlacePlant(g, ParsnipType);
    }
    g->BuyItemCooldown++;
    if (EventHandler("testkey=") && g->BuyItemCooldown > 50)
    {
        g->BuyItemCooldown = 0;
        if (BuyItem(&g->player.ent, &g->CoreItems[0]))
        {
            char buffer[1000];
            sprintf(buffer, "Bought item: %s", g->CoreItems[0].Name);
            AlertGui(&g->gui, 2, buffer);
        }
    }
    if (EventHandler("buyitem1=") && g->BuyItemCooldown > 50)
    {
        g->BuyItemCooldown = 0;
        if (BuyItem(&g->player.ent, &g->CoreItems[1]))
        {
            char buffer[1000];
            sprintf(buffer, "Bought item: %s", g->CoreItems[1].Name);
            AlertGui(&g->gui, 2, buffer);
        }
    }
    if (EventHandler("buyitem2=") && g->BuyItemCooldown > 50)
    {
        g->BuyItemCooldown = 0;
        if (BuyItem(&g->player.ent, &g->CoreItems[2]))
        {
            char buffer[1000];
            sprintf(buffer, "Bought item: %s", g->CoreItems[2].Name);
            AlertGui(&g->gui, 2, buffer);
        }
    }

    //DISPLAY ITEMS****************************
    if (EventHandler("quickSlot1="))
    {
        g->player.ent.items[0].d.destrect.x = g->player.activeItem.d.destrect.x;
        g->player.ent.items[0].d.destrect.y = g->player.activeItem.d.destrect.y;
        g->player.activeItem = g->player.ent.items[0];
        g->player.activeItemIndex = 0;
    }
    if (EventHandler("quickSlot2="))
    {
        g->player.ent.items[1].d.destrect.x = g->player.activeItem.d.destrect.x;
        g->player.ent.items[1].d.destrect.y = g->player.activeItem.d.destrect.y;
        g->player.activeItem = g->player.ent.items[1];
        g->player.activeItemIndex = 1;
    }
    if (EventHandler("quickSlot3="))
    {
        g->player.ent.items[2].d.destrect.x = g->player.activeItem.d.destrect.x;
        g->player.ent.items[2].d.destrect.y = g->player.activeItem.d.destrect.y;
        g->player.activeItem = g->player.ent.items[2];
        g->player.activeItemIndex = 2;
    }
    //DISPLAY ITEMS****************************
    EntityDeathEvent(g, &g->player.ent);

    if (EventHandler("harvestTemp="))
    {
        for (int i = 0; i < g->nPlants; i++)
        {
            if (SDL_HasIntersection(&g->player.ent.interaction_hitbox, &g->plants[i].TextureMap.destrect))
            {
                TryHarvestPlant(g, &g->plants[i]);
                break;
            }
        }
    }
    for (int i = 0; i < g->nPlants; i++)
    {
        UpdatePlant(&g->plants[i], SDL_GetTicks());
    }
    //TEMP
    UpdateDroppedItem(&g->d_item, &g->player);
    //----
    UpdateCamera(&g->cam);
}

void Render(Game *g)
{
    g->nToRender = 0;
    AddTileMapToRenderList(g);
    AddToRenderList(g, &g->player.ent.d);

    AddToRenderList(g, &g->player.activeItem.d);
    AddToRenderList(g, &g->player.ent.droppableItem.d);
    AddToRenderList(g, &g->d_item.ent.d);

    for (int i = 0; i < g->nPlants; i++)
    {
        AddToRenderList(g, &g->plants[i].TextureMap);
    }

    SortRenderList(g);
    RenderList(g);

    UpdateGui(&g->gui);

#ifdef DEBUG
    SDL_Rect playerHitbox = g->player.ent.hitbox;
    playerHitbox.x -= g->cam.camRectVirtual.x;
    playerHitbox.y -= g->cam.camRectVirtual.y;
    SDL_RenderDrawRect(g->gfx.rend, &playerHitbox);
    SDL_Rect playerInteractionHitbox = g->player.ent.interaction_hitbox;
    playerInteractionHitbox.x -= g->cam.camRectVirtual.x;
    playerInteractionHitbox.y -= g->cam.camRectVirtual.y;
    SDL_RenderDrawRect(g->gfx.rend, &playerInteractionHitbox);
    for (int i = 0; i < g->nGoodTiles; i++)
    {
        SDL_Rect treeHitbox = g->GoodTiles[i]->hitboxes[1];
        treeHitbox.x -= g->cam.camRectVirtual.x;
        treeHitbox.y -= g->cam.camRectVirtual.y;
        SDL_RenderDrawRect(g->gfx.rend, &treeHitbox);
    }
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
    int tilesOutsideScreen_y = 5;
    int tilesOutsideScreen_x = 3;
    g->nGoodTiles = 0;
    for (int i = 0; i < g->tileMap.nTiles_x * g->tileMap.nTiles_y; i++)
    {
        SDL_Rect currTile = g->tileMap.tiles[i].drawables[0].destrect;
        SDL_Rect camera = g->cam.camRectVirtual;
        if (currTile.x > camera.x + camera.w + TILE_WIDTH * tilesOutsideScreen_x)
        {
            i += (int)(abs(currTile.x - (g->tileMap.nTiles_x * TILE_WIDTH)) / TILE_WIDTH) - 1;
            continue;
        }
        if (currTile.x + currTile.w < camera.x - TILE_WIDTH * tilesOutsideScreen_x)
        {
            i += (int)(abs((currTile.x + currTile.w) - (camera.x - TILE_WIDTH * 2)) / TILE_WIDTH);
            continue;
        }
        if (currTile.y + currTile.h < camera.y - TILE_HEIGHT * tilesOutsideScreen_y)
        {
            i += (int)(abs(g->tileMap.nTiles_x * TILE_WIDTH) / TILE_WIDTH);
            continue;
        }
        if (currTile.y > camera.y + camera.h + TILE_HEIGHT * tilesOutsideScreen_y)
        {
            break;
        };
        for (int j = 0; j < g->tileMap.tiles[i].currentSpriteAmmount; j++)
        {
            if (SDL_HasIntersection(&g->tileMap.tiles[i].drawables[j].destrect, &g->cam.camRectVirtual))
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
        for (int j = 0; j < g->GoodTiles[i]->currentSpriteAmmount; j++)
        {
            AddToRenderList(g, &g->GoodTiles[i]->drawables[j]);
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
void CreateAllStandardItems(Game *g)
{
    CreateItem(&g->CoreItems[0], &g->gfx, IronPickaxeEnum);
    CreateItem(&g->CoreItems[1], &g->gfx, IronAxeEnum);
    CreateItem(&g->CoreItems[2], &g->gfx, IronSwordEnum);
    CreateItem(&g->CoreItems[3], &g->gfx, DiamondEnum);
}
void EntityDeathEvent(Game *g, Entity *e)
{
    if (e->health <= 0 && e->deadTrigger == SDL_FALSE)
    {
        e->deadTrigger = SDL_TRUE;
        //***********DEATH***************
        e->droppableItem = g->CoreItems[3];
        e->droppableItem.d.z_index = e->d.z_index;
        e->droppableItem.d.destrect.x = e->d.destrect.x;
        e->droppableItem.d.destrect.y = e->d.destrect.y;
    }
}

void TryPlacePlant(Game *g, PlantEnum plant)
{
    if (g->nPlants >= MAXPLANTS)
    {
        return;
    }
    for (int i = 0; i < g->nGoodTiles; i++)
    {
        if (SDL_HasIntersection(&g->player.ent.interaction_hitbox, &g->GoodTiles[i]->hitboxes[0]))
        {
            int found = 0;
            for (int j = 0; j < g->nPlants; j++)
            {
                if (SDL_HasIntersection(&g->player.ent.interaction_hitbox, &g->plants[j].TextureMap.destrect))
                {
                    found++;
                    break;
                }
            }
            if (found == 0)
            {
                CreatePlant(&g->plants[g->nPlants], &g->gfx, plant, g->GoodTiles[i]->drawables[0].destrect, SDL_GetTicks(), g->GoodTiles[i]->drawables[0].z_index + 1);
                g->nPlants++;
            }
            break;
        }
    }
}
void TryHarvestPlant(Game *g, Plant *plant)
{
    if (g->player.ent.n_items == INVENTORY_SIZE)
    {
        return;
    }
    if (!plant->HasHarvestableBerries || plant->TickToRegrow > plant->TickSinceLastHarvested)
    {
    }
    else
    {
        if (plant->nPlantStages - 1 == plant->nToUpdate)
        {
            plant->TickAtHarvestation = SDL_GetTicks();
            plant->nToUpdate++;

            g->player.ent.items[g->player.ent.n_items] = plant->GrownItems;
            g->player.ent.n_items++;
        }
        return;
    }
    if (!plant->HasHarvestableBerries)
    {
        if (plant->plantStages[plant->nPlantStages].GrowTick <= SDL_GetTicks() - plant->TickPlaced)
        {
            //DELETE PLANT
            //PROCC DROPPED ITEMS ON
            g->player.ent.items[g->player.ent.n_items] = plant->GrownItems;
            g->player.ent.n_items++;
            DeletePlant(g, plant);
        }
    }
}
void DeletePlant(Game *g, Plant *plant)
{
    for (int i = 0; g->nPlants; i++)
    {
        if (SDL_HasIntersection(&g->plants[i].TextureMap.destrect, &plant->TextureMap.destrect))
        {
            for (int j = i; j < g->nPlants; j++)
            {
                g->plants[j] = g->plants[j + 1];
            }
            g->nPlants--;
            break;
        }
    }
}