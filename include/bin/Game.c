#include "Game.h"
#include <stdio.h>
void ConstructGame(Game *g, int* noExit){
    
    ConstructGraphics(&g->gfx);
    SDL_Rect sr;
    sr.x = 10;
    sr.y = 10;
    sr.w = 200;
    sr.h = 200;

    ConstructTileMap(&g->tm, &g->gfx, 7, 7, 0, 0);
    ConstructPlayer(&g->player, &g->gfx);

    g->noExit = noExit;
}
void DestroyGame(Game *g){
    DestroyGraphics(&g->gfx);
}

void Input(SDL_Event *e, GameState gs, Game *g){
    while(SDL_PollEvent(e)){
        if (gs != Startmenu)
        {
            switch(e->type)
            {
                case SDL_KEYDOWN:
                    switch (e->key.keysym.scancode)
                    {
                        case SDL_SCANCODE_D:
                            g->player.moveDir = 'd';
                            g->player.x_vel = 10;
                            MovePlayer(&g->player);
                            break;
                        case SDL_SCANCODE_A:
                            g->player.moveDir = 'a';
                            g->player.x_vel = -10;
                            MovePlayer(&g->player);
                            break;
                        case SDL_SCANCODE_W:
                            g->player.moveDir = 'w';
                            g->player.y_vel = -10;
                            MovePlayer(&g->player);
                            break;
                        case SDL_SCANCODE_S:
                            g->player.moveDir = 's';
                            g->player.y_vel = 10;
                            MovePlayer(&g->player);
                            break;
                        
                        default:
                            break;
                    }
                    break;
                case SDL_QUIT:
                    g->noExit = (int *) 0;
                    return;
            }
        }
    }
}
void Go(Game *g){
    BeginFrame(&g->gfx);
    UpdateLogic(g);
    Render(g);
    EndFrame(&g->gfx);
}

void UpdateLogic(Game *g){
    Input(&g->event, Level1, g);
}
void Render(Game *g){
    DrawTileMap(&g->tm);
    DrawPlayer(&g->player);
}

// void HandleEvents(Game* g){
//     while(SDL_PollEvent(&g->event)){                                                                     UNUSED
//         switch(g->event.type){
//             case SDL_QUIT:
//                 *g->noExit = 0;
//                 break;
//         }
//     }
// }