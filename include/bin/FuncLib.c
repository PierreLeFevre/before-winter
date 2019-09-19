#include "FuncLib.h"

#include <stdio.h>
#include <math.h>

void RemoveCharacterFromArray(char* const buffer, char toRemove, int size) {
    // char* bufferP = buffer;
    // int nBytesToMove = 0;
    // for (bufferP = buffer; *(bufferP - 1) != 0; bufferP++) {
    //     *(bufferP - nBytesToMove) = *bufferP;
    //     if (*bufferP == toRemove) {
    //         nBytesToMove++;
    //     }
    // }
    for(int i = 0; i < size; i++){
        while (buffer[i] == toRemove) {
            for(int j = i ; j < size; j++){
                buffer[j] = buffer[j + 1];
            }
        }
    }
}

double Map(double value, double in_min, double in_max, double out_min, double out_max){
    if(in_min > in_max || out_min > out_max){
        return -1;
    }
    if(value > in_min || value < out_max){
        return (value - in_min) * ((out_max - out_min)/(in_max - in_min)) + out_min;
    }
    else{
        return value;
    }
}

int Cap(int value_in, int cap_to){
    if(value_in > abs(cap_to)){
        return abs(cap_to);
    }else if(value_in < -abs(cap_to)){
        return -abs(cap_to);
    }else{
        return value_in;
    }
}

int CheckCollision(SDL_Rect A, SDL_Rect B)//lazy foo  http://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php
{
    if (A.y + A.h <= B.y)
    {
        return 0;
    }

    if (A.y >= B.y + B.h)
    {
        return 0;
    }

    if (A.x + A.w <= B.x)
    {
        return 0;
    }

    if (A.x >= B.x + B.w)
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
char IntToChar(int input){
    switch (input)
    {
    case 0:
        return 48;
        break;
    case 1:
        return 49;
        break;
    case 2:
        return 50;
        break;
    case 3:
        return 51;
        break;
    case 4:
        return 52;
        break;
    case 5:
        return 53;
        break;
    case 6:
        return 54;
        break;
    case 7:
        return 55;
        break;
    case 8:
        return 56;
        break;
    case 9:
        return 57;
        break;
    default:
        break;
    }
}