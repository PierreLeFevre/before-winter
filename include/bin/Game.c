#include "Game.h"
#include <stdio.h>
#include "Animal.h"

void ConstructGame(Game *g, int* noExit){
    
    ConstructGraphics(&g->gfx);
    ConstructTileMap(&g->tileMapBackground, &g->gfx, 20, 20, 0, 0);
    ConstructPlayer(&g->player, &g->gfx);
    ConstructAnimal(&g->animal, &g->gfx);

    g->noExit = noExit;
}
void DestroyGame(Game *g){
    DestroyGraphics(&g->gfx);
}

void Go(Game *g){
    BeginFrame(&g->gfx);
    UpdateLogic(g);
    Render(g);
    EndFrame(&g->gfx);
}

void UpdateLogic(Game *g){
    HandleEvents(g);
    UpdatePlayer(&g->player);
    UpdateAnimal(&g->animal);
}
void Render(Game *g){
    DrawTileMap(&g->tileMapBackground);
    DrawPlayer(&g->player);
    DrawAnimal(&g->animal);
}

void HandleEvents(Game* g){
    while(SDL_PollEvent(&g->event)){
        if(g->event.type == SDL_QUIT){
                *g->noExit = 0;
        }
<<<<<<< HEAD
=======
        g->player.x_dir = 0;
        g->player.y_dir = 0;
        
        //behöver översättas
        /*if(g->event.type = SDL_KEYDOWN){
            printf("Physical %s key acting as %s key\n",
                    SDL_GetScancodeName(g->event.key.keysym.scancode),
                    SDL_GetKeyName(g->event.key.keysym.sym));
        }*/
        /*if(g->event.key.keysym.sym == SDLK_w || g->event.type == SDL_KEYDOWN){
            g->player.y_dir -= 1;
        }
        if(g->event.key.keysym.sym == SDLK_a){
            g->player.x_dir -= 1;
        }
        if(g->event.key.keysym.sym == SDLK_s){
            g->player.y_dir += 1;
        }
        if(g->event.key.keysym.sym == SDLK_d){
            g->player.x_dir += 1;
        }*/
        
>>>>>>> 441daac50be1c00efcf79f79ef3e44c010950994
    }
}
