#ifndef ENTITY_H
#define ENTITY_H
#include "Drawable.h"
#include "Item.h"
#include "Plants.h"
#define N_ENTITYITEMS 10
typedef struct Entity
{
    Drawable d;
    SDL_Rect hitbox;
    SDL_Rect interaction_hitbox;

    int interaction_hitbox_size;
    int interaction_hitbox_offset;

    float x_pos;
    float y_pos;
    float x_vel;
    float y_vel;
    float movement_speed;
    float accaleration;
    float friction;
    float x_axis;
    float y_axis;
    float x_dir;
    float y_dir;
    float x_face;
    float y_face;

    float health;

    int Gold;

    Item items[N_ENTITYITEMS];
    int n_items;

    Item droppableItem;
    SDL_bool deadTrigger;

} Entity;

void ConstructEntity(Entity *e, Graphics *gfx, SDL_Rect destrect, char *filePath);
void UpdateEntity(Entity *e);

void MoveEntity(Entity *e);

int BuyItem(Entity *e, Item *i);
void SellItem(Entity *e, Item *i);

void AddItem(Entity *e, Item *i, int index);
void CreateItem(Item *i, Graphics *gfx, ItemEnums item);

void CreatePlant(Plant *plant, Graphics *gfx, PlantEnum plantEnum, SDL_Rect tile);
void UpdatePlant(Plant *p, Uint32 Tick);
#endif
