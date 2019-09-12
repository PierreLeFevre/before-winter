#include "Player.h"
#include <stdio.h>

void ConstructPlayer(Player* player, Graphics* gfx){
    player->img_path = "./include/assets/character_set.png";
    SDL_Rect src;
    src.x = 20;
    src.y = 20;
    src.w = 300;
    src.h = 300;
    ConstructDrawable(&player->d, gfx, player->img_path, src);
    player->x_vel = 0.0f;
    player->y_vel = 0.0f;
    ChangeImagePath(&player->d, player->img_path);
}

void UpdatePlayer(Player* player){
    MovePlayer(player);
}

void MovePlayer(Player* player){
    player->d.srcrect.x += player->x_vel;
    player->d.srcrect.y += player->y_vel;
}

void DrawPlayer(Player* player){
    Draw(&player->d);
}