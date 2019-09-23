#include <stdlib.h>
#include <string.h>

#include "Gui.h"

void ConstructGui(Gui* g, Graphics* gfx, Player* p){
    g->d.gfx = gfx;
    g->p = p;
    g->d.destrect.x = 100;
    g->d.destrect.y = 500;
    g->d.destrect.w = 400;
    g->d.destrect.h = 100;

    ConstructDrawable(&g->d, g->d.gfx, "include/assets/guibox.png", g->d.destrect, 19999);
}

void UpdateGui(Gui* g){
    DrawGuiBoxes(g);

    RenderText(g, 160, 520, 1, "Gold:");
    //RenderText(g, 220, 520, 1, IntToCharArray(g->p->ent.Gold));

    RenderText(g, 160, 540, 1, "Items:");
    //RenderText(g, 235, 540, 1, g->p->ent.items[0]->Name);

    RenderText(g, 160, 560, 1, "HP: ");

    //RenderText(g, 190, 520, 1, IntToCharArray( g->p->ent.health ));
}

void DrawGuiBoxes(Gui* g){
    Draw(g->d);
}

void RenderText(Gui* g, int x, int y, int b, char text[]){

    Drawable charToPrint;

    SDL_Rect destrect = {x, y, 17, 18};

    ConstructDrawable(&charToPrint, g->d.gfx, "include/assets/BW_ASCII.png", destrect, 20000);

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
        
        charToPrint.destrect.x = x;
        charToPrint.destrect.y = y;
        charToPrint.destrect.w = 17;
        charToPrint.destrect.h = 18;

        charToPrint.srcrect.x = 17 * ( text[i] - 32);
        charToPrint.srcrect.y = b * 18;
        charToPrint.srcrect.w = 17;
        charToPrint.srcrect.h = 18;

        Draw(charToPrint);

        if(text[i] != '\n')
        {
            x += 10;
        }

        i++;
    }
}