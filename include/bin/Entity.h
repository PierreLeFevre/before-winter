#ifndef ENTITY_H
#define ENTITY_H
#include "Drawable.h"
#include "Item.h"
typedef struct Entity{
    Drawable d;
    SDL_Rect hitbox;
    SDL_Rect interaction_hitbox;
    int interaction_hitbox_size;    
    int interaction_hitbox_offset;

    float x_pos;
    float y_pos;
    float x_vel;
    float y_vel;
    float x_dir;
    float y_dir;
    float x_face;
    float y_face;

    int Gold;
    Item *items[10];
    int itemLength;

}Entity;

void ConstructEntity(Entity *e, Graphics* gfx, SDL_Rect destrect, char* filePath);
void UpdateEntity(Entity *e);

void MoveEntity(Entity* e);
void CheckEntityCollision(Entity* e, SDL_Rect other_hitbox);

int BuyItem(Entity *e, Item *i);
void SellItem(Entity *e, Item *i);
#endif
