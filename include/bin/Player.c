#include "Player.h"

void ConstructPlayer(Player* player, float x_vel, float y_vel){
    player->x_vel = x_vel;
    player->y_vel = y_vel;
    player->moveDir = '-';
}

void UpdatePlayer(Player* player){
    MoveCharacter(player);
}

void MovePlayer(Player* player){
    if(player->moveDir == 'a'){
        player->d.srcrect.x--;
    }
    if(player->moveDir == 'd'){
        player->d.srcrect.x++;        
    }
    if(player->moveDir == 'w'){
        player->d.srcrect.y--;        
    }
    if(player->moveDir == 's'){
        player->d.srcrect.y++;        
    }
}