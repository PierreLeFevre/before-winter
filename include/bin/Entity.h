#include "Drawable.h"
#define ENTITY_LENGTH 100
typedef struct Entity{
    Drawable d;
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

void ConstructEntity(Entity *e, Graphics *g, SDL_Rect src, SDL_Rect dest);
void UpdateEntity(Entity *e);
void MoveEntitySoft(Entity *e);
void Ai(Entity *e, Moveset m);