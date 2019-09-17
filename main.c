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
    ConstructGame(&g, &noExit);
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