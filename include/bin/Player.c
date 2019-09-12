#include "Player.h"
#include <stdio.h>

void ConstructPlayer(Player* player, Graphics* gfx){
    player->img_path = "./include/assets/character_set.png";
    SDL_Rect src = {20, 20, 30, 30};
    SDL_Rect dest = {0, 0, 17, 18};
    ConstructDrawable(&player->d, gfx, player->img_path, src);
    DrawableSetDestrect(&player->d, dest);
    player->x_vel = 0.0f;
    player->y_vel = 0.0f;
    ChangeImagePath(&player->d, player->img_path);
}

void UpdatePlayer(Player* player){
    MovePlayer(player);
    player->d.x_pos += 1;
    player->d.y_pos += 1;
}

void MovePlayer(Player* player){
    player->d.x_pos += player->x_vel;
    player->d.y_pos += player->y_vel;
}

void DrawPlayer(Player* player){
    Draw(&player->d);
}