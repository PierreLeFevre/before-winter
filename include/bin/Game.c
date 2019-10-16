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
    ConstructTileMap(&g->tileMap, &g->gfx, 60, 100, 0, 0, "./TileMap.csv");
    ConstructPlayer(&g->player, &g->gfx);
    ConstructCamera(&g->cam, &g->gfx, &g->player.ent.d.destrect, &g->tileMap);
    ConstructGui(&g->gui, &g->gfx, &g->player, &g->dateTime);
    ConstructTime(&g->dateTime, &g->tileMap);

    CreatePlantsToPlayer(g);

    //animal temp
    //ConstructAnimal(&g->animals[0], &g->gfx, DOGE, 15, 12);

    g->n_animals = 0;
    //for testing
    g->circel = 1;
    //---
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
    QuickSlotHandeling(&g->player);
    UpdateTime(SDL_GetTicks(), &g->dateTime);
    CalculateGoodTiles(g);
    HandleEvents(g);
    UpdatePlayer(&g->player);
    //A
    //B
    //C
    //D
    //E
    //F
    //G
    if (g->n_animals != 0)
    {
        for (int i = 0; i < g->n_animals; i++)
        {
            if (g->animals[i].animaltype == DOGE)
            {
                for (int j = 0; j <= g->nPlants; j++)
                {
                    if (g->plants[j].nPlantStages - 1 == g->plants[j].nToUpdate)
                    {
                        if (Dist(g->animals[i].ent.x_pos, g->animals[i].ent.y_pos, g->plants[j].TextureMap.destrect.x, g->plants[j].TextureMap.destrect.y) < 5 * 32)
                        {
                            g->animals[i].animalmood = Follow;
                        }
                    }
                }
            }
            UpdateAnimal(&g->animals[i]);
        }
    }
    if (!(g->gui.menuActive || (g->gui.shopActive || g->gui.invActive)))
    {
        CheckEntityCollision(&g->player.ent, g->GoodTiles, g->nGoodTiles);
        if (g->n_animals != 0)
        {
            for (int i = 0; i < g->n_animals; i++)
            {
                CheckEntityCollision(&g->animals[i].ent, g->GoodTiles, g->nGoodTiles);
            }
        }
    }
    //Temp
    g->animals[0].Follow_x = g->player.ent.hitbox.x - g->player.ent.hitbox.w / 2;
    g->animals[0].Follow_y = g->player.ent.hitbox.y - g->player.ent.hitbox.h / 2;

    g->animals[0].playerdirX = g->player.ent.x_dir;
    g->animals[0].playerdirY = g->player.ent.y_dir;
    g->cooldown++;
    if (EventHandler("SpawnAnimal="))
    {
        if (g->cooldown >= 200)
        {
            switch (g->circel)
            {
            case 1:
                ConstructAnimal(&g->animals[g->n_animals], &g->gfx, DOGE, g->player.ent.hitbox.x / TILE_WIDTH, g->player.ent.hitbox.y / TILE_HEIGHT);
                g->circel = 2;
                break;
            case 2:
                ConstructAnimal(&g->animals[g->n_animals], &g->gfx, Cow, g->player.ent.hitbox.x / TILE_WIDTH, g->player.ent.hitbox.y / TILE_HEIGHT);
                g->circel = 3;
                break;
            case 3:
                ConstructAnimal(&g->animals[g->n_animals], &g->gfx, Pig, g->player.ent.hitbox.x / TILE_WIDTH, g->player.ent.hitbox.y / TILE_HEIGHT);
                g->circel = 4;
                break;
            case 4:
                ConstructAnimal(&g->animals[g->n_animals], &g->gfx, Chicken, g->player.ent.hitbox.x / TILE_WIDTH, g->player.ent.hitbox.y / TILE_HEIGHT);
                g->circel = 1;
                break;
            }
            g->n_animals++;
            g->cooldown = 0;
        }
    }
    //Temp
    if (EventHandler("action="))
    {
        int planterror = 0;
        if (strstr(g->player.ent.items[g->player.activeItemIndex].Name, "Seed") != NULL || !strcmp(g->player.ent.items[g->player.activeItemIndex].Name, "Coffee Bean"))
        {
            if (g->player.ent.items[g->player.activeItemIndex].amount > 0)
            {
                PlantEnum p = ItemToPlant(&g->player.activeItem);
                if (p == StrawberryType && g->dateTime.season != Summer)
                { //Strawberries only in summer
                    planterror = 1;
                }
                if (p == CornType && g->dateTime.season != Spring)
                { //Corn only in spring
                    planterror = 1;
                }
                if (!planterror)
                {
                    if (TryPlacePlant(g, p))
                    {
                        g->player.ent.items[g->player.activeItemIndex].amount--;
                        if (g->player.ent.items[g->player.activeItemIndex].amount == 0)
                        {
                            g->player.ent.items[g->player.activeItemIndex].exists = 0;
                            for (int i = g->player.activeItemIndex; i < g->player.ent.n_items; i++)
                            { //REMOVE ITEM WHEN NONE LEFT
                                g->player.ent.items[i] = g->player.ent.items[i + 1];
                            }
                            g->player.ent.n_items--;
                        }
                    }
                }
                else
                {
                    AlertGui(&g->gui, 2, "Cannot plant right now");
                }
            }
        }
    }

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
        UpdatePlant(&g->plants[i], g->dateTime.BaseTick);
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
    if (g->n_animals != 0)
    {
        for (int i = 0; i < g->n_animals; i++)
        {
            AddToRenderList(g, &g->animals[i].ent.d);
        }
    }
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
    SDL_Rect animalhitbox = g->animals[0].ent.hitbox;
    animalhitbox.x -= g->cam.camRectVirtual.x;
    animalhitbox.y -= g->cam.camRectVirtual.y;
    SDL_RenderDrawRect(g->gfx.rend, &animalhitbox);

