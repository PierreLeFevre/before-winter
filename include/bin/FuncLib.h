#ifndef FUNCLIB_H
#define FUNCLIB_H

#include "../SDL2/SDL_rect.h"

void RemoveCharacterFromArray(char* const buffer, char toRemove, int size);
double Map(double value, double range_1_min, double range_1_max, double range_2_min, double range_2_max);
int Cap(int value_in, int cap_to);
float Dist(float x1, float y1, float x2, float y2);

int CheckCollision(SDL_Rect A, SDL_Rect B);//lazy foo http://lazyfoo.net/tutorials/SDL/27_collision_detection/index.php
int sign(int A);
float signf(float A);
float min(float a, float b);
float speed_cap(float Value, float Cap);
char* IntToCharArray(int nr);

void CharReverse(char *str);
char *strcpyMACFRIENDLY(char *d, const char *s);
#endif