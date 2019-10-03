#include "FuncLib.h"

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
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

char *IntToCharArray(int number)
{
    int isNegative = 0;

    if (number < 0)
    {
        isNegative = 1;
        number *= -1;
    }

    int n = log10(number) + 1;
    int k;
    char *array = malloc(n * sizeof(char));
    //char *array = calloc(n, sizeof(char));
    for (k = 0; k < n; ++k, number /= 10)
    {
        array[k] = number % 10;
    }
    if (isNegative)
    {
        array[k] = '-';
    }

    for (int i = 0; i < k; i++)
    {
        switch (array[i])
        {
        case 0:
            array[i] = 48;
            break;
        case 1:
            array[i] = 49;
            break;
        case 2:
            array[i] = 50;
            break;
        case 3:
            array[i] = 51;
            break;
        case 4:
            array[i] = 52;
            break;
        case 5:
            array[i] = 53;
            break;
        case 6:
            array[i] = 54;
            break;
        case 7:
            array[i] = 55;
            break;
        case 8:
            array[i] = 56;
            break;
        case 9:
            array[i] = 57;
            break;
        default:
            break;
        }
    }
    array[k + 1] = '\0';
    CharReverse(array);
    return array;
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
char *strcpyMACFRIENDLY(char *s1, const char *s2)
{
    char *s = s1;
    while ((*s++ = *s2++) != 0)
        ;
    return (s1);
}
int Get_Tile_Number(int x, int y)
{
    return (x / 60) + ((y / 60) * 60);
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