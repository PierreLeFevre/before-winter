#include "./include/bin/Game.h"

int main()
{
    Game g;
    ConstructGame(&g);
    int noExit = 1;
<<<<<<< HEAD
    SDL_SetRenderDrawColor(g.gfx.rend,0,255,0,255); //Ritar skärmen grön varje frame för att sedan få banan utritad
        SDL_RenderClear(g.gfx.rend);
=======
    SDL_SetRenderDrawColor(g.gfx.rend,0,255,0,0); //Ritar skärmen grön varje frame för att sedan få banan utritad
    SDL_RenderClear(g.gfx.rend);
>>>>>>> e96ad8769c5bbe88e021ca3da881a17852cb5bf5
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