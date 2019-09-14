#include "Animal.h"
#include <stdio.h>

void ConstructAnimal(Animal* animal, Graphics* gfx){
    animal->x_vel = 2.0f;
    animal->y_vel = 2.0f;
    animal->x_dir = 0;
    animal->y_dir = 0;

    animal->Border.x = 300;
    animal->Border.y = 300;
    animal->Border.w = 1000;
    animal->Border.h = 1000;

    animal->aiIterations = 0;
    animal->aiTarget = rand() % 100;

    animal->img_path = "./include/assets/cow_set.png";
    SDL_Rect src = {10 * TILE_WIDTH, 10 * TILE_HEIGHT, 200, 150};
    SDL_Rect dest = {40, 40, 40, 100};
    ConstructDrawable(&animal->d, gfx, animal->img_path, src);
    DrawableSetDestRect(&animal->d, dest);
    ChangeImagePath(&animal->d, animal->img_path);
}

void UpdateAnimal(Animal* animal){
    UpdateAnimalDirection(animal);
    MoveAnimalSoft(animal);
}

void UpdateAnimalDirection(Animal* animal){
    animal->x_dir = 0;
    animal->y_dir = 0;

    int tmpX = animal->x_dir;
    int tmpY = animal->y_dir;


    Ai(animal);
    //down
    if (animal->d.srcrect.y > animal->Border.h){
        animal->d.srcrect.y = animal->Border.h;
    }
    //up
    if(animal->d.srcrect.y < animal->Border.y){
        animal->d.srcrect.y = animal->Border.y;
    }
    //right
    if(animal->d.srcrect.x > animal->Border.w){
        animal->d.srcrect.x = animal->Border.w;
    }
    //left
    if(animal->d.srcrect.x < animal->Border.x){
        animal->d.srcrect.x = animal->Border.x;
    }

    
}

void MoveAnimal(Animal* animal){    
    animal->d.srcrect.x += animal->x_vel * animal->x_dir;
    animal->d.srcrect.y += animal->y_vel * animal->y_dir;
}

void DrawAnimal(Animal* animal){
    animal->d.srcrect.y -= animal->d.srcrect.h - TILE_HEIGHT;
    animal->d.srcrect.y += animal->d.srcrect.h - TILE_HEIGHT;
}

void MoveAnimalSoft(Animal *animal){
    if (animal->x_dir > 0){
        animal->d.srcrect.x -= animal->x_vel;
        animal->x_dir--;
    }

    if (animal->x_dir < 0){
        animal->d.srcrect.x += animal->x_vel;
        animal->x_dir++;
        }

    if (animal->y_dir > 0){
        animal->d.srcrect.y -= animal->y_vel;
        animal->y_dir--;
        }
    if (animal->y_dir < 0){
        animal->d.srcrect.y += animal->y_vel;
        animal->y_dir++;
    }
}
int Ai(Animal *a)
{
    a->aiIterations++;
    if (a->aiTarget == a->aiIterations)
    {
        a->aiTarget = rand() % 100 + 1;
        a->aiIterations = 0;
        
        if (a->aiTarget >= 70)
        {
            //moo
        }
        if (a->aiTarget > 20 && a->aiTarget < 70)
        {
            //Walk
            a->x_dir = rand() % (10 + 1 - -10) + -10;
            a->x_vel = 1;

            a->y_dir = rand() % (10 + 1 - -10) + -10;
            a->x_vel = 1;
            return 1;
        }
        if (a->aiTarget > 30 && a->aiTarget < 50)
        {
            //shit
        }
        if (a->aiTarget > 0 && a->aiTarget < 30)
        {
            //eat
        }
        
        
    }
}