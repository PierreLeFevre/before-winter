#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
typedef struct ExitData
{
    int exitInitialized;
} ExitData;

struct SaveData
{
    float player_X;
    float player_Y;
};

void saveToFile(char saveFileName[20 + 1], float *x, float *y);
void loadFromFile(char saveFileName[20 + 1], float *x, float *y);