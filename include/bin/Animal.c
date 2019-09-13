#include "Animal.h"
#include <stdio.h>

void ConstructAnimal(Animal* animal, Graphics* gfx){
    animal->x_vel = 2.0f;
    animal->y_vel = 2.0f;
    animal->x_dir = 0;
    animal->y_dir = 0;

    animal->Boorder.x = 0;
    animal->Boorder.y = 0;
    animal->Boorder.w = 400;
    animal->Boorder.h = 400;

    animal->img_path = "./include/assets/character_set.png";
    SDL_Rect src = {3 * TILE_WIDTH, 3 * TILE_HEIGHT, 60, 60};
    SDL_Rect dest = {0, 0, 17, 18};
    ConstructDrawable(&animal->d, gfx, animal->img_path, src);
    DrawableSetDestrect(&animal->d, dest);
    ChangeImagePath(&animal->d, animal->img_path);
}

void UpdateAnimal(Animal* animal){
    UpdateAnimalDirection(animal);
    MoveAnimal(animal);
}

void UpdateAnimalDirection(Animal* animal){
    animal->x_dir = 0;
    animal->y_dir = 0;
    const Uint8 *Keys = SDL_GetKeyboardState(NULL);
    SDL_PumpEvents();

    int tmpX = animal->x_dir;
    int tmpY = animal->y_dir;

    animal->x_dir = Randomize(1, -1);
    animal->y_dir = Randomize(1, -1);

    if (!SDL_IntersectRect(&animal->Boorder, &animal->d.destrect, &animal->RectIntersect)){
        animal->x_dir += tmpX;
        animal->y_dir += tmpY;
    }
}

void MoveAnimal(Animal* animal){    
    animal->d.srcrect.x += animal->x_vel * animal->x_dir;
    animal->d.srcrect.y += animal->y_vel * animal->y_dir;
}

void DrawAnimal(Animal* animal){
    animal->d.srcrect.y -= animal->d.srcrect.h - TILE_HEIGHT;
    Draw(&animal->d);
    animal->d.srcrect.y += animal->d.srcrect.h - TILE_HEIGHT;
}

void AnimateAnimal(Animal* animal){
    if(animal->x_dir == 1){

    }
}
int Randomize(int upper, int lower)
{
    int num = (rand() % (upper - lower + 1)) + lower;
    return num;
}