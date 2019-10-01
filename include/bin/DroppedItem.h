#ifndef DROPPEDITEM_H
#define DROPPEDITEM_H
#include "Item.h"
#include "Player.h"

typedef struct DroppedItem{
    Item* item;
    Entity ent;
    float x_desired;
    float y_desired;
}DroppedItem;

void ConstructDroppedItem(DroppedItem* d_item, Item* item, Graphics* gfx, float x_pos, float y_pos);

void UpdateDroppedItem(DroppedItem* d_item, Player* player);

#endif