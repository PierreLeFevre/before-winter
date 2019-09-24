#include <stdlib.h>
#include <string.h>

#include "Gui.h"

void ConstructGui(Gui* g, Graphics* gfx, Player* p){
    g->d.gfx = gfx;
    g->charToPrint.gfx = gfx;
    g->p = p;

    g->d.destrect.x = 100;
    g->d.destrect.y = 500;
    g->d.destrect.w = 400;
    g->d.destrect.h = 100;

    SDL_Rect destrect = {0,0,0,0};
    ConstructDrawable(&g->charToPrint, g->charToPrint.gfx, "include/assets/BW_ASCII.png", destrect, 20000);

    ConstructDrawable(&g->d, g->d.gfx, "include/assets/guibox.png", g->d.destrect, 19999);
}

void UpdateGui(Gui* g){
    DrawGuiBoxes(g);

    RenderText(g, 160, 520, 1, "Gold:");
    char gold[100];
    gcvt(g->p->ent.Gold, 6, gold);
    RenderText(g, 220, 520, 1, gold);

    RenderText(g, 160, 540, 1, "Items:");
    //RenderText(g, 235, 540, 1, g->p->ent.items[0]->Name);

    RenderText(g, 160, 560, 1, "HP: ");
    char health[100];
    gcvt(g->p->ent.health, 6, health);
    RenderText(g, 190, 560, 1, health);
}

void DrawGuiBoxes(Gui* g){
    Draw(g->d);
}

void RenderText(Gui* g, int x, int y, int b, char text[]){

    SDL_Rect destrect = {x, y, 17, 18};
     
    g->charToPrint.destrect = destrect;

    int xStart = x;

    int i = 0;

    while (1){

        if(text[i] == '\0')
        {
            break;
        }

        if(text[i] == '\n')
        {
            y+=18;
            x = xStart;
        }
        
        g->charToPrint.destrect.x = x;
        g->charToPrint.destrect.y = y;
        g->charToPrint.destrect.w = 17;
        g->charToPrint.destrect.h = 18;

        g->charToPrint.srcrect.x = 17 * ( text[i] - 32);
        g->charToPrint.srcrect.y = b * 18;
        g->charToPrint.srcrect.w = 17;
        g->charToPrint.srcrect.h = 18;

        Draw(g->charToPrint);

        if(text[i] != '\n')
        {
            x += 10;
        }

        i++;
    }
}