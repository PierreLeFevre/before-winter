#include "Game.h"
#include <stdio.h>
void ConstructGame(Game *g, int* noExit){
    
    ConstructGraphics(&g->gfx);
    ConstructTileMap(&g->tileMap, &g->gfx, 20, 20, 0, 0);
    ConstructPlayer(&g->player, &g->gfx);
    ConstructCamera(&g->cam, &g->gfx, &g->player.d.srcrect.x, &g->player.d.srcrect.y);
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
    UpdateCamera(&g->cam);
}
void Render(Game *g){
    Draw(&g->cam.background);
    CamDraw(&g->cam, g->player.d);
}

void HandleEvents(Game* g){
    while(SDL_PollEvent(&g->event)){
        if(g->event.type == SDL_QUIT){
                *g->noExit = 0;
        }
        
        //behöver översättas
        /*if(g->event.type = SDL_KEYDOWN){
            printf("Physical %s key acting as %s key\n",
                    SDL_GetScancodeName(g->event.key.keysym.scancode),
                    SDL_GetKeyName(g->event.key.keysym.sym));
        }

        /*if(g->event.key.keysym.sym == SDLK_w){
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
    }
}
