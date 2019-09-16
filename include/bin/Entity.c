#include "Entity.h"
#include <stdio.h>
#include "FuncLib.h"
#include <time.h>
void ConstructEntity(Entity *e, Graphics *g, SDL_Rect src, SDL_Rect dest, SDL_Rect Boundrary){
    e->x_vel = 1;
    e->y_vel = 1;
    e->MoveCompleted = SDL_TRUE;
    e->Boundrary = Boundrary;
    ConstructDrawable(&e->d, g, e->img_path, src, 0);
    DrawableSetDestRect(&e->d, dest);
    ChangeImagePath(&e->d, e->img_path);
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