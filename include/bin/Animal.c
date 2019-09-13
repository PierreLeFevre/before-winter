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
    AnimateAnimal(animal);
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
        printf("1");
    }
    //up
    if(animal->d.srcrect.y < animal->Border.y){
        animal->d.srcrect.y = animal->Border.y;
        printf("2");
    }
    //right
    if(animal->d.srcrect.x > animal->Border.w){
        animal->d.srcrect.x = animal->Border.w;
        printf("3");
    }
    //left
    if(animal->d.srcrect.x < animal->Border.x){
        animal->d.srcrect.x = animal->Border.x;
        printf("4");
    }
    
}

void MoveAnimal(Animal* animal){    
    animal->d.srcrect.x += animal->x_vel * animal->x_dir;
    animal->d.srcrect.y += animal->y_vel * animal->y_dir;
}

<<<<<<< HEAD
void DrawAnimal(Animal* animal){
    animal->d.srcrect.y -= animal->d.srcrect.h - TILE_HEIGHT;
    animal->d.srcrect.y += animal->d.srcrect.h - TILE_HEIGHT;
}

=======
>>>>>>> d72727d536f6e67b5d5dd7cc0ac8128ed1686031
void AnimateAnimal(Animal* animal){
    if(animal->x_dir == 1){

    }
}
int Ai(Animal *a)
{
    a->aiIterations++;

    a->x_dir = 30;
            a->y_dir = 30;
    if (a->aiTarget == a->aiIterations)
    {
        int r = rand() % 100;
        if (r >= 70)
        {
            //moo
        }
        if (r > 60 && r < 70)
        {
            //Walk
            

        }
        if (r > 30 && r < 50)
        {
            //shit
        }
        if (r > 0 && r < 30)
        {
            //eat
        }
        a->aiIterations = 0;
    }
}