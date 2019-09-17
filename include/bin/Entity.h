#ifndef ENTITY_H
#define ENTITY_H
#include "Drawable.h"
#include "Item.h"
typedef struct Entity{
    Drawable d;
    float x_pos;
    float y_pos;
    float x_vel;
    float y_vel;
    float x_dir;
    float y_dir;

    int Gold;
    Item *items[10];
    int itemLength;

}Entity;

void ConstructEntity(Entity *e, Graphics* gfx, SDL_Rect srcrect, char* filePath);
void UpdateEntity(Entity *e);

void MoveEntity(Entity* e);

int BuyItem(Entity *e, Item *i);
void SellItem(Entity *e, Item *i);
#endif
