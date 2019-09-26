#include "Entity.h"
#include <stdio.h>
#include "FuncLib.h"
#include <time.h>
void ConstructEntity(Entity *e, Graphics* gfx, SDL_Rect destrect, char* filePath){
    e->interaction_hitbox_size = 10;
    e->interaction_hitbox_offset = 25;
    e->x_pos = destrect.x;
    e->y_pos = destrect.y;
    ConstructDrawable(&e->d, gfx, filePath, destrect, 0);
}
void UpdateEntity(Entity *e){
    MoveEntity(e);
    e->d.z_index = ((e->d.destrect.y + e->d.destrect.h) / TILE_HEIGHT) * TILE_Z_INDEX_MAX + Map((e->d.destrect.y + e->d.destrect.h) % TILE_HEIGHT, 0, TILE_HEIGHT, 0, TILE_Z_INDEX_MAX); //Row 1 = 15, Row 2 = 25....
}

void MoveEntity(Entity* e){
    e->x_pos += e->x_vel * e->x_dir;
    e->y_pos += e->y_vel * e->y_dir;
    e->d.destrect.x = (e->x_pos + 0.5f);
    e->d.destrect.y = (e->y_pos + 0.5f);
    if(e->x_dir != 0 || e->y_dir != 0){
        e->x_face = e->x_dir;
        e->y_face = e->y_dir;
        if(e->x_dir != 0 && e->y_dir != 0){
            e->y_face = 0;
        }
    }
}

void CheckEntityCollision(Entity* e, SDL_Rect other_hitbox){
    SDL_Rect result;
    if(SDL_IntersectRect(&e->hitbox, &other_hitbox, &result)){
        int xPrio = 0;
        int yPrio = 0;
        if(result.w >= result.h){
            yPrio = 1;
        }else{
            xPrio = 1;
        }
        if(xPrio){
            if(e->x_dir > 0){
                e->x_pos -= result.w;
            }
            if(e->x_dir < 0){
                e->x_pos += result.w;
            }
        }else if(yPrio){
            if(e->y_dir > 0){
                e->y_pos -= result.h;
            }
            if(e->y_dir < 0){
                e->y_pos += result.h;      
            }
        }
    }
}

int BuyItem(Entity *e, Item *i){
    if (e->Gold >= i->Cost){
        e->Gold -= i->Cost;
        e->items[e->n_items] = *i;
        return 1;
    }
    else{
        return 0;
    }
}
void SellItem(Entity *e, Item *i){
    for (int nr = 0; nr < e->n_items; nr++)
    {
        if (&e->items[nr] == i){
            for (int del = nr; del < e->n_items; del++)
            {
                e->items[del] = e->items[del + 1];
            }
            e->n_items--;
            e->Gold += i->SellValue;
        }
    }
}

void AddItem(Entity *e, Item *i, int index){
    
    e->items[index] = *i;
    e->items[index].d.destrect.x = e->x_pos;
    e->items[index].d.destrect.y = e->y_pos;
}
void UpdateItem(Entity *e, Item *i, int index){
    // e->items[index]->d.destrect.x = e->x_pos;
    // e->items[index]->d.destrect.y = e->y_pos;
}
void CreateItem(Item *i, Graphics *gfx, ItemEnums item){
    SDL_Rect r= {100, 100,60,60};
    int z = 10000;
    switch(item){
        case IronAxeEnum:
            ConstructDrawable(&i->d, gfx, "./include/assets/item/iron_axe.png", r, z);
            break;
        case IronPickaxeEnum:
            ConstructDrawable(&i->d, gfx, "./include/assets/item/iron_pickaxe.png", r, z);
            break;
        case IronSwordEnum:
            ConstructDrawable(&i->d, gfx, "./include/assets/item/iron_sword.png", r, z);
            break;
    }
}