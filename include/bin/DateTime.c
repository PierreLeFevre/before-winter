#include "DateTime.h"
void ConstructTime(DateTime *date){
    date->sec = 0;
    date->min = 0;
    date->hour = 0;
    date->day = 0;
}
void UpdateTime(Uint32 base, DateTime *date){
    date->BaseTick = base;
    date->sec += date->BaseTick % 60;
    if (date->sec >= 60){
        date->sec = 0;
        date->min++;
    }
    if (date->min >= 60){
        date->min = 0;
        date->hour++;
    }
    if (date->hour >= 24){
        date->hour = 0;
        date->day++;
    }
    if (date->day >= 10){
        date->day = 0;
        date->season++;
    }
}