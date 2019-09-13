#include "Player.h"
#include <stdio.h>

void ConstructPlayer(Player* player, Graphics* gfx){
    player->x_pos_currCoord = 3;
    player->y_pos_currCoord = 3;
    player->x_pos_destCoord = player->x_pos_currCoord;
    player->y_pos_destCoord = player->y_pos_currCoord;
    player->x_vel = 1.0f;
    player->y_vel = 1.0f;
    player->x_dir = 0;
    player->y_dir = 0;

    player->img_path = "./include/assets/character_set.png";
    SDL_Rect src = {player->x_pos_currCoord * TILE_WIDTH, player->y_pos_currCoord * TILE_HEIGHT, 70, 80};
    SDL_Rect dest = {0, 0, 17, 18};
    ConstructDrawable(&player->d, gfx, player->img_path, src);
    DrawableSetDestrect(&player->d, dest);
    ChangeImagePath(&player->d, player->img_path);
}

void UpdatePlayer(Player* player){
    UpdatePlayerDirection(player);
    MovePlayer(player);
}

void UpdatePlayerDirection(Player* player){
    if(player->x_pos_destCoord == player->x_pos_currCoord &&
    player->y_pos_destCoord == player->y_pos_currCoord)
    {
        player->x_dir = 0;
        player->y_dir = 0;
        const Uint8 *Keys = SDL_GetKeyboardState(NULL);
        SDL_PumpEvents();
        if (Keys[SDL_SCANCODE_LEFT] || Keys[SDL_SCANCODE_A]) {
            player->x_dir -= 1;
        }
        if (Keys[SDL_SCANCODE_RIGHT] || Keys[SDL_SCANCODE_D]) {
            player->x_dir += 1;
        }
        if (Keys[SDL_SCANCODE_UP] || Keys[SDL_SCANCODE_W]) {
            player->y_dir -= 1;
        }
        if (Keys[SDL_SCANCODE_DOWN] || Keys[SDL_SCANCODE_S]) {
            player->y_dir += 1;
        }
        player->x_pos_destCoord = player->x_pos_currCoord + player->x_dir;
        player->y_pos_destCoord = player->y_pos_currCoord + player->y_dir;
    }
}

void MovePlayer(Player* player){    
    player->d.srcrect.x += player->x_vel * player->x_dir;
    player->d.srcrect.y += player->y_vel * player->y_dir;
    if(player->d.srcrect.x / TILE_WIDTH == player->x_pos_destCoord){
        player->x_pos_currCoord = player->x_pos_destCoord;
    }
    if(player->d.srcrect.y / TILE_HEIGHT == player->y_pos_destCoord){
        player->y_pos_currCoord = player->y_pos_destCoord;
    }
}

void DrawPlayer(Player* player){
    player->d.srcrect.y -= player->d.srcrect.h - TILE_HEIGHT;
    Draw(&player->d);
    player->d.srcrect.y += player->d.srcrect.h - TILE_HEIGHT;
}

void AnimatePlayer(Player* player){
    if(player->x_dir == 1){

    }
}