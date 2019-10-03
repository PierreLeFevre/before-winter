#include "Entity.h"
#include <stdio.h>
#include "FuncLib.h"
#include <time.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
void ConstructEntity(Entity *e, Drawable *d)
{
    e->d = *d;
    e->x_pos = e->d.destrect.x;
    e->y_pos = e->d.destrect.y;
    e->interaction_hitbox_size = 10;
    e->interaction_hitbox_offset = 25;
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

    if ((abs((int)e->x_axis) <= 0.6f))
    {
        e->x_axis = 0;
    }
    if ((abs((int)e->y_axis) <= 0.6f))
    {
        e->y_axis = 0;
    }
    // if (e->x_axis != 0 && e->y_axis != 0)
    // {
    //     e->x_axis = e->x_axis * 0.7f;
    //     e->y_axis = e->y_axis * 0.71014f;
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
        if (Pre_CheckCollision(e->hitbox, GoodTiles[i]->hitboxes[1], 0, 0, e->x_axis, e->x_axis))
        {
            pre_colision[0] = 1;
        }
        if (Pre_CheckCollision(e->hitbox, GoodTiles[i]->hitboxes[1], e->y_axis, e->y_axis, 0, 0))
        {
            pre_colision[1] = 1;
        }
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
    // SDL_Rect r = {100, 100, 30, 30};
    // int z = 10000;

    // i->Cost = 0;

    // switch (item)
    // {
    // case IronAxeEnum:
    //     ConstructDrawable(&i->d, gfx, "./include/assets/item/iron_axe.png",SS_ITEM , r, r, z);
    //     strcpy(i->Name, "Iron Axe");
    //     i->Cost = 50;
    //     break;
    // case IronPickaxeEnum:
    //     ConstructDrawable(&i->d, gfx, "./include/assets/item/iron_pickaxe.png", SS_ITEM , r, r, z);
    //     strcpy(i->Name, "Iron Pickaxe");
    //     i->Cost = 50;
    //     break;
    // case IronSwordEnum:
    //     ConstructDrawable(&i->d, gfx, "./include/assets/item/iron_sword.png", SS_ITEM , r, r, z);
    //     strcpy(i->Name, "Iron Sword");
    //     i->Cost = 100;
    //     break;
    // case DiamondEnum:
    //     ConstructDrawable(&i->d, gfx, "./include/assets/item/diamond.png", SS_ITEM , r, r, z);
    //     strcpy(i->Name, "Diamond");
    //     i->Cost = 1000;
    //     break;
    // }
}
void CreatePlant(Plant *plant, Graphics *gfx, PlantEnum plantEnum, SDL_Rect tile, Uint32 TickPlaced, int zIndex)
{   
    ConstructDrawable(&plant->GrownItems,DT_Plant, gfx, SS_ITEM, tile, tile, zIndex);
    ConstructDrawable(&plant->TextureMap, DT_Plant, gfx, SS_PLANT, tile, tile, zIndex);
    SDL_Rect r;
    switch (plantEnum)
    {
    case ParsnipType:
        r.x = 0;
        r.y = 0;
        r.w = 16;
        r.h = 32;

        r.y += 10;
        r.h = 20;

        plant->GrownItems.srcrect.x = 0;
        plant->GrownItems.srcrect.y = 16;
        plant->GrownItems.srcrect.w = 16;
        plant->GrownItems.srcrect.h = 16;
        CreatePlantType(plant, "Parsnip", r, 6, 5000);

        break;

    case CauliflowerType:
        r.x = 0;
        r.y = 32;
        r.w = 16;
        r.h = 32;

        r.h -= 16;
        r.y += 16;

        plant->GrownItems.srcrect.x = 22*16;
        plant->GrownItems.srcrect.y = 7*16;
        plant->GrownItems.srcrect.w = 16;
        plant->GrownItems.srcrect.h = 16;
        CreatePlantType(plant, "Cauliflower", r, 7, 5000);
    break;

    case GarlicType:
        r.x = 0;
        r.y = 64;
        r.w = 16;
        r.h = 32;

        r.y += 10;
        CreatePlantType(plant, "Garlic", r, 6, 1000);

    break;

    case RhubarbType:
        r.x = 0;
        r.y = 96;
        r.w = 16;
        r.h = 32;
        CreatePlantType(plant, "Rhubarb", r, 7, 1000);

    break;

    case TomatoType:
        r.x = 0;
        r.y = 96 + 32;
        r.w = 16;
        r.h = 32;
        CreatePlantType(plant, "Tomato", r, 8, 1000);
        plant->nPlantStages -= 1;
        plant->TickToRegrow = 2000;
        plant->HasHarvestableBerries = 1;
    break;

    default:
        break;
    }
    plant->TickPlaced = TickPlaced;
}
void CreatePlantType(Plant *plant, char name[], SDL_Rect base, int length, int diffTime){
    plant->nPlantStages = length - 1;
    plant->nToUpdate = 0;
    SDL_Rect r = base;
    strcpy(plant->Name, name);
    for (int i = 0; i < length; i++)
    {
        r.x += 16;
        plant->plantStages[i].srcrect = r;
        plant->plantStages[i].GrowTick = diffTime * i;
    }
}
void UpdatePlant(Plant *plant, Uint32 Tick)
{
    Uint32 calcTick = Tick - plant->TickPlaced;
    if (plant->plantStages[plant->nToUpdate].GrowTick <= calcTick)
    {
        plant->TextureMap.srcrect = plant->plantStages[plant->nToUpdate].srcrect;
        if (plant->HasHarvestableBerries == 0){
            if (plant->plantStages[plant->nToUpdate].GrowTick <= Tick && plant->nPlantStages - 1 >= plant->nToUpdate + 1){
                plant->nToUpdate++;
            }
        }
        else{
            if (plant->plantStages[plant->nPlantStages].GrowTick > Tick - plant->TickPlaced){ //initial growth
                plant->nToUpdate++;
            }
            if (plant->nPlantStages == plant->nToUpdate){//no berries
                plant->TickSinceLastHarvested = Tick - plant->TickAtHarvestation;
                if (plant->TickToRegrow <= plant->TickSinceLastHarvested){
                    plant->nToUpdate--;
                }
            }
        }
    }
}