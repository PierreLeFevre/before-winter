#include "./include/bin/Game.h"
#include <stdio.h>
int main()
{
    const int FPS = 60;
    const int Framedelay = 1000 / FPS;

    Uint32 frameStart;
    int frameTime;

    int noExit = 1;
    Game* g = malloc(500000);
    
    ConstructGame(g, &noExit);

    while(noExit){
        frameStart = SDL_GetTicks();
        Go(g);  //THIS IS A init() FUNKTION
        frameTime = SDL_GetTicks() - frameStart;
        if (Framedelay > frameTime)
        {
            SDL_Delay(Framedelay - frameTime);
        }
        printf("Items: %s for %d Gold\n", g->animals[0].ent.items[0]->Name, g->animals[0].ent.items[0]->Cost);
    }
    DestroyGame(g);
    free(g);
    return 0;
}