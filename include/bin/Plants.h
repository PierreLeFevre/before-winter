#ifndef PLANTS_H
#define PLANTS_H
#include "Drawable.h"
#include "Item.h"
#include <string.h>
typedef enum PlantEnum{ //16x32
    ParsnipType,
    CauliflowerType,
    GarlicType,
    RhubarbType,
    TomatoType,
    WheatType,
    CoffeeBeanType,
    StrawberryType
}PlantEnum;

typedef struct PlantStge{
    SDL_Rect srcrect;
    char Name[100];
    int GrowTick;
}PlantStage;

typedef struct Plant{
    char Name[100];
    Drawable TextureMap;
    Item GrownItems;
    Item SeedItems;
    PlantStage plantStages[10];
    int nPlantStages;
    Uint32 TickPlaced;
    int nToUpdate;

    int HasHarvestableBerries;
    int TickSinceLastHarvested;
    int TickAtHarvestation;
    int TickToRegrow;
}Plant;

void CreatePlant(Plant *plant, Graphics *gfx, PlantEnum plantEnum, SDL_Rect tile, Uint32 PlacedTick, int zIndex);
void CreatePlantType(Plant *plant, char name[], SDL_Rect base, int length, int diffTime);
void UpdatePlant(Plant *plant, Uint32 Tick);
Item SeedToItem(Graphics *gfx, PlantEnum plant, int nr);
#endif