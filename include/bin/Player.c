#include "Player.h"
#include <stdio.h>
#include <string.h>
#include "FuncLib.h"
#include "Entity.h"

void ConstructPlayer(Player *player, Graphics *gfx)
{
    player->ent.movement_speed = 2.0f;
    player->ent.accaleration = 1.1f;
    player->ent.friction = 0.6f;
    player->ent.health = 100;
    player->ent.Gold = 10000;
    player->itemAttractionRange = 50.0f;
    player->itemPickupRange = 15.0f;

    SDL_Rect destrect = {6 * TILE_WIDTH, 9 * TILE_HEIGHT, TILE_HEIGHT, TILE_HEIGHT * 2};
    SDL_Rect srcrect = {0, 0, 18, 18};

    Drawable d;
    ConstructDrawable(&d, DT_Player, gfx, SS_PLAYER, srcrect, destrect, 0);
    ConstructEntity(&player->ent, &d);

    UpdatePlayerHitbox(player);
}

void UpdatePlayer(Player *player)
{
    UpdatePlayerDirection(player);
    UpdateEntity(&player->ent);

    UpdateItemPreview(player, &player->activeItem);
    UpdatePlayerHitbox(player);
}

void UpdateItemPreview(Player *player, Item *i)
{
    player->activeItem.d = i->d;
    player->activeItem.d.z_index = player->ent.d.z_index;

    player->activeItem.d.destrect.x = player->ent.d.destrect.x + 15;
    player->activeItem.d.destrect.y = player->ent.d.destrect.y - 35;
}
void UpdatePlayerDirection(Player *player)
{
    player->ent.x_dir = 0.0f;
    player->ent.y_dir = 0.0f;
    player->ent.x_dir += (EventHandler("1RIGHT=") || EventHandler("2RIGHT=")) - (EventHandler("2LEFT=") || EventHandler("1LEFT="));
    player->ent.y_dir += (EventHandler("1DOWN=") || EventHandler("2DOWN=")) - (EventHandler("1UP=") || EventHandler("2UP="));

    AnimatePlayer(player);
}

void UpdatePlayerHitbox(Player *player)
{
    Entity *e = &player->ent;
    e->hitbox.x = e->d.destrect.x + 10;
    e->hitbox.y = e->d.destrect.y + e->d.destrect.h - 10;
    e->hitbox.w = e->d.destrect.w - 20;
    e->hitbox.h = 10;

    e->interaction_hitbox.x = e->hitbox.x + e->hitbox.w / 2 - e->interaction_hitbox_size / 2 + e->interaction_hitbox_offset * e->x_face;
    e->interaction_hitbox.y = e->hitbox.y + e->hitbox.h / 2 - e->interaction_hitbox_size / 2 + e->interaction_hitbox_offset * e->y_face / 1.5f;
    e->interaction_hitbox.w = e->interaction_hitbox_size;
    e->interaction_hitbox.h = e->interaction_hitbox_size;
}

void AnimatePlayer(Player *player)
{
    player->ent.d.srcrect.w = 16;
    player->ent.d.srcrect.h = 32;

    if (player->ent.x_dir != 0 || player->ent.y_dir != 0)
    {
        player->animationState += 1;
        //Choose direction in layer
        if (player->ent.y_dir == -1)
        {
            player->ent.d.srcrect.y = 64;
        }
        if (player->ent.y_dir == 1)
        {
            player->ent.d.srcrect.y = 0;
        }
        if (player->ent.x_dir == -1)
        {
            player->ent.d.srcrect.y = 96;
        }
        if (player->ent.x_dir == 1)
        {
            player->ent.d.srcrect.y = 32;
        }
        //Animate steps
        if (player->animationState == 0)
        {
            player->ent.d.srcrect.x = 16;
        }
        if (player->animationState == 10)
        {
            player->ent.d.srcrect.x = 32;
        }
        if (player->animationState == 20)
        {
            player->ent.d.srcrect.x = 48;
        }
        if (player->animationState == 30)
        {
            player->ent.d.srcrect.x = 0;
        }
        if (player->animationState == 40)
        {
            player->animationState = -1;
        }
    }
    else
    {
        player->animationState = -1;
        player->ent.d.srcrect.x = 0;
    }
}