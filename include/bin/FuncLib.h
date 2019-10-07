#ifndef FUNCLIB_H
#define FUNCLIB_H

#include "../SDL2/SDL_rect.h"
#include "../SDL2/SDL_events.h"
//#include "Keys.h"

// typedef struct Key_Events
// {
//     /*movment*/
//     int UP[2];
//     int DOWN[2];
//     int RIGHT[2];
//     int LEFT[2];
//     /*interaction*/
//     int testkey;
//     int inventroy;
//     int harvestTemp;
//     int meny;
//     int quickSlot[9];
//     int buyitem[2];
//     int action;
// };
// struct Key_Events Key_Event;

void RemoveCharacterFromArray(char *const buffer, char toRemove, int size);
double Map(double value, double range_1_min, double range_1_max, double range_2_min, double range_2_max);
int Cap(int value_in, int cap_to);
float Dist(float x1, float y1, float x2, float y2);

int Pre_CheckCollision(SDL_Rect A, SDL_Rect B, float UP, float DOWN, float RIGHT, float LEFT);
int sign(int A);
float signf(float A);
float min(float a, float b);
float speed_cap(float Value, float Cap);
char *IntToCharArray(int nr);
int Get_Option(char option[20]);
//void Key_Options();
int EventHandler(char idea[20]);

void CharReverse(char *str);
char *strcpyMACFRIENDLY(char *d, const char *s);

void saveToFile(float x, float y);
void loadFromFile();
#endif