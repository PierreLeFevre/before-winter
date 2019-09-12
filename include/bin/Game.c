#include "Game.h"
#include <stdio.h>
void ConstructGame(Game *g, int* noExit){
    
    ConstructGraphics(&g->gfx);
    ConstructTileMap(&g->tileMapMAIN, &g->gfx, 7, 7, 0, 0);
    ConstructTileMap(&g->tileMapSUB, &g->gfx, 3, 3, 0, 0);
    ConstructPlayer(&g->player, &g->gfx);

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
}
void Render(Game *g){
    DrawTileMap(&g->tileMapSUB);
    DrawPlayer(&g->player);
}

void HandleEvents(Game* g){
    while(SDL_PollEvent(&g->event)){
        if(g->event.type == SDL_QUIT){
                *g->noExit = 0;
        }
        g->player.x_dir = 0;
        g->player.y_dir = 0;
        const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
        if (keyboardState[SDL_SCANCODE_LEFT] || keyboardState[SDL_SCANCODE_A]) {
            g->player.x_dir -= 1;
        }
        if (keyboardState[SDL_SCANCODE_RIGHT] || keyboardState[SDL_SCANCODE_D]) {
            g->player.x_dir += 1;
        }
        if (keyboardState[SDL_SCANCODE_UP] || keyboardState[SDL_SCANCODE_W]) {
            g->player.y_dir -= 1;
        }
        if (keyboardState[SDL_SCANCODE_DOWN] || keyboardState[SDL_SCANCODE_S]) {
            g->player.y_dir += 1;
        }
    }   
    
}
