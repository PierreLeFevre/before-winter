#include "../SDL2/SDL.h"
#include "TileMap.h"

int
MoveCharacter(int x, int y, char moveDir)
{
    switch(moveDir)
    {
        case 'a':
            if (x > 0)
            {
                x--;
                return 1;
            }
            break;
        case 'd':
            if (x < TILES_X)
            {
                x++;
                return 1;
            }
            break;
        case 'w':
            if (y > 0)
            {
                y--;
                return 1;
            }
            break;
        case 's':
            if (x < TILES_Y)
            {
                y++;
                return 1;
            }
            break;
    }
    return 0;
}