#include "Drawable.h"
typedef enum PlantEnum{ //16x32
    ParsnipType,
    CauliflowerType
}PlantEnum;
typedef struct PlantStges{
    SDL_Rect srcrect;
    char Name[100];
    int GrowTick;
}PlantStages;
typedef struct Plant{
    char Name[100];
    Drawable TextureMap;
    PlantStages plantStages[10];
    int nPlantStages;
    Uint32 TickPlaced;
    int nToUpdate;
}Plant;