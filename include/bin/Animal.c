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

    animal->img_path = "./include/assets/cow_set.png";
    SDL_Rect src = {10 * TILE_WIDTH, 10 * TILE_HEIGHT, 200, 150};
    SDL_Rect dest = {40, 40, 40, 100};
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

    int tmpX = animal->x_dir;
    int tmpY = animal->y_dir;

    animal->x_dir = Randomize(2, -2);
    animal->y_dir = Randomize(2, -2);

    //down
    if (animal->d.srcrect.y > animal->Boorder.h){
        animal->d.srcrect.y = animal->Boorder.h;
    }
    //up
    if(animal->d.srcrect.y < animal->Boorder.y){
        animal->d.srcrect.y = animal->Boorder.y;
    }
    //right
    if(animal->d.srcrect.x > animal->Boorder.w){
        animal->d.srcrect.x = animal->Boorder.w;
    }
    //left
    if(animal->d.srcrect.x < animal->Boorder.x){
        animal->d.srcrect.x = animal->Boorder.x;
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