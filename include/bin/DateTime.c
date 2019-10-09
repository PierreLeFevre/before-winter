#include "DateTime.h"
void ConstructTime(DateTime *date){
    date->sec = 0;
    date->min = 0;
    date->hour = 0;
    date->day = 0;
    date->season = Spring;
}
void UpdateTime(Uint32 base, DateTime *date){
    date->BaseTick = base;
    date->sec += date->BaseTick % 6000;

    if (date->sec >= 60){
        date->sec = 0;
        
        date->min += 5;
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