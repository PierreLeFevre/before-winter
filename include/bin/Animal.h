#ifndef ANIMAL_H
#define ANIMAL_H

#include "Drawable.h"

typedef struct Animal{
    Drawable d;
    SDL_Rect Border;
    SDL_Rect RectIntersect;
    float x_vel;
    float y_vel;
    int x_dir;
    int y_dir;
    int aiIterations;
    int aiTarget;

    char* img_path;
}Animal;
void ConstructAnimal(Animal* animal, Graphics* gfx);
void UpdateAnimal(Animal* animal);
void UpdateAnimalDirection(Animal* Animal);
void MoveAnimal(Animal* animal);

void DrawAnimal(Animal* animal);
void AnimateAnimal(Animal* animal);
int Ai(Animal *a);
#endif