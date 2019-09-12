#include "./include/bin/Game.h"

int main()
{
    SDL_Event event;
    Game g;
    ConstructGame(&g);
    int noExit = 1;
    while(noExit){
        Go(&g);
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_QUIT:
                noExit = 0;
                break;
            }
        }
    }
    DestroyGame(&g);
    return 0;
}