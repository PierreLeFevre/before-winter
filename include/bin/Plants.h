#include "Drawable.h"
typedef enum PlantEnum{
    PumpkinEnum,
    MelonSeedsIntoRoseEnum,
    WheatEnum
}PlantEnum;
typedef struct PlantStges{
    Drawable drawable;
    char FilePath[100];
    int GrowTick;
}PlantStages;
typedef struct Plant{
    Drawable Current;
    PlantStages plantStages[10];
    int nPlantStages;
    Uint32 TickPlaced;
}Plant;