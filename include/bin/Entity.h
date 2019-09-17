#include "Drawable.h"
#include "Item.h"

#define ENTITY_LENGTH 100
typedef struct Entity{
    SDL_Rect Boundrary;
    Drawable d;
    
    int Gold;
    Item *items[10];
    int itemLength;
    
    int x_vel;
    int y_vel;

    int x_dir;
    int y_dir;

    int x_distance;
    int y_distance;

    char *img_path;

    int nrFrame;
    SDL_bool MoveCompleted;
}Entity;

typedef enum Moveset{
    RandomMoveset,
    PointsMoveset
}Moveset;

void ConstructEntity(Entity *e, Graphics* gfx, char* filePath);
void UpdateEntity(Entity *e);
void MoveEntitySoft(Entity *e);
void Ai(Entity *e, Moveset m);

int BuyItem(Entity *e, Item *i);
void SellItem(Entity *e, Item *i);