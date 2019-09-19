#include "Gui.h"

void ConstructGui(Gui* g, Graphics* gfx){
    g->d.gfx = gfx;
    g->d.srcrect.x = 0;
    g->d.srcrect.y = 0;
    g->d.srcrect.w = 600;
    g->d.srcrect.h = 600;
}

void UpdateGui(Gui* g){
    RenderText(g, 0, 0, 1, "HP: 10");
}

void RenderText(Gui* g, int x, int y, int b, char text[]){

    Drawable charToPrint;

    SDL_Rect src = {x, y, 17, 18};

    ConstructDrawable(&charToPrint, g->d.gfx, "include/assets/BW_ASCII.png", src, 20000);

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
        
        charToPrint.srcrect.x = x;
        charToPrint.srcrect.y = y;
        charToPrint.srcrect.w = 17;
        charToPrint.srcrect.h = 18;

        charToPrint.destrect.x = 17 * ( text[i] - 32);
        charToPrint.destrect.y = b * 18;
        charToPrint.destrect.w = 17;
        charToPrint.destrect.h = 18;

        Draw(charToPrint);

        if(text[i] != '\n')
        {
            x += 10;
        }

        i++;
    }
}