#endif
}

void HandleEvents(Game *g)
{

    while (SDL_PollEvent(&g->event))
    {
        if (g->event.type == SDL_QUIT /*|| g->gui.exitdata.exitInitialized*/)
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
        for (int j = 0; j < tile_overlay_types_enumsize; j++)
        {
            for (int k = 0; k < tile_overlay_enumsize; k++)
            {
                if (g->GoodTiles[i]->overlays_used[j][k])
                {
                    AddToRenderList(g, &g->GoodTiles[i]->overlays[j][k]);
                }
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
void CreatePlantsToPlayer(Game *g)
{
    SDL_Rect rect = {0, 0, TILE_WIDTH, TILE_HEIGHT};
    Plant p;
    CreatePlant(&p, &g->gfx, ParsnipType, rect, SDL_GetTicks(), g->player.ent.d.z_index - 1);
    g->player.ent.items[0] = p.SeedItems;
    g->player.ent.items[0].amount = 2;
    g->player.ent.items[0].exists = 1;
    strcpy(g->player.ent.items[0].Name, "Parsnip Seed");

    CreatePlant(&p, &g->gfx, TomatoType, rect, SDL_GetTicks(), g->player.ent.d.z_index - 1);
    g->player.ent.items[1] = p.SeedItems;
    g->player.ent.items[1].amount = 2;
    g->player.ent.items[1].exists = 1;
    strcpy(g->player.ent.items[1].Name, "Tomato Seed");

    CreatePlant(&p, &g->gfx, CauliflowerType, rect, SDL_GetTicks(), g->player.ent.d.z_index - 1);
    g->player.ent.items[2] = p.SeedItems;
    g->player.ent.items[2].amount = 2;
    g->player.ent.items[2].exists = 1;
    strcpy(g->player.ent.items[2].Name, "Cauliflower Seed");

    CreatePlant(&p, &g->gfx, GarlicType, rect, SDL_GetTicks(), g->player.ent.d.z_index - 1);
    g->player.ent.items[3] = p.SeedItems;
    g->player.ent.items[3].amount = 2;
    g->player.ent.items[3].exists = 1;
    strcpy(g->player.ent.items[3].Name, "Garlic Seed");

    CreatePlant(&p, &g->gfx, RhubarbType, rect, SDL_GetTicks(), g->player.ent.d.z_index - 1);
    g->player.ent.items[4] = p.SeedItems;
    g->player.ent.items[4].amount = 2;
    g->player.ent.items[4].exists = 1;
    strcpy(g->player.ent.items[4].Name, "Rhubarb Seed");

    CreatePlant(&p, &g->gfx, WheatType, rect, SDL_GetTicks(), g->player.ent.d.z_index - 1);
    g->player.ent.items[5] = p.SeedItems;
    g->player.ent.items[5].amount = 2;
    g->player.ent.items[5].exists = 1;
    strcpy(g->player.ent.items[5].Name, "Wheat Seed");

    CreatePlant(&p, &g->gfx, CornType, rect, SDL_GetTicks(), g->player.ent.d.z_index - 1);
    g->player.ent.items[6] = p.SeedItems;
    g->player.ent.items[6].amount = 2;
    g->player.ent.items[6].exists = 1;
    strcpy(g->player.ent.items[6].Name, "Corn Seed");

    CreatePlant(&p, &g->gfx, CoffeeBeanType, rect, SDL_GetTicks(), g->player.ent.d.z_index - 1);
    g->player.ent.items[7] = p.SeedItems;
    g->player.ent.items[7].amount = 2;
    g->player.ent.items[7].exists = 1;
    strcpy(g->player.ent.items[7].Name, "Coffee Bean");

    CreatePlant(&p, &g->gfx, StrawberryType, rect, SDL_GetTicks(), g->player.ent.d.z_index - 1);
    g->player.ent.items[8] = p.SeedItems;
    g->player.ent.items[8].amount = 2;
    g->player.ent.items[8].exists = 1;
    strcpy(g->player.ent.items[8].Name, "Strawberry Seed");

    g->player.ent.n_items = 9;
}
PlantEnum ItemToPlant(Item *i)
{
    if (strstr(i->Name, "Parsnip") != NULL)
    {
        return ParsnipType;
    }
    if (strstr(i->Name, "Cauliflower") != NULL)
    {
        return CauliflowerType;
    }
    if (strstr(i->Name, "Tomato") != NULL)
    {
        return TomatoType;
    }
    if (strstr(i->Name, "Garlic") != NULL)
    {
        return GarlicType;
    }
    if (strstr(i->Name, "Rhubarb") != NULL)
    {
        return RhubarbType;
    }
    if (strstr(i->Name, "Wheat") != NULL)
    {
        return WheatType;
    }
    if (strstr(i->Name, "Corn") != NULL)
    {
        return CornType;
    }
    if (strstr(i->Name, "Coffee Bean") != NULL)
    {
        return CoffeeBeanType;
    }
    if (strstr(i->Name, "Strawberry") != NULL)
    {
        return StrawberryType;
    }
    return 100;
}
//TMP
int TryPlacePlant(Game *g, PlantEnum plant)
{
    if (g->nPlants >= MAXPLANTS)
    {
        return 0;
    }
    for (int i = 0; i < g->nGoodTiles; i++)
    {
        if (SDL_HasIntersection(&g->player.ent.interaction_hitbox, &g->GoodTiles[i]->hitboxes[0]))
        {
            if (g->GoodTiles[i]->drawables[0].type != DT_Dirt)
            {
                return 0;
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
                CreatePlant(&g->plants[g->nPlants], &g->gfx, plant, g->GoodTiles[i]->drawables[0].destrect, g->dateTime.BaseTick, g->GoodTiles[i]->drawables[0].z_index + 4);
                g->nPlants++;
                return 1;
            }

            break;
        }
    }
    return 0;
}
void TryHarvestPlant(Game *g, Plant *plant)
{
    if (g->player.ent.n_items == INVENTORY_SIZE)
    {
        return;
    }
    if (plant->HasHarvestableBerries && plant->nPlantStages - 1 == plant->nToUpdate)
    { //to make index easier
        if (plant->nToUpdate == plant->nPlantStages - 1 && plant->HasHarvestableBerries && plant->TickToRegrow <= plant->TickSinceLastHarvested)
        {
            if (g->player.ent.n_items < INVENTORY_SIZE)
            {
                plant->GrownItems.exists = 1;
                plant->GrownItems.amount = 1;
                plant->TickAtHarvestation = g->dateTime.BaseTick;
                plant->nToUpdate++;
                g->player.ent.items[g->player.ent.n_items] = plant->GrownItems;
                g->player.ent.n_items++;
            }
        }
    }
    if (!plant->HasHarvestableBerries)
    {
        if (plant->nToUpdate == plant->nPlantStages)
        {
            if (g->player.ent.n_items < INVENTORY_SIZE)
            {
                plant->GrownItems.exists = 1;
                plant->GrownItems.amount = 1;
                g->player.ent.items[g->player.ent.n_items] = plant->GrownItems;
                g->player.ent.n_items++;
                DeletePlant(g, plant);
            }
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
void ChangeActiveItem(Player *player, int index)
{
    player->activeItem = player->ent.items[index];
    player->activeItemIndex = index;
}