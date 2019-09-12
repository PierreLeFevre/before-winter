#include "Player.h"

void ConstructPlayer(Player* player, Graphics* gfx){
    player->x_vel = 0.0f;
    player->y_vel = 0.0f;
    player->moveDir = '-';
    player->img_path = "mud.jpg";
}

void UpdatePlayer(Player* player){
    SDL_Event k_event;
    while(SDL_PollEvent(&k_event)){
        switch(k_event.type){
            case SDL_KEYDOWN:
            switch (k_event.key.keysym.scancode)
            {
            case SDL_SCANCODE_LEFT:
            player->x_vel += 10;
            break;
            case SDL_SCANCODE_RIGHT:
            player->x_vel -= 10;
            break;
            case SDL_SCANCODE_UP:
            player->y_vel += 10;
            break;
            case SDL_SCANCODE_DOWN:
            player->y_vel -= 10;
            break;            
            }
        }
    }
    MovePlayer(player);
}

void MovePlayer(Player* player){
    player->d.srcrect.x += player->x_vel;
    player->d.srcrect.y += player->y_vel;
}

void DrawPlayer(Player* player){
    Draw(&player->d);
}