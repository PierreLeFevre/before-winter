#include "DroppedItem.h"
#include "FuncLib.h"
#include <stdio.h>


void ConstructDroppedItem(DroppedItem* d_item, Item* item, Entity* ent){
    d_item->item = item;
    d_item->ent = *ent;
    d_item->x_desired = d_item->ent.x_pos;
    d_item->y_desired = d_item->ent.y_pos;    
    d_item->ent.movement_speed = 3.0f;
    d_item->ent.x_dir = 0.0f;
    d_item->ent.y_dir = 0.0f;
}

void UpdateDroppedItem(DroppedItem* d_item, Player* player){
    UpdateEntity(&d_item->ent);
    float player_attract_x = player->ent.hitbox.x + player->ent.hitbox.w / 2;
    float player_attract_y = player->ent.hitbox.y + player->ent.hitbox.h / 2;
    float d_item_attract_x = d_item->ent.d.destrect.x + d_item->ent.d.destrect.w / 2;
    float d_item_attract_y = d_item->ent.d.destrect.y + d_item->ent.d.destrect.h / 2;
    float distance = Dist(player_attract_x, player_attract_y, d_item_attract_x, d_item_attract_y);
    //Player attracts dropped items
    if(distance < player->itemAttractionRange && distance >= player->itemPickupRange){
        //Generate a direction vector towards desired position
        d_item->x_desired = player_attract_x;
        d_item->y_desired = player_attract_y;
        //----------------------------------------------------
        //Sets direction towards that position
        d_item->ent.x_dir = d_item->x_desired - d_item_attract_x;
        d_item->ent.y_dir = d_item->y_desired - d_item_attract_y;
        int length = Dist(0.0f, 0.0f, d_item->ent.x_dir, d_item->ent.y_dir);
        d_item->ent.x_dir /= length;
        d_item->ent.y_dir /= length;
        //------------------------------------
    }else{
        d_item->ent.x_dir = 0.0f;
        d_item->ent.y_dir = 0.0f;
    }
    if(distance < player->itemPickupRange){
        //Pick up item
    }

    d_item->ent.x_pos += d_item->ent.movement_speed * d_item->ent.x_dir;
    d_item->ent.y_pos += d_item->ent.movement_speed * d_item->ent.y_dir;

    d_item->ent.d.destrect.x = d_item->ent.x_pos;
    d_item->ent.d.destrect.y = d_item->ent.y_pos;
    d_item->ent.hitbox = d_item->ent.d.destrect;
}