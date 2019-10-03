#include "Drawable.h"
typedef enum PlantEnum{ //16x32
    ParsnipType,
    CauliflowerType,
    GarlicType,
    RhubarbType,
    TomatoType
}PlantEnum;

typedef struct PlantStge{
    SDL_Rect srcrect;
    char Name[100];
    int GrowTick;
}PlantStage;

typedef struct Plant{
    char Name[100];
    Drawable TextureMap;
    PlantStage plantStages[10];
    int nPlantStages;
    Uint32 TickPlaced;
    int nToUpdate;

    int HasHarvestableBerries;
    int TickSinceLastHarvested;
    int TickAtHarvestation;
    int TimeToRegrow;
}Plant;