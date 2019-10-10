#include "Game.h"
#include <stdio.h>
#include "FuncLib.h"
#include <string.h>
#include <stdlib.h>

//#define DEBUG
//#define HarvestDebug

void ConstructGame(Game *g, int *noExit)
{
    ConstructGraphics(&g->gfx);
    ConstructTileMap(&g->tileMap, &g->gfx, 60, 60, 0, 0, "./TileMap.txt");
    ConstructPlayer(&g->player, &g->gfx);
    ConstructCamera(&g->cam, &g->gfx, &g->player.ent.d.destrect, &g->tileMap);
    ConstructGui(&g->gui, &g->gfx, &g->player, &g->dateTime);
    ConstructTime(&g->dateTime, &g->tileMap);
    g->nDroppedItems = 0;
    g->droppedItems = (DroppedItem **)malloc(sizeof(DroppedItem *) * 5000);
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
    free(g->droppedItems);
    g->droppedItems = NULL;
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
    if (!(g->gui.menuActive || g->gui.shopActive))
    {
        CheckEntityCollision(&g->player.ent, g->GoodTiles, g->nGoodTiles);
    }
    
    
    if (EventHandler("action="))
    {
        TryPlacePlant(g, TomatoType);
    }
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
#ifdef HarvestDebug
    for (int i = 0; i < g->nDroppedItems; i++)
    {
        if (g->droppedItems[i]->exists == 0)
        {
            g->droppedItems[i] = g->droppedItems[i + 1];
            g->nDroppedItems--;
        }
        else
        {
            UpdateDroppedItem(g->droppedItems[i], &g->player);
        }
    }
#endif
    UpdateCamera(&g->cam);
}

