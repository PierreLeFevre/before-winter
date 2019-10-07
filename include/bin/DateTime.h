#ifndef DATETIME_H
#define DATETIME_H
#include "../SDL2/SDL.h"
typedef enum SeasonTypes{
    Spring,
    Summer,
    Fall,
    Winter
}SeasonTypes;
typedef struct DateTime{
    Uint32 BaseTick;
    int day;
    int hour;
    int min;
    int sec;
    SeasonTypes season;
}DateTime;
void ConstructTime(DateTime *date);
void UpdateTime(Uint32 base, DateTime *date);
#endif