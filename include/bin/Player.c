#include "Player.h"
#include <stdio.h>

void ConstructPlayer(Player* player, Graphics* gfx){
    player->img_path = "./include/assets/character_set.png";
    SDL_Rect src = {20, 20, 30, 30};
    SDL_Rect dest = {0, 0, 17, 18};
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