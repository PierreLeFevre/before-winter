#ifndef PLAYER_H
#define PLAYER_H
#include "Entity.h"

typedef struct Player{
    Entity ent;
    Item activeItem;
    int activeItemIndex;
    
    int animationState;

    float itemAttractionRange;
    float itemPickupRange;
}Player;

void ConstructPlayer(Player *player, Graphics *gfx);
void UpdatePlayer(Player *player);
void UpdateItemPreview(Player* player, Item *i);
void UpdatePlayerDirection(Player *player);
void UpdatePlayerHitbox(Player *player);
void MovePlayer(Player *player);

void DrawPlayer(Player *player);
void AnimatePlayer(Player *player);
#endif