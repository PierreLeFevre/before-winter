#include "Player.h"
#include <stdio.h>

void ConstructPlayer(Player* player, Graphics* gfx){
    player->x_vel = 2.0f;
    player->y_vel = 2.0f;
    player->x_dir = 0;
    player->y_dir = 0;

    player->img_path = "./include/assets/character_set.png";
    SDL_Rect src = {0 * TILE_WIDTH, 0 * TILE_HEIGHT, 60, 60};//he's not dumd thick
    SDL_Rect dest = {0, 0, 18, 18};
    player->hitbox.x = src.x;
    player->hitbox.y = src.y;
    player->hitbox.w = src.w - 10;
    player->hitbox.h = src.h - 10;

    ConstructDrawable(&player->d, gfx, player->img_path, src, 0);
    DrawableSetDestRect(&player->d, dest);
    ChangeImagePath(&player->d, player->img_path);
}

void UpdatePlayer(Player* player){
    UpdatePlayerDirection(player);
    MovePlayer(player);
    player->d.z_index = ((player->d.srcrect.y + player->d.srcrect.h) / TILE_HEIGHT) * TILE_Z_INDEX_MAX + Map((player->d.srcrect.y + player->d.srcrect.h) % TILE_HEIGHT, 0, TILE_HEIGHT, 0, TILE_Z_INDEX_MAX); //Row 1 = 15, Row 2 = 25....
}

void UpdatePlayerDirection(Player* player){
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

    AnimatePlayer(player);
}

void MovePlayer(Player* player){    
    player->d.srcrect.x += player->x_vel * player->x_dir;
    player->d.srcrect.y += player->y_vel * player->y_dir;

    player->hitbox.x = player->d.srcrect.x;
    player->hitbox.y = player->d.srcrect.y;
    player->hitbox.w = player->d.srcrect.w - 10;
    player->hitbox.h = player->d.srcrect.h - 10;
}

void AnimatePlayer(Player* player){
    player->d.destrect.w = 16;
    player->d.destrect.h = 18;

    if(player->x_dir != 0 || player->y_dir != 0)
    {
        player->animationState += 1;

        //Choose direction in layer
        if (player->y_dir == -1)
        {
            player->d.destrect.y = 18;
        }
        if (player->y_dir == 1)
        {
            player->d.destrect.y = 0;
        }
        if (player->x_dir == -1)
        {
            player->d.destrect.y = 36;
        }
        if (player->x_dir == 1)
        {
            player->d.destrect.y = 54;
        }

        //Animate steps
        if (player->animationState == 0)
        {
            player->d.destrect.x = 16;
        }
        if (player->animationState == 10)
        {
            player->d.destrect.x = 0;
        }
        if (player->animationState == 20)
        {
            player->d.destrect.x = 32;
        }
        if (player->animationState == 30)
        {
            player->d.destrect.x = 0;
        }
        if (player->animationState == 40)
        {
            player->animationState = -1;
        }
    }
    else
    {
        player->animationState = -1;
        player->d.destrect.x = 0;
    }
    
    
    

}