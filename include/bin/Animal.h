#include "Entity.h"

typedef enum AnimalType
{
    DOGE,
    Cow,
    Pig,
    Chicken,
} AnimalType;
typedef enum AnimalMood
{
    Panic,
    Follow,
    Chilling,
    Sheeping,
    Testing,
} AnimalMood;

typedef struct Animal
{
    Entity ent;
    AnimalType animaltype;
    AnimalMood animalmood;
    int T;
    int Follow_x, Follow_y;
    int animationstate;
    int Priority;

    //Temp
    int playerdirX;
    int playerdirY;
} Animal;

void ConstructAnimal(Animal *animal, Graphics *gfx, AnimalType animaltype, int x, int y);

void UpdateAnimal(Animal *animal);

void UpdateAnimalAnimation(Animal *animal);
void AnimalUpdateHitbox(Animal *animal);
