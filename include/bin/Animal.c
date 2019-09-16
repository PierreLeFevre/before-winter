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
    SDL_Rect src = {10 * TILE_WIDTH, 10 * TILE_HEIGHT, 124, 200};
    SDL_Rect dest = {40, 40, 40, 100};
    ConstructDrawable(&animal->d, gfx, animal->img_path, src, 0);
    DrawableSetDestRect(&animal->d, dest);
    ChangeImagePath(&animal->d, animal->img_path);
}

void UpdateAnimal(Animal* animal){
    UpdateAnimalDirection(animal);
    MoveAnimalSoft(animal);
    animal->d.z_index = ((animal->d.srcrect.y + animal->d.srcrect.h) / TILE_HEIGHT + 1) * 10 + 3; //Row 1 = 13, Row 2 = 23....
}

void UpdateAnimalDirection(Animal* animal){
    animal->x_dir = 0;
    animal->y_dir = 0;

    int tmpX = animal->x_dir;
    int tmpY = animal->y_dir;


    Ai(animal);
    //down
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
    
    while (animal->x_distance != 0 || animal->y_distance != 0)
    {
        //printf(" 1 %d %d \n", animal->x_distance, animal->y_distance);    
        if (animal->x_distance > 0)
        {
            animal->d.srcrect.x++;
            animal->x_distance--;
        }
        else if (animal->x_distance != 0){
            animal->d.srcrect.x--;
            animal->x_distance++;
        }

        if (animal->y_distance > 0)
        {
            animal->d.srcrect.y++;
            animal->y_distance--;
        }
        else if (animal->y_distance != 0){
            animal->d.srcrect.y--;
            animal->y_distance++;
        }
        CheckHitbox(animal);
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
            a->x_dir = rand()%3 - 1;
            a->x_distance = rand()%100 - 5;

            a->y_dir = rand()%3 - 1;
            a->y_distance = rand()%100 - 5;

            MoveAnimalSoft(a);
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
void CheckHitbox(Animal *animal){
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