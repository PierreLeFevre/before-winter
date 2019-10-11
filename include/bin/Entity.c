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

    for(int i = 0; i < INVENTORY_SIZE; i++){
        e->items[i].d.gfx = e->d.gfx;
    }
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
    if (e->n_items >= INVENTORY_SIZE)
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