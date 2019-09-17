#include "Drawable.h"

typedef struct Stats Stats;
struct Stats{
    int Power;
    int Protection;
    int Health;
};

typedef struct Item{
    Drawable d;
    Stats s;
    char* Name[100];
    int Cost;
    int SellValue;
}Item;

