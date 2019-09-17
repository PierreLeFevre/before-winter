#include "Player.h"
#include <stdio.h>
#include "FuncLib.h"

void ConstructPlayer(Player* player, Graphics* gfx){
    player->ent.x_vel = 2.0f;
    player->ent.y_vel = 2.0f;

    player->img_path = "./include/assets/character_set.png";
    SDL_Rect src = {1 * TILE_WIDTH, 0 * TILE_HEIGHT, 60, 60};
    SDL_Rect dest = {0, 0, 18, 18};
    ConstructEntity(&player->ent, gfx, src, player->img_path);
    DrawableSetDestRect(&player->ent.d, dest);

    UpdatePlayerHitbox(player);
}

void UpdatePlayer(Player *player)
{
    UpdatePlayerDirection(player);
    UpdateEntity(&player->ent);
    UpdatePlayerHitbox(player);
}

void UpdatePlayerDirection(Player* player){
    player->ent.x_dir = 0.0f;
    player->ent.y_dir = 0.0f;
    const Uint8 *Keys = SDL_GetKeyboardState(NULL);
    SDL_PumpEvents();
    if (Keys[SDL_SCANCODE_LEFT] || Keys[SDL_SCANCODE_A]) {
        player->ent.x_dir -= 1.0f;
    }
    if (Keys[SDL_SCANCODE_RIGHT] || Keys[SDL_SCANCODE_D]) {
        player->ent.x_dir += 1.0f;
    }
    if (Keys[SDL_SCANCODE_UP] || Keys[SDL_SCANCODE_W]) {
        player->ent.y_dir -= 1.0f;
    }
    if (Keys[SDL_SCANCODE_DOWN] || Keys[SDL_SCANCODE_S]) {
        player->ent.y_dir += 1.0f;
    }
    AnimatePlayer(player);
}

void UpdatePlayerHitbox(Player* player){
    player->ent.hitbox.x = player->ent.d.srcrect.x + 10;
    player->ent.hitbox.y = player->ent.d.srcrect.y + player->ent.d.srcrect.h - 10;
    player->ent.hitbox.w = player->ent.d.srcrect.w - 20;
    player->ent.hitbox.h = 10;
}

void AnimatePlayer(Player* player){
    player->ent.d.destrect.w = 16;
    player->ent.d.destrect.h = 18;

    if(player->ent.x_dir != 0 || player->ent.y_dir != 0)
    {
        player->animationState += 1;
        //Choose direction in layer
        if (player->ent.y_dir == -1)
        {
            player->ent.d.destrect.y = 18;
        }
        if (player->ent.y_dir == 1)
        {
            player->ent.d.destrect.y = 0;
        }
        if (player->ent.x_dir == -1)
        {
            player->ent.d.destrect.y = 36;
        }
        if (player->ent.x_dir == 1)
        {
            player->ent.d.destrect.y = 54;
        }
        //Animate steps
        if (player->animationState == 0)
        {
            player->ent.d.destrect.x = 16;
        }
        if (player->animationState == 10)
        {
            player->ent.d.destrect.x = 0;
        }
        if (player->animationState == 20)
        {
            player->ent.d.destrect.x = 32;
        }
        if (player->animationState == 30)
        {
            player->ent.d.destrect.x = 0;
        }
        if (player->animationState == 40)
        {
            player->animationState = -1;
        }
    }
    else
    {
        player->animationState = -1;
        player->ent.d.destrect.x = 0;
    }
}