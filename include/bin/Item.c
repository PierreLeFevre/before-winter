#include "Item.h"


void ConstructItem(Item* item, Graphics* gfx, char* file_path){
    SDL_Rect destrect = {50, 50, 50, 50};
    ConstructDrawable(&item->d, gfx, file_path, destrect, 100000);
}