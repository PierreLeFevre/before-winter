#include "Entity.h"
void ConstructEntity(Entity e[ENTITY_LENGTH], Graphics *g){
    ConstructDrawable(&e->d, g, e->img_path, e->d.srcrect, 1);
    DrawableSetDestRect(&e->d, e->d.srcrect);
    ChangeImagePath(&e->d, e->img_path);
}
void UpdateEntity(Entity e[ENTITY_LENGTH]){
    MoveEntitySoft(e);
}
void MoveEntitySoft(Entity e[ENTITY_LENGTH])
{
    e->nrFrame++;
    if (e->nrFrame == 60)
    {
        e->nrFrame = 0;
        e->d.srcrect.x += e->x_dir;
        e->d.srcrect.y += e->y_dir;
    }
}