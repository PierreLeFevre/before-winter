#include "Gui.h"

void ConstructGui(Gui* g, Graphics* gfx){
    g->d.gfx = gfx;
    g->d.destrect.x = 0;
    g->d.destrect.y = 0;
    g->d.destrect.w = 600;
    g->d.destrect.h = 600;
}

void UpdateGui(Gui* g){
    RenderText(g, 0, 0, 1, "HP: 10");
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