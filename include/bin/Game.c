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
        switch(g->event.type){
            case SDL_QUIT:
                *g->noExit = 0;
                break;
        }

    }   
    g->player.x_dir = 0;
    g->player.y_dir = 0;
    const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);
    if (keyboardState[SDL_SCANCODE_LEFT]) {
        g->player.x_dir -= 1;
    }
    if (keyboardState[SDL_SCANCODE_RIGHT]) {
        g->player.x_dir += 1;
    }
    if (keyboardState[SDL_SCANCODE_UP]) {
        g->player.y_dir -= 1;
    }
    if (keyboardState[SDL_SCANCODE_DOWN]) {
        g->player.y_dir += 1;
    }
}
