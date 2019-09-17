#include "Entity.h"
#include <stdio.h>
void ConstructEntity(Entity *e, Graphics *g){

    e->img_path = "./include/assets/cow_set.png";
    SDL_Rect src = {10 * TILE_WIDTH, 10 * TILE_HEIGHT, 124, 200};
    SDL_Rect dest = {40, 40, 40, 100};
    ConstructDrawable(&e->d, g, e->img_path, src, 0);
    DrawableSetDestRect(&e->d, dest);
    ChangeImagePath(&e->d, e->img_path);
}
void UpdateEntity(Entity *e){
    MoveEntitySoft(e);
    e->d.z_index = ((e->d.srcrect.y + e->d.srcrect.h)/ TILE_HEIGHT + 1) * 10 + 5;
}
void MoveEntitySoft(Entity *e)
{
    e->nrFrame++;
    if (e->nrFrame == 60)
    {
        e->nrFrame = 0;
        e->d.srcrect.x += e->x_dir;
        e->d.srcrect.y += e->y_dir;
    }
}