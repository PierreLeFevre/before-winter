#include "Entity.h"

typedef struct Animal{
    Entity ent;
}Animal;

void ConstructAnimal(Animal *animal, Entity* ent);

void UpdateAnimal(Animal *animal);

void GenerateDesiredPosition(Animal* a);
