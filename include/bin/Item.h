#include "Drawable.h"

typedef enum ItemEnums{
    IronAxeEnum
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