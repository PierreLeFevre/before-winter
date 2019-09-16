#include "./include/bin/Game.h"
#include <stdio.h>
int main()
{
    const int FPS = 60;
    const int Framedelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    int noExit = 1;
    Game g;

    #pragma Cow
    g.entities[0].img_path = "./include/assets/cow_set.png";
    SDL_Rect src = {10 * TILE_WIDTH, 10 * TILE_HEIGHT, 124, 200};
    SDL_Rect dest = {40, 40, 40, 100};
    SDL_Rect bound = {0, 0, 1000, 1000};
    #pragma Cow

    ConstructGame(&g, &noExit);
    
    ConstructEntity(&g.entities[0], &g.gfx, src, dest, bound);
    int nr = 0;

    while(noExit){
        frameStart = SDL_GetTicks();
        Go(&g);  //THIS IS A init() FUNKTION
        frameTime = SDL_GetTicks() - frameStart;
        if (Framedelay > frameTime)
        {
            SDL_Delay(Framedelay - frameTime);
        }
        
    }
    DestroyGame(&g);
    return 0;
}