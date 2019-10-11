#include "saveLoadExit.h"

void saveToFile(char saveFileName[20 + 1], float *x, float *y)
{
    FILE *saveFile;
    struct SaveData saver;

    saver.player_X = *x;
    saver.player_Y = *y;
    saveFile = fopen(saveFileName, "wb");
    if (!saveFile)
    {
        printf("FuncLib.c saveFunction Error:%s\n", strerror(errno));
    }
    fwrite(&saver, sizeof(struct SaveData), 1, saveFile);
    fclose(saveFile);
}
void loadFromFile(char saveFileName[20 + 1], float *x, float *y)
{
    FILE *loadFile;
    struct SaveData saver;
    loadFile = fopen(saveFileName, "rb");
    if (!loadFile)
    {
        printf("FuncLib.c loadFunction Error:%s\n", strerror(errno));
        return;
    }
    fread(&saver, sizeof(struct SaveData), 1, loadFile);
    fclose(loadFile);
    *x = saver.player_X;
    *y = saver.player_Y;
}