void Render(Game *g)
{
    g->nToRender = 0;
    AddTileMapToRenderList(g);
    AddToRenderList(g, &g->player.ent.d);

    AddToRenderList(g, &g->player.activeItem.d);
    AddToRenderList(g, &g->player.ent.droppableItem.d);

#ifdef HarvestDebug
    for (int i = 0; i < g->nDroppedItems; i++)
    {
        AddToRenderList(g, &g->droppedItems[i]->ent->d);
    }
#endif

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
    //int tilesOutsideScreen_x = 5;
    int tilesOutsideScreen_y = 5;
    g->nGoodTiles = 0;
    for (int i = 0; i < g->tileMap.nTiles_x * g->tileMap.nTiles_y; i++)
    {
        SDL_Rect currTile = g->tileMap.tiles[i].drawables[0].destrect;
        SDL_Rect camera = g->cam.camRectVirtual;
        // NOT WORKING
        // if (currTile.x > camera.x + camera.w + TILE_WIDTH * tilesOutsideScreen_x)
        // {
        //     i += (int)(abs(currTile.x - (g->tileMap.nTiles_x * TILE_WIDTH)) / TILE_WIDTH) - 1;
        //     continue;
        // }
        // if (currTile.x + currTile.w < camera.x - TILE_WIDTH * tilesOutsideScreen_x)
        // {
        //     i += (int)(abs((currTile.x + currTile.w) - (camera.x - TILE_WIDTH * 2)) / TILE_WIDTH);
        //     continue;
        // }
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
        for (int j = 0; j < tile_overlay_enumsize; j++)
        {
            if (g->GoodTiles[i]->overlays_used[j])
            {
                AddToRenderList(g, &g->GoodTiles[i]->overlays[j]);
            }
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
    DrawableMergeSort(g->RenderList, 0, g->nToRender - 1);
}
void CreateAllStandardItems(Game *g)
{
    CreateItem(&g->CoreItems[1], &g->gfx, IronAxeEnum);
    // CreateItem(&g->CoreItems[0], &g->gfx, IronPickaxeEnum);
    // CreateItem(&g->CoreItems[2], &g->gfx, IronSwordEnum);
    // CreateItem(&g->CoreItems[3], &g->gfx, DiamondEnum);
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
            if (g->GoodTiles[i]->drawables[0].type != DT_Dirt)
            {
                return;
            }
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
                CreatePlant(&g->plants[g->nPlants], &g->gfx, plant, g->GoodTiles[i]->drawables[0].destrect, SDL_GetTicks(), g->GoodTiles[i]->drawables[0].z_index + 2);
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
    if (plant->HasHarvestableBerries && plant->nToUpdate == plant->nPlantStages - 2)
    { //to make index easier
        if (g->player.ent.n_items < INVENTORY_SIZE)
        {
            plant->TickAtHarvestation = SDL_GetTicks();
            plant->nToUpdate++;
            g->player.ent.items[g->player.ent.n_items] = plant->GrownItems;
            g->player.ent.n_items++;
        }
    }
    if (!plant->HasHarvestableBerries)
    {
        if (plant->plantStages[plant->nPlantStages].GrowTick <= SDL_GetTicks() - plant->TickPlaced)
        {
//DELETE PLANT
//PROCC DROPPED ITEMS ON
#ifdef HarvestDebug
            // if (g->nDroppedItems == 0){
            Entity e;
            ConstructEntity(&e, &plant->GrownItems.d);
            ConstructDroppedItem(g->droppedItems[g->nDroppedItems], &plant->GrownItems, &e);
            g->nDroppedItems++;
            DeletePlant(g, plant);
// }
#endif

#ifndef HarvestDebug
#define HarvestDebug
            if (g->player.ent.n_items < INVENTORY_SIZE)
            {
                plant->GrownItems.exists = 1;
                plant->GrownItems.amount = 1;
                g->player.ent.items[g->player.ent.n_items] = plant->GrownItems;
                g->player.ent.n_items++;
                DeletePlant(g, plant);
            }
#endif
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

void DrawableMerge(Drawable *DrawablesCurrentSort[], int l, int m, int r)
{
    int i, j, k;        // left_index, right_index and merged_index
    int n1 = m - l + 1; // N elements in left sub-array
    int n2 = r - m;     // N elements in right sub-array

    // create temp sub-arrays for left and right side
    Drawable **DrawablesToSort_L;
    DrawablesToSort_L = (Drawable **)malloc(sizeof(Drawable *) * n1);
    Drawable **DrawablesToSort_R;
    DrawablesToSort_R = (Drawable **)malloc(sizeof(Drawable *) * n2);

    // copy data to temp vectors currSort_L and currSort_R
    for (i = 0; i < n1; i++)
    {
        DrawablesToSort_L[i] = DrawablesCurrentSort[l + i];
    }

    for (j = 0; j < n2; j++)
    {
        DrawablesToSort_R[j] = DrawablesCurrentSort[m + 1 + j];
    }

    // merge the temp temp sub-arrays back into DrawablesCurrentSort
    // indicies to start with
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (DrawablesToSort_L[i]->z_index <= DrawablesToSort_R[j]->z_index)
        {
            DrawablesCurrentSort[k] = DrawablesToSort_L[i];
            i++;
        }
        else
        {
            DrawablesCurrentSort[k] = DrawablesToSort_R[j];
            j++;
        }
        k++;
    }

    // copy the left-over elements of DrawablesToSort_L, should there be any...
    while (i < n1)
    {
        DrawablesCurrentSort[k] = DrawablesToSort_L[i];
        i++;
        k++;
    }

    // copy the left-over elements of DrawablesToSort_R, should there be any...
    while (j < n2)
    {
        DrawablesCurrentSort[k] = DrawablesToSort_R[j];
        j++;
        k++;
    }
    free(DrawablesToSort_L);
    free(DrawablesToSort_R);
}

void DrawableMergeSort(Drawable *DrawablesCurrentSort[], int l, int r)
{
    //  l = first index      r = last index
    // "If size of DrawablesCurrentSort is two or larger"
    // "If not, algorithm is at the bottom of the merge-chain
    if (l < r)
    {
        //m = middle
        int m = l + (r - l) / 2;

        // Sort first and second halves, recursively
        DrawableMergeSort(DrawablesCurrentSort, l, m);
        DrawableMergeSort(DrawablesCurrentSort, m + 1, r);

        DrawableMerge(DrawablesCurrentSort, l, m, r);
    }
}