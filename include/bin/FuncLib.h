#ifndef FUNCLIB_H
#define FUNCLIB_H

#include "../SDL2/SDL_rect.h"

void RemoveCharacterFromArray(char* const buffer, char toRemove, int size);

double Map(double value, double range_1_min, double range_1_max, double range_2_min, double range_2_max);

int Cap(int value_in, int cap_to);

int CheckCollision(SDL_Rect A, SDL_Rect B);

#endif