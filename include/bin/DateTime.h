#ifndef DATETIME_H
#define DATETIME_H
#include "../SDL2/SDL.h"
typedef struct DateTime{
    Uint32 BaseTick;
    int days;
    int hour;
    int min;
    int sec;
}DateTime;
void ConstructTime(DateTime *date);
void UpdateTime(Uint32 base, DateTime *date);
#endif