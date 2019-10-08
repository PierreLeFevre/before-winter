#ifndef ENTITY_H
#define ENTITY_H
#include "Drawable.h"
#include "Item.h"
#include "Plants.h"
#include "Tile.h"

#define INVENTORY_SIZE 1000
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

    Item* items;
    int n_items;

    Item droppableItem;
    SDL_bool deadTrigger;

} Entity;

void ConstructEntity(Entity* e, Drawable* d);
void UpdateEntity(Entity *e);

void MoveEntity(Entity *e);

void CheckEntityCollision(Entity *e, Tile *GoodTiles[], int max);

int BuyItem(Entity *e, Item *i);
void SellItem(Entity *e, Item *i);

void AddItem(Entity *e, Item *i, int index);
void CreateItem(Item *i, Graphics *gfx, ItemEnums item);

void CreatePlant(Plant *plant, Graphics *gfx, PlantEnum plantEnum, SDL_Rect tile, Uint32 PlacedTick, int zIndex);
void CreatePlantType(Plant *plant, char name[], SDL_Rect base, int length, int diffTime);
void UpdatePlant(Plant *p, Uint32 Tick);
#endif
