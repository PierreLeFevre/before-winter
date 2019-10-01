#ifndef ITEM_H
#define ITEM_H
#include "Drawable.h"

typedef enum ItemEnums{
    IronAxeEnum,
    IronPickaxeEnum,
    IronSwordEnum,
    DiamondEnum
}ItemEnums;

typedef struct Stats{
    int Power;
    int Protection;
    int Health;
}Stats;

typedef struct Item{
    Drawable d;
    Stats s;
    char Name[100];
    int Cost;
    int SellValue;
}Item;

void ConstructItem(Item* item, Graphics* gfx, char* file_path);

#endif