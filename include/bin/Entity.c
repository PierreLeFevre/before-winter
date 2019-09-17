#include "Entity.h"
#include <stdio.h>
#include "FuncLib.h"
#include <time.h>
void ConstructEntity(Entity *e, Graphics* gfx, SDL_Rect srcrect, char* filePath){
    ConstructDrawable(&e->d, gfx, filePath, srcrect, 0);
}
void UpdateEntity(Entity *e){
    MoveEntity(e);
    e->d.z_index = ((e->d.srcrect.y + e->d.srcrect.h) / TILE_HEIGHT) * TILE_Z_INDEX_MAX + Map((e->d.srcrect.y + e->d.srcrect.h) % TILE_HEIGHT, 0, TILE_HEIGHT, 0, TILE_Z_INDEX_MAX); //Row 1 = 15, Row 2 = 25....
}

void MoveEntity(Entity* e){
    e->x_pos += e->x_vel * e->x_dir;
    e->y_pos += e->y_vel * e->y_dir;
    e->d.srcrect.x = e->x_pos;
    e->d.srcrect.y = e->y_pos;
}