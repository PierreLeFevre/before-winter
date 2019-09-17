#ifndef ENTITY_H
#define ENTITY_H
#include "Drawable.h"

typedef struct Entity{
    SDL_Rect Boundrary;
    Drawable d;
    float x_pos;
    float y_pos;
    float x_vel;
    float y_vel;
    float x_dir;
    float y_dir;

}Entity;

void ConstructEntity(Entity *e, Graphics* gfx, SDL_Rect srcrect, char* filePath);
void UpdateEntity(Entity *e);

void MoveEntity(Entity* e);

#endif