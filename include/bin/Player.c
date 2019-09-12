#include "Player.h"

void ConstructPlayer(Player* player, Graphics* gfx){
    player->x_vel = 0.0f;
    player->y_vel = 0.0f;
    player->moveDir = '-';
    player->img_path = "mud.jpg";
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