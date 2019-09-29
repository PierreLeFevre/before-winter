#include "Animal.h"
#include <stdio.h>
#include "FuncLib.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

void ConstructAnimal(Animal *a, Graphics *gfx, char *filePath)
{
    a->ent.x_vel = 0.4f;
    a->ent.y_vel = 0.4f;
    a->biggest_distance_x = 100;
    a->biggest_distance_y = 100;
    a->x_posSTART = 2 * TILE_WIDTH;
    a->y_posSTART = 2 * TILE_HEIGHT;

    SDL_Rect destrect = {a->x_posSTART, a->x_posSTART, 40, 60};
    a->ent.hitbox = destrect;
    ConstructEntity(&a->ent, gfx, destrect, filePath);
    DrawableSetSrcRect(&a->ent.d, destrect);
    GenerateDesiredPosition(a);
}
void UpdateAnimal(Animal *a)
{
    //Generate a direction vector towards desired position
    if (a->ent.d.destrect.x < a->x_desired + 2 && a->ent.d.destrect.x > a->x_desired - 2)
    {
        GenerateDesiredPosition(a);
    }
    //----------------------------------------------------
    //Sets direction towards that position
    a->ent.x_dir = a->x_desired - a->ent.d.destrect.x;
    a->ent.y_dir = a->y_desired - a->ent.d.destrect.y;
    int length = Dist(0.0f, 0.0f, a->ent.x_dir, a->ent.y_dir);
    a->ent.x_dir /= length;
    a->ent.y_dir /= length;
    //------------------------------------

    a->ent.hitbox = a->ent.d.destrect;
    UpdateEntity(&a->ent);
}
void GenerateDesiredPosition(Animal *a)
{
    time_t t;
    srand((unsigned)time(&t));
    a->x_desired = Map(rand() % (int)a->biggest_distance_x, 0, a->biggest_distance_x, a->x_posSTART - a->biggest_distance_x / 2, a->x_posSTART + a->biggest_distance_x / 2);
    a->y_desired = Map(rand() % (int)a->biggest_distance_y, 0, a->biggest_distance_y, a->x_posSTART - a->biggest_distance_y / 2, a->x_posSTART + a->biggest_distance_y / 2);
}