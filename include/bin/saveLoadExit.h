#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct
{
    int exitInitialized;
} ExitData;
#define INIT_EXITDATA(X) ExitData X = {.exitInitialized = 0}

struct SaveData
{
    float player_X;
    float player_Y;
};

void saveToFile(char saveFileName[20 + 1], float *x, float *y);
void loadFromFile(char saveFileName[20 + 1], float *x, float *y);