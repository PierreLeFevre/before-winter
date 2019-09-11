#include "./include/header/Game.h"

int main()
{
    Game g;
    ConstructGame(&g);
    int noExit = 1;
    while(noExit){
        Go(&g);
        SDL_Event event;
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