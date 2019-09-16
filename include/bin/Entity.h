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
}Entity;

void ConstructEntity(Entity e[ENTITY_LENGTH], Graphics *g);
void UpdateEntity(Entity e[ENTITY_LENGTH]);
void MoveEntitySoft(Entity e[ENTITY_LENGTH]);