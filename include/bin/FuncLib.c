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
int signFI(float A)
{
    if (A < 0)
    {
        return -1;
    }
    else
    {
        return 1;
    }
    return 0;
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
int EventHandler(char thinboi[20])
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[Get_Option(thinboi)])
    {
        return 1;
    }
    return 0;
}
