#include "Player.h"
#include <stdio.h>

void ConstructPlayer(Player* player, Graphics* gfx){
    player->img_path = "./include/assets/character_set.png";
    SDL_Rect src;
    src.x = 20;
    src.y = 20;
    src.w = 300;
    src.h = 300;
    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = 17;
    dest.h = 18;
    ConstructDrawable(&player->d, gfx, player->img_path, src);
    DrawableSetDestrect(&player->d, dest);
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