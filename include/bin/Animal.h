#include "Entity.h"

typedef struct Animal{
    Entity ent;
    float x_posSTART;
    float y_posSTART;
    float x_desired;
    float y_desired;
    float biggest_distance_x;
    float biggest_distance_y;
}Animal;

typedef enum Moveset{
    RandomMoveset,
    PointsMoveset
}Moveset;

void ConstructAnimal(Animal *e, Graphics* gfx, char* filePath);
void UpdateAnimal(Animal *e);

void GenerateDesiredPosition(Animal* a);

void MoveAnimalSoft(Animal *e);
void Ai(Animal *e, Moveset m);