#include "Entity.h"
#include <stdio.h>
#include "FuncLib.h"
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
void ConstructEntity(Entity *e, Graphics *gfx, SDL_Rect destrect, char *filePath)
{
    e->interaction_hitbox_size = 10;
    e->interaction_hitbox_offset = 25;
    e->x_pos = destrect.x;
    e->y_pos = destrect.y;
    ConstructDrawable(&e->d, gfx, filePath, destrect, 0);
    e->deadTrigger = SDL_FALSE;
}
void UpdateEntity(Entity *e)
{
    MoveEntity(e);
    e->d.z_index = ((e->d.destrect.y + e->d.destrect.h) / TILE_HEIGHT) * TILE_Z_INDEX_MAX + Map((e->d.destrect.y + e->d.destrect.h) % TILE_HEIGHT, 0, TILE_HEIGHT, 0, TILE_Z_INDEX_MAX); //Row 1 = 15, Row 2 = 25....
}

void MoveEntity(Entity *e)
{
    e->x_axis += e->accaleration * e->x_dir;
    e->y_axis += e->accaleration * e->y_dir;
    e->x_axis -= min(e->friction, abs((int)e->x_axis)) * sign(e->x_axis) * (e->x_dir == 0);
    e->y_axis -= min(e->friction, abs((int)e->y_axis)) * sign(e->y_axis) * (e->y_dir == 0);

    e->x_axis = min(abs((int)e->x_axis), e->movement_speed) * sign(e->x_axis);
    e->y_axis = min(abs((int)e->y_axis), e->movement_speed) * sign(e->y_axis);
    // if (e->x_axis != 0 && e->y_axis != 0)
    // {
    //     e->x_axis *= sq2;
    //     e->y_axis *= sq2;
    // }
    if (e->x_dir != 0 || e->y_dir != 0)
    {
        e->x_face = e->x_dir;
        e->y_face = e->y_dir;
        if (e->x_dir != 0 && e->y_dir != 0)
        {
            e->y_face = 0;
        }
    }
}

void CheckEntityCollision(Entity *e, Tile *GoodTiles[], int max)
{
    int pre_colision[2] = {0, 0};
    for (int i = 0; i < max; i++)
    {
        if (Pre_X_CheckCollision(e->hitbox, GoodTiles[i]->hitboxes[1], e->x_axis))
        {
            pre_colision[0] = 1;
        }
        if (Pre_Y_CheckCollision(e->hitbox, GoodTiles[i]->hitboxes[1], e->y_axis))
        {
            pre_colision[1] = 1;
        }
    }

    if ((abs((int)e->x_axis) <= 0.6f))
    {
        e->x_axis = 0;
    }
    if ((abs((int)e->y_axis) <= 0.6f))
    {
        e->y_axis = 0;
    }
    if (pre_colision[0] == 0 && pre_colision[1] == 0)
    {
        e->x_pos += e->x_axis;
        e->y_pos += e->y_axis;
        e->d.destrect.x = (e->x_pos + 0.5f);
        e->d.destrect.y = (e->y_pos + 0.5f);
    }
    else
    {
        if (pre_colision[0] == 1)
        {
            e->y_pos += e->y_axis;
            e->x_pos -= e->x_axis;
        }
        if (pre_colision[1] == 1)
        {
            e->x_pos += e->x_axis;
            e->y_pos -= e->y_axis;
        }
        e->d.destrect.x = (e->x_pos + 0.5f);
        e->d.destrect.y = (e->y_pos + 0.5f);
    }
}

int BuyItem(Entity *e, Item *i)
{
    if (e->n_items >= N_ENTITYITEMS)
    {
        return 0;
    }
    if (e->Gold >= i->Cost)
    {
        
        e->Gold -= i->Cost;
        e->items[e->n_items] = *i;
        e->n_items = e->n_items + 1;
        return 1;
    }
    else
    {
        return 0;
    }
}
void SellItem(Entity *e, Item *i)
{
    for (int nr = 0; nr < e->n_items; nr++)
    {
        if (&e->items[nr] == i)
        {
            for (int del = nr; del < e->n_items; del++)
            {
                e->items[del] = e->items[del + 1];
            }
            e->n_items--;
            e->Gold += i->SellValue;
        }
    }
}

