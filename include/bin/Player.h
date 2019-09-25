#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

typedef struct Player{
    Entity ent;
    Drawable itemPreview;
    Item* activeItem;
    
    int animationState;
} Player;

void ConstructPlayer(Player *player, Graphics *gfx);
void UpdatePlayer(Player *player);
void UpdateItemPreview(Player* player);
void UpdatePlayerDirection(Player *player);
void UpdatePlayerHitbox(Player *player);
void MovePlayer(Player *player);

void DrawPlayer(Player *player);
void AnimatePlayer(Player *player);

#endif