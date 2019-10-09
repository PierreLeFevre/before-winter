#include "DateTime.h"
void ConstructTime(DateTime *date, TileMap* tilemap){
    date->sec = 0;
    date->min = 0;
    date->hour = 8;
    date->day = 0;
    
    date->season = Spring;
    date->tilemap = tilemap;
}
void UpdateTime(Uint32 base, DateTime *date){
    date->BaseTick = base;
    date->sec += date->BaseTick % 2;

    if (date->sec >= 60){
        date->sec = 0;
        date->min += 5;
    }
    if (date->min >= 60){
        date->min = 0;
        date->hour++;
    }
    if (date->hour >= 24){
        date->hour = 8;
        date->day++;
    }
    if (date->day > 10){
        date->day = 1;
        date->season++;
        
        SpriteSheet spritesheet;
        switch (date->season)
        {
        case Spring:
            spritesheet = (SpriteSheet)Spring;
            break;
        case Summer:
            spritesheet = (SpriteSheet)Summer;
            break;
        case Fall:
            spritesheet = (SpriteSheet)Fall;
            break;
        default:
            spritesheet = (SpriteSheet)Spring;
            break;
        }
        TileMapChangeSpriteSheet(date->tilemap, spritesheet);
    }
}