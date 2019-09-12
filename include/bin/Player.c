#include "Player.h"
#include <stdio.h>

void ConstructPlayer(Player* player, Graphics* gfx){
    player->img_path = "./include/assets/character_set.png";
    SDL_Rect src;
    src.x = 20;
    src.y = 20;
    src.w = 30;
    src.h = 30;
    SDL_Rect dest;
    dest.x = 0;
    dest.y = 0;
    dest.w = 17;
    dest.h = 18;
    ConstructDrawable(&player->d, gfx, player->img_path, src);
    DrawableSetDestrect(&player->d, dest);
    player->x_vel = 1.0f;
    player->y_vel = 1.0f;
    ChangeImagePath(&player->d, player->img_path);
}

void UpdatePlayer(Player* player){
    MovePlayer(player);
}

void MovePlayer(Player* player){
    player->d.srcrect.x += player->x_vel * player->x_dir;
    player->d.srcrect.y += player->y_vel * player->y_dir;
}

void DrawPlayer(Player* player){
    Draw(&player->d);
}

void AnimatePlayer(Player* player){
    if(player->x_dir == 1){

    }
}