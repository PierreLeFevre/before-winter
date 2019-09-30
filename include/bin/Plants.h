#include "Drawable.h"
typedef enum PlantEnum{
    MelonEnum,
}PlantEnum;
typedef struct Plant{
    Drawable d[2];
    int growIntervals[2];
}Plant;