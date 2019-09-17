#include "Entity.h"
#include <stdio.h>
#include "FuncLib.h"
#include <time.h>
void ConstructEntity(Entity *e, Graphics* gfx, SDL_Rect srcrect, char* filePath){
    e->x_pos = srcrect.x;
    e->y_pos = srcrect.y;
    ConstructDrawable(&e->d, gfx, filePath, srcrect, 0);
}
void UpdateEntity(Entity *e){
    MoveEntity(e);
    e->d.z_index = ((e->d.srcrect.y + e->d.srcrect.h) / TILE_HEIGHT) * TILE_Z_INDEX_MAX + Map((e->d.srcrect.y + e->d.srcrect.h) % TILE_HEIGHT, 0, TILE_HEIGHT, 0, TILE_Z_INDEX_MAX); //Row 1 = 15, Row 2 = 25....
}

void MoveEntity(Entity* e){
    e->x_pos += e->x_vel * e->x_dir;
    e->y_pos += e->y_vel * e->y_dir;
    e->d.srcrect.x = e->x_pos;
    e->d.srcrect.y = e->y_pos;
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
        e->items[e->itemLength] = i;
        return 1;
    }
    else{
        return 0;
    }
}
void SellItem(Entity *e, Item *i){
    for (int nr = 0; nr < e->itemLength; nr++)
    {
        if (e->items[nr] == i){
            for (int del = nr; del < e->itemLength; del++)
            {
                e->items[del] = e->items[del + 1];
            }
            e->itemLength--;
            e->Gold += i->SellValue;
        }
    }
}