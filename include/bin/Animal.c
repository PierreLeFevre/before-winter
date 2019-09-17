#include "Animal.h"
#include <stdio.h>
#include "FuncLib.h"
#include <time.h>
#include <math.h>

void ConstructAnimal(Animal* a, Graphics* gfx, char* filePath){
    a->ent.x_vel = 0.4f;
    a->ent.y_vel = 0.4f;
    a->biggest_distance_x = 100;
    a->biggest_distance_y = 100;
    a->x_posSTART = 2 * TILE_WIDTH;
    a->y_posSTART = 2 * TILE_HEIGHT;

    SDL_Rect src = {a->x_posSTART, a->x_posSTART, 40, 60};
    SDL_Rect dest = {40, 40, 40, 100};
    a->ent.hitbox = src;
    ConstructEntity(&a->ent, gfx, src, filePath);
    DrawableSetDestRect(&a->ent.d, dest);
    GenerateDesiredPosition(a);
}
void UpdateAnimal(Animal *a){
    //Generate a direction vector towards desired position
    if(a->ent.d.srcrect.x < a->x_desired + 2 && a->ent.d.srcrect.x > a->x_desired - 2 ){
        GenerateDesiredPosition(a);
    }
    //----------------------------------------------------
    //Sets direction towards that position
    a->ent.x_dir = a->x_desired - a->ent.d.srcrect.x;
    a->ent.y_dir = a->y_desired - a->ent.d.srcrect.y;
    int lenght = sqrt(pow(a->ent.x_dir, 2) + pow(a->ent.y_dir, 2));
    a->ent.x_dir /= lenght;
    a->ent.y_dir /= lenght;
    //------------------------------------

    a->ent.hitbox = a->ent.d.srcrect;
    UpdateEntity(&a->ent);
}
void GenerateDesiredPosition(Animal* a){
    a->x_desired = Map(rand() % (int)a->biggest_distance_x, 0, a->biggest_distance_x, a->x_posSTART - a->biggest_distance_x / 2, a->x_posSTART + a->biggest_distance_x / 2);
    a->y_desired = Map(rand() % (int)a->biggest_distance_y, 0, a->biggest_distance_y, a->x_posSTART - a->biggest_distance_y / 2, a->x_posSTART + a->biggest_distance_y / 2);
}