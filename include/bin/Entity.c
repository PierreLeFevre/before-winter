#include "Entity.h"
#include <stdio.h>
#include "FuncLib.h"
#include <time.h>
void ConstructEntity(Entity *e, Graphics* gfx, char* filePath){
    e->x_vel = 1;
    e->y_vel = 1;
    e->Boundrary.x = 0;
    e->Boundrary.y = 0;
    e->Boundrary.w = 1000;
    e->Boundrary.h = 1000;
    e->MoveCompleted = SDL_TRUE;
    e->nrFrame = 0;
    SDL_Rect src = {10 * TILE_WIDTH, 10 * TILE_HEIGHT, 124, 200};
    SDL_Rect dest = {40, 40, 40, 100};

    ConstructDrawable(&e->d, gfx, filePath, src, 0);
    DrawableSetDestRect(&e->d, dest);
}
void UpdateEntity(Entity *e){
    MoveEntitySoft(e);
    Ai(e, RandomMoveset);
    e->d.z_index = ((e->d.srcrect.y + e->d.srcrect.h) / TILE_HEIGHT) * TILE_Z_INDEX_MAX + Map((e->d.srcrect.y + e->d.srcrect.h) % TILE_HEIGHT, 0, TILE_HEIGHT, 0, TILE_Z_INDEX_MAX); //Row 1 = 15, Row 2 = 25....
}
void Ai(Entity *e, Moveset m){
    srand(time(NULL));
    if (e->nrFrame == 0 && e->MoveCompleted == SDL_TRUE)
    {
        switch (m)
        {
            case RandomMoveset:
                e->x_dir = rand() % 3 - 1;
                e->y_dir = rand() % 3 - 1;
                e->x_distance = rand() % 300;
                e->y_distance = rand() % 300;
                break;
            default:
                break;
        }
        
    }
    
}
void MoveEntitySoft(Entity *e)
{
    e->nrFrame++;
    
    e->MoveCompleted = SDL_FALSE;
    if (e->nrFrame == 2) //loop per step
    {
        e->nrFrame = 0;
        if (e->x_distance != 0)
        {
            e->d.srcrect.x += e->x_dir * e->x_vel;

            if (SDL_HasIntersection(&e->Boundrary, &e->d.srcrect)){
                //inside
            }
            else{
                e->d.srcrect.x -= e->x_dir * e->x_vel;
                //outside
            }

            if (e->x_distance > 0){e->x_distance -= 1;}

            if (SDL_HasIntersection(&e->Boundrary, &e->d.srcrect)){
                //inside
            }
            else{
                e->d.srcrect.y -= e->y_dir * e->y_vel;
                //outside
            }
        }
        if (e->y_distance != 0){
            e->d.srcrect.y += e->y_dir * e->x_vel;
            if (e->y_distance > 0){e->y_distance -= 1;}
        }
        if (e->x_distance == 0 && e-> y_distance == 0){e->MoveCompleted = SDL_TRUE;}
    }
}
//************************ITEMS*************************************
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