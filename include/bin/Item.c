#include "Item.h"


void ConstructItem(Item *i, Graphics *gfx, char *FilePath){
    ConstructDrawable(&i->d, gfx, FilePath, i->d.destrect, 0);
}
void UpdateItem(Item *i, SDL_Rect r, int zDrawIndex){
    i->d.z_index = zDrawIndex;
    i->d.destrect = r;
}