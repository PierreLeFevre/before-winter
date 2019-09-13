#include "Player.h"
#include <stdio.h>

void ConstructPlayer(Player* player, Graphics* gfx){
    player->x_vel = 2.0f;
    player->y_vel = 2.0f;
    player->x_dir = 0;
    player->y_dir = 0;

    player->img_path = "./include/assets/character_set.png";
    SDL_Rect src = {3 * TILE_WIDTH, 3 * TILE_HEIGHT, 120, 120};
    SDL_Rect dest = {0, 0, 18, 18};
    ConstructDrawable(&player->d, gfx, player->img_path, src);
    DrawableSetDestrect(&player->d, dest);
    ChangeImagePath(&player->d, player->img_path);
}

void UpdatePlayer(Player* player){
    UpdatePlayerDirection(player);
    MovePlayer(player);
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
}

void DrawPlayer(Player* player){
    player->d.srcrect.y -= player->d.srcrect.h - TILE_HEIGHT;
    Draw(player->d);
    player->d.srcrect.y += player->d.srcrect.h - TILE_HEIGHT;
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