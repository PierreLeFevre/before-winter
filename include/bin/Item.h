#include "Drawable.h"

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

void ConstructItem(Item *i, Graphics *gfx, char *FilePath);

void UpdateItem(Item *i, SDL_Rect r, int zDrawIndex);