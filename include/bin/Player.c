#include "Player.h"
#include <stdio.h>
#include <string.h>
#include "FuncLib.h"
#include "Entity.h"

void ConstructPlayer(Player* player, Graphics* gfx){
    player->ent.x_vel = 2.0f;
    player->ent.y_vel = 2.0f;

    SDL_Rect destrect = {6 * TILE_WIDTH, 9 * TILE_HEIGHT, 60, 60};
    SDL_Rect srcrect = {0, 0, 18, 18};

    ConstructEntity(&player->ent, gfx, destrect, "include/assets/character_set.png");
    player->ent.health = 100;
    player->ent.Gold = 0;
    
    CreateItem(&player->ent.items[0], gfx, IronAxeEnum);
    AddItem(&player->ent, &player->ent.items[0], 0);
    strcpy(player->ent.items[0].Name, "Iron Axe");

    CreateItem(&player->ent.items[1], gfx, IronPickaxeEnum);
    AddItem(&player->ent, &player->ent.items[1], 1);
    strcpy(player->ent.items[1].Name, "Iron Pickaxe");


    DrawableSetSrcRect(&player->ent.d, srcrect);

    UpdatePlayerHitbox(player);
}

void UpdatePlayer(Player *player)
{
    UpdatePlayerDirection(player);
    UpdateEntity(&player->ent);

    UpdateItemPreview(player, &player->ent.items[1]);

    UpdatePlayerHitbox(player);
}

void UpdateItemPreview(Player* player, Item *i){
    player->itemPreview = i->d;
    player->itemPreview.destrect.x = player->ent.d.destrect.x;
    player->itemPreview.destrect.y = player->ent.d.destrect.y -70;
}

void UpdatePlayerDirection(Player* player){
    player->ent.x_dir = 0.0f;
    player->ent.y_dir = 0.0f;
    const Uint8 *Keys = SDL_GetKeyboardState(NULL);
    SDL_PumpEvents();
    player->ent.x_dir += (Keys[SDL_SCANCODE_RIGHT] || Keys[SDL_SCANCODE_D]) - (Keys[SDL_SCANCODE_LEFT] || Keys[SDL_SCANCODE_A]);
    player->ent.y_dir += (Keys[SDL_SCANCODE_DOWN] || Keys[SDL_SCANCODE_S]) - (Keys[SDL_SCANCODE_UP] || Keys[SDL_SCANCODE_W]);
    
    AnimatePlayer(player);
}

void UpdatePlayerHitbox(Player* player){
    Entity* e = &player->ent;
    e->hitbox.x = e->d.destrect.x + 10;
    e->hitbox.y = e->d.destrect.y + e->d.destrect.h - 10;
    e->hitbox.w = e->d.destrect.w - 20;
    e->hitbox.h = 10;

    e->interaction_hitbox.x = e->hitbox.x + e->hitbox.w / 2 - e->interaction_hitbox_size / 2 + e->interaction_hitbox_offset * e->x_face;
    e->interaction_hitbox.y = e->hitbox.y + e->hitbox.h / 2 - e->interaction_hitbox_size / 2 + e->interaction_hitbox_offset * e->y_face / 1.5f;
    e->interaction_hitbox.w = e->interaction_hitbox_size;
    e->interaction_hitbox.h = e->interaction_hitbox_size;
}

void AnimatePlayer(Player* player){
    player->ent.d.srcrect.w = 16;
    player->ent.d.srcrect.h = 18;

    if(player->ent.x_dir != 0 || player->ent.y_dir != 0)
    {
        player->animationState += 1;
        //Choose direction in layer
        if (player->ent.y_dir == -1)
        {
            player->ent.d.srcrect.y = 18;
        }
        if (player->ent.y_dir == 1)
        {
            player->ent.d.srcrect.y = 0;
        }
        if (player->ent.x_dir == -1)
        {
            player->ent.d.srcrect.y = 36;
        }
        if (player->ent.x_dir == 1)
        {
            player->ent.d.srcrect.y = 54;
        }
        //Animate steps
        if (player->animationState == 0)
        {
            player->ent.d.srcrect.x = 16;
        }
        if (player->animationState == 10)
        {
            player->ent.d.srcrect.x = 0;
        }
        if (player->animationState == 20)
        {
            player->ent.d.srcrect.x = 32;
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
void CreateAllStandardItemsIntoCorrectSlot(Player *player, Graphics *gfx){
    CreateItem(&player->ent.items[0], gfx, IronAxeEnum);
    AddItem(&player->ent, &player->ent.items[0], 0);
    strcpy(player->ent.items[0].Name, "Iron Axe");

    CreateItem(&player->ent.items[1], gfx, IronPickaxeEnum);
    AddItem(&player->ent, &player->ent.items[1], 1);
    strcpy(player->ent.items[1].Name, "Iron Pickaxe");

    CreateItem(&player->ent.items[2], gfx, IronSwordEnum);
    AddItem(&player->ent, &player->ent.items[2], 2);
    strcpy(player->ent.items[2].Name, "Iron Sword");
}