void AddItem(Entity *e, Item *i, int index)
{

    e->items[index] = *i;
    e->items[index].d.destrect.x = e->x_pos;
    e->items[index].d.destrect.y = e->y_pos;
}
void CreateItem(Item *i, Graphics *gfx, ItemEnums item)
{
    SDL_Rect r = {100, 100, 30, 30};
    int z = 10000;

    i->Cost = 0;

    switch (item)
    {
    case IronAxeEnum:
        ConstructDrawable(&i->d, gfx, "./include/assets/item/iron_axe.png", r, z);
        strcpy(i->Name, "Iron Axe");
        i->Cost = 50;
        break;
    case IronPickaxeEnum:
        ConstructDrawable(&i->d, gfx, "./include/assets/item/iron_pickaxe.png", r, z);
        strcpy(i->Name, "Iron Pickaxe");
        i->Cost = 50;
        break;
    case IronSwordEnum:
        ConstructDrawable(&i->d, gfx, "./include/assets/item/iron_sword.png", r, z);
        strcpy(i->Name, "Iron Sword");
        i->Cost = 100;
        break;
    case DiamondEnum:
        ConstructDrawable(&i->d, gfx, "./include/assets/item/diamond.png", r, z);
        strcpy(i->Name, "Diamond");
        i->Cost = 1000;
        break;
    }
}
void CreatePlant(Plant *plant, Graphics *gfx, PlantEnum plantEnum, SDL_Rect tile, Uint32 TickPlaced, int zIndex){
    ConstructDrawable(&plant->TextureMap, gfx, "./include/assets/unpacked/TileSheets/crops.png", tile, zIndex);
    switch (plantEnum)
    {
        case ParsnipType:
            plant->nPlantStages = 6;

            plant->plantStages[0].GrowTick = 0;
            strcpy(plant->plantStages[0].FilePath, "./include/assets/unpacked/TileSheets/crops.png");
            strcpy(plant->plantStages[0].Name, "Parsnip Seed");
            SDL_Rect a = {0, 0, 16, 32};
            plant->plantStages[0].srcrect = a;

            plant->plantStages[1].GrowTick = 3000;
            strcpy(plant->plantStages[1].FilePath, "./include/assets/unpacked/TileSheets/crops.png");
            strcpy(plant->plantStages[1].Name, "Parsnip Seed");
            SDL_Rect b = {16, 0, 16, 32};
            plant->plantStages[1].srcrect = b;

            plant->plantStages[2].GrowTick = 6000;
            strcpy(plant->plantStages[2].FilePath, "./include/assets/unpacked/TileSheets/crops.png");
            strcpy(plant->plantStages[2].Name, "Parsnip Seed");
            SDL_Rect c = {32, 0, 16, 32};
            plant->plantStages[2].srcrect = c;

            plant->plantStages[3].GrowTick = 8000;
            strcpy(plant->plantStages[3].FilePath, "./include/assets/unpacked/TileSheets/crops.png");
            strcpy(plant->plantStages[3].Name, "Parsnip Seed");
            SDL_Rect d = {48, 0, 16, 32};
            plant->plantStages[3].srcrect = d;

            plant->plantStages[4].GrowTick = 12000;
            strcpy(plant->plantStages[4].FilePath, "./include/assets/unpacked/TileSheets/crops.png");
            strcpy(plant->plantStages[4].Name, "Parsnip Seed");
            SDL_Rect e = {64, 0, 16, 32};
            plant->plantStages[4].srcrect = e;

            plant->plantStages[5].GrowTick = 16000;
            strcpy(plant->plantStages[5].FilePath, "./include/assets/unpacked/TileSheets/crops.png");
            strcpy(plant->plantStages[5].Name, "Parsnip");
            SDL_Rect f = {80, 0, 16, 32};
            plant->plantStages[5].srcrect = f;

        break;
    
    default:
        break;
    }
    plant->TickPlaced = TickPlaced;
}
void UpdatePlant(Plant *plant, Uint32 Tick){
    Uint32 calcTick = Tick - plant->TickPlaced;
    if (plant->plantStages[plant->nToUpdate].GrowTick <= calcTick){
        DrawableSetSrcRect(&plant->TextureMap, plant->plantStages[plant->nPlantStages].srcrect);
        strcpy(plant->Name, plant->plantStages[plant->nToUpdate].Name);
        if (plant->nToUpdate != plant->nPlantStages){
            plant->nToUpdate++; 
        }
    }
}