#include "Drawable.h"
typedef enum PlantEnum{ //16x32
    ParsnipType
}PlantEnum;
typedef struct PlantStges{
    Drawable drawable;
    char FilePath[100];
    char Name[100];
    int GrowTick;
}PlantStages;
typedef struct Plant{
    char Name[100];
    Drawable Current;
    PlantStages plantStages[10];
    int nPlantStages;
    Uint32 TickPlaced;
    int nToUpdate;
}Plant;