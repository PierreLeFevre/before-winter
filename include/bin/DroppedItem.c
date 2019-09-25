#include "DroppedItem.h"
#include "FuncLib.h"


void ConstructDroppedItem(DroppedItem* d_item, Item* item, float x_pos, float y_pos){
    d_item->item = item;
    d_item->x_desired = x_pos;
    d_item->y_desired = y_pos;
    SDL_Rect destrect = {x_pos, y_pos, 20, 20};
    ConstructEntity(&d_item->ent, d_item->ent.d.gfx, destrect, d_item->item->d.filePath);
}

void UpdateDroppedItem(DroppedItem* d_item, Player* player){
    UpdateEntity(&d_item->ent);

    //Player attracts dropped items
    if(Dist(player->ent.x_pos, player->ent.y_pos, d_item->ent.x_pos, d_item->ent.y_pos) < 30){
        //Generate a direction vector towards desired position
        if(d_item->ent.d.destrect.x < d_item->x_desired + 2 && d_item->ent.d.destrect.x > d_item->x_desired - 2 ){
            //Pick up item, add to inventory etc.
        }
        //----------------------------------------------------
        //Sets direction towards that position
        d_item->ent.x_dir = d_item->x_desired - d_item->ent.d.destrect.x;
        d_item->ent.y_dir = d_item->y_desired - d_item->ent.d.destrect.y;
        int length = Dist(0.0f, 0.0f, d_item->ent.x_dir, d_item->ent.y_dir);
        d_item->ent.x_dir /= length;
        d_item->ent.y_dir /= length;
        //------------------------------------

        d_item->ent.hitbox = d_item->ent.d.destrect;
    }
}