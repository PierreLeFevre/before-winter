#include "FuncLib.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void RemoveCharacterFromArray(char *const buffer, char toRemove, int size)
{
    // char* bufferP = buffer;
    // int nBytesToMove = 0;
    // for (bufferP = buffer; *(bufferP - 1) != 0; bufferP++) {
    //     *(bufferP - nBytesToMove) = *bufferP;
    //     if (*bufferP == toRemove) {
    //         nBytesToMove++;
    //     }
    // }
    for (int i = 0; i < size; i++)
    {
        while (buffer[i] == toRemove)
        {
            for (int j = i; j < size; j++)
            {
                buffer[j] = buffer[j + 1];
            }
        }
    }
}

double Map(double value, double in_min, double in_max, double out_min, double out_max)
{
    if (in_min > in_max || out_min > out_max)
    {
        return -1;
    }
    if (value > in_min || value < out_max)
    {
        return (value - in_min) * ((out_max - out_min) / (in_max - in_min)) + out_min;
    }
    else
    {
        return value;
    }
}

int Cap(int value_in, int cap_to)
{
    if (value_in > abs(cap_to))
    {
        return abs(cap_to);
    }
    else if (value_in < -abs(cap_to))
    {
        return -abs(cap_to);
    }
    else
    {
        return value_in;
    }
}

float Dist(float x1, float y1, float x2, float y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int Pre_CheckCollision(SDL_Rect A, SDL_Rect B, float UP, float DOWN, float RIGHT, float LEFT)
{
    if (A.y + A.h + DOWN <= B.y)
    {
        return 0;
    }

    if (A.y + UP >= B.y + B.h)
    {
        return 0;
    }

    if (A.x + A.w + RIGHT <= B.x)
    {
        return 0;
    }

    if (A.x + LEFT >= B.x + B.w)
    {
        return 0;
    }
    return 1;
}
int sign(int A)
{
    if (A == 0)
    {
        return 0;
    }
    else if (A < 0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
}
float signf(float A)
{
    if (A == 0)
    {
        return 0.0f;
    }
    else if (A < 0)
    {
        return -1.0f;
    }
    else
    {
        return 1.0f;
    }
}
float min(float a, float b)
{
    if (a < b)
    {
        return a;
    }
    return b;
}
float speed_cap(float value, float cap)
{
    if (value > cap)
    {
        return cap;
    }
    return value;
}
void CharReverse(char *str)
{
    int i;
    int j;
    char a;
    char len = strlen(str);
    for (i = 0, j = len - 1; i < j; i++, j--)
    {
        a = str[i];
        str[i] = str[j];
        str[j] = a;
    }
}
int Get_Option(char Option[20])
{
    FILE *fp;
    char String[20];
    int Value;
    fp = fopen("options.txt", "r");
    if (fp == NULL)
    {
        return -1;
    }
    while (fscanf(fp, "%s %d", String, &Value) != -1)
    {
        if (!strcmp(String, Option))
        {
            fclose(fp);
            return Value;
        }
    }
    fclose(fp);
    return -2;
}
// void Key_Options()
// {
//     Key_Event.UP[0] = Get_Option("1UP=");
//     Key_Event.DOWN[0] = Get_Option("1DOWN=");
//     Key_Event.RIGHT[0] = Get_Option("1RIGHT=");
//     Key_Event.LEFT[0] = Get_Option("1LEFT=");

//     Key_Event.UP[1] = Get_Option("2UP=");
//     Key_Event.DOWN[1] = Get_Option("2DOWN=");
//     Key_Event.RIGHT[1] = Get_Option("2RIGHT=");
//     Key_Event.LEFT[1] = Get_Option("2LEFT=");

//     Key_Event.testkey = Get_Option("testkey=");
//     Key_Event.meny = Get_Option("meny=");
//     Key_Event.harvestTemp = Get_Option("harvestTemp=");
//     Key_Event.inventroy = Get_Option("inventory=");
//     Key_Event.action = Get_Option("action=");

//     Key_Event.quickSlot[0] = Get_Option("quickSlot1=");
//     Key_Event.quickSlot[1] = Get_Option("quickSlot2=");
//     Key_Event.quickSlot[2] = Get_Option("quickSlot3=");
//     Key_Event.quickSlot[3] = Get_Option("quickSlot4=");
//     Key_Event.quickSlot[4] = Get_Option("quickSlot5=");
//     Key_Event.quickSlot[5] = Get_Option("quickSlot6=");
//     Key_Event.quickSlot[6] = Get_Option("quickSlot7=");
//     Key_Event.quickSlot[7] = Get_Option("quickSlot8=");
//     Key_Event.quickSlot[8] = Get_Option("quickSlot9=");
// }
int EventHandler(char thinboi[20])
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[Get_Option(thinboi)])
    {
        return 1;
    }
    return 0;
}

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