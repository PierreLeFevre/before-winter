#include "Animal.h"
#include <stdio.h>
#include "FuncLib.h"
#include <time.h>
#include <math.h>
#include <stdlib.h>

void ConstructAnimal(Animal *animal, Graphics *gfx, AnimalType animaltype, int X, int Y)
{
    animal->animaltype = animaltype;
    animal->T = 0;
    animal->Follow_x = 0;
    animal->Follow_y = 0;
    animal->animationstate = 0;

    if (animaltype == DOGE)
    {
        animal->ent.movement_speed = 3.0f;
        animal->ent.accaleration = 1.1f;
        animal->ent.friction = 0.6f;

        SDL_Rect src = {0, 0, 32, 32};
        SDL_Rect dest = {X * TILE_WIDTH, Y * TILE_HEIGHT, 60, 60};
        Drawable d;
        ConstructDrawable(&d, DT_Animal, gfx, SS_Doge, src, dest, 10000);
        ConstructEntity(&animal->ent, &d);
        AnimalUpdateHitbox(animal);
    }
    else if (animaltype == Cow)
    {
        animal->ent.movement_speed = 1.6f;
        animal->ent.accaleration = 1.06f;
        animal->ent.friction = 0.6f;

        SDL_Rect src = {0, 0, 32, 32};
        SDL_Rect dest = {X * TILE_WIDTH, Y * TILE_HEIGHT, 100, 100};
        Drawable d;
        ConstructDrawable(&d, DT_Animal, gfx, SS_Cow, src, dest, 10000);
        ConstructEntity(&animal->ent, &d);
        AnimalUpdateHitbox(animal);
    }
    else if (animaltype == Pig)
    {
        animal->ent.movement_speed = 2.0f;
        animal->ent.accaleration = 1.08f;
        animal->ent.friction = 0.6f;

        SDL_Rect src = {0, 0, 32, 32};
        SDL_Rect dest = {X * TILE_WIDTH, Y * TILE_HEIGHT, 50, 50};
        Drawable d;
        ConstructDrawable(&d, DT_Animal, gfx, SS_Pig, src, dest, 10000);
        ConstructEntity(&animal->ent, &d);
        AnimalUpdateHitbox(animal);
    }
    else if (animaltype == Chicken)
    {
        animal->ent.movement_speed = 5.0f;
        animal->ent.accaleration = 1.1f;
        animal->ent.friction = 0.6f;

        SDL_Rect src = {0, 0, 16, 16};
        SDL_Rect dest = {X * TILE_WIDTH, Y * TILE_HEIGHT, 30, 30};
        Drawable d;
        ConstructDrawable(&d, DT_Animal, gfx, SS_Chiken, src, dest, 10000);
        ConstructEntity(&animal->ent, &d);
        AnimalUpdateHitbox(animal);
    }
    else
    {
        printf("Error: creating a animal that dosen't exist!\n");
    }
}
void UpdateAnimal(Animal *animal)
{
    time_t t;
    srand((unsigned)time(&t));
    if (animal->T < 10000)
    {
        animal->T++;
        switch (animal->animalmood)
        {
        case Panic:
            animal->ent.x_dir = ((rand() % 5) + 1) * sin(animal->T / 10) * signFI(cos(animal->T / 5));
            animal->ent.y_dir = ((rand() % 5) + 1) * cos(animal->T / 40) * signFI(cos(animal->T / 5));
            break;
        case Follow:
            //X axis
            if ((animal->ent.hitbox.x + animal->ent.hitbox.w / 2 + animal->ent.hitbox.w / 4) < animal->Follow_x)
            {
                animal->ent.x_dir = 1;
            }
            else if ((animal->ent.hitbox.x + animal->ent.hitbox.w / 2 - animal->ent.hitbox.w / 4) > animal->Follow_x)
            {
                animal->ent.x_dir = -1;
            }
            else
            {
                animal->ent.x_dir = 0;
            }
            //Y axis
            if ((animal->ent.hitbox.y + 10) < animal->Follow_y)
            {
                animal->ent.y_dir = 1;
            }
            else if ((animal->ent.hitbox.y - 10) > animal->Follow_y)
            {
                animal->ent.y_dir = -1;
            }
            else
            {
                animal->ent.y_dir = 0;
            }
            break;
        case Chilling:
            break;
        case Sheeping:
            animal->ent.x_dir = 0;
            animal->ent.y_dir = 0;
            break;
        case Testing: // animal[0] copy player movement for animation testing
            animal->ent.x_dir = animal->playerdirX;
            animal->ent.y_dir = animal->playerdirY;
            break;
        default:
            animal->ent.x_dir = 0;
            animal->ent.y_dir = 0;
            printf("Error: animal dose not have mood\n");
            break;
        }
    }
    else
    {
        animal->T = 0;
    }
    MoveEntity(&animal->ent);
    AnimalUpdateHitbox(animal);
    UpdateAnimalAnimation(animal);
}
void GenerateDesiredPosition(Animal *animal)
{
}

void FollowPos(int X, int Y)
{
}
void AnimalUpdateHitbox(Animal *animal)
{
    if (animal->animaltype == DOGE)
    {
        animal->ent.hitbox.x = animal->ent.d.destrect.x + 20;
        animal->ent.hitbox.y = animal->ent.d.destrect.y + 25;
        animal->ent.hitbox.w = animal->ent.d.destrect.w - 40;
        animal->ent.hitbox.h = animal->ent.d.destrect.h - 25;
    }
    else if (animal->animaltype == Cow)
    {
        animal->ent.hitbox.x = animal->ent.d.destrect.x + 25;
        animal->ent.hitbox.y = animal->ent.d.destrect.y + 40;
        animal->ent.hitbox.w = animal->ent.d.destrect.w - 46;
        animal->ent.hitbox.h = animal->ent.d.destrect.h - 40;
    }
    else if (animal->animaltype == Pig)
    {
        animal->ent.hitbox.x = animal->ent.d.destrect.x + 10;
        animal->ent.hitbox.y = animal->ent.d.destrect.y + 25;
        animal->ent.hitbox.w = animal->ent.d.destrect.w - 20;
        animal->ent.hitbox.h = animal->ent.d.destrect.h - 25;
    }
    else if (animal->animaltype == Chicken)
    {
        animal->ent.hitbox.x = animal->ent.d.destrect.x + 5;
        animal->ent.hitbox.y = animal->ent.d.destrect.y + 15;
        animal->ent.hitbox.w = animal->ent.d.destrect.w - 10;
        animal->ent.hitbox.h = animal->ent.d.destrect.h - 15;
    }
}

void UpdateAnimalAnimation(Animal *animal)
{
    if (animal->ent.x_dir != 0 || animal->ent.y_dir != 0)
    {
        animal->animationstate++;
        if (animal->ent.x_dir == -1)
        {
            animal->ent.d.srcrect.y = 32; //left dosen't exist
        }
        if (animal->ent.x_dir == 1)
        {
            animal->ent.d.srcrect.y = 32;
        }
        if (animal->ent.y_dir == -1)
        {
            animal->ent.d.srcrect.y = 64;
        }
        if (animal->ent.y_dir == 1)
        {
            animal->ent.d.srcrect.y = 0;
        }

        if (animal->animationstate == 0)
        {
            animal->ent.d.srcrect.x = 0;
        }
        if (animal->animationstate == 10)
        {
            animal->ent.d.srcrect.x = 32;
        }
        if (animal->animationstate == 20)
        {
            animal->ent.d.srcrect.x = 64;
        }
        if (animal->animationstate == 30)
        {
            animal->ent.d.srcrect.x = 96;
        }
        if (animal->animationstate == 40)
        {
            animal->animationstate = -1;
        }
    }
    //causes chicken is special
    if (animal->animaltype == Chicken)
    {
        if (animal->ent.x_dir != 0 || animal->ent.y_dir != 0)
        {
            animal->animationstate++;
            if (animal->ent.x_dir == -1)
            {
                animal->ent.d.srcrect.y = 48;
            }
            if (animal->ent.x_dir == 1)
            {
                animal->ent.d.srcrect.y = 16;
            }
            if (animal->ent.y_dir == -1)
            {
                animal->ent.d.srcrect.y = 32;
            }
            if (animal->ent.y_dir == 1)
            {
                animal->ent.d.srcrect.y = 0;
            }
            if (animal->animationstate == 0)
            {
                animal->ent.d.srcrect.x = 16;
            }
            if (animal->animationstate == 10)
            {
                animal->ent.d.srcrect.x = 32;
            }
            if (animal->animationstate == 20)
            {
                animal->ent.d.srcrect.x = 48;
            }
            if (animal->animationstate == 30)
            {
                animal->ent.d.srcrect.x = 0;
            }
            if (animal->animationstate == 40)
            {
                animal->animationstate = -1;
            }
        }
        else
        {
            animal->ent.d.srcrect.y = 64;
        }
    }
}