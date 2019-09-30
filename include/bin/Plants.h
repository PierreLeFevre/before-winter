#include "Drawable.h"
typedef enum PlantEnum{
    MelonEnum,
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
}Plant;