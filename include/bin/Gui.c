#include <stdlib.h>
#include <string.h>

#include "Gui.h"

void ConstructGui(Gui* g, Graphics* gfx, Player* p){
    g->d.gfx = gfx;
    g->charToPrint.gfx = gfx;
    g->messageBox.gfx = gfx;
    g->p = p;

    g->messageActive = 0;

    SDL_Rect gui_destrect = {100, 500, 400, 100};
    ConstructDrawable(&g->d, g->d.gfx, "include/assets/guibox.png", gui_destrect, 19999);

    SDL_Rect messageBox_destrect = {50, 50, 500, 400};
    ConstructDrawable(&g->messageBox, g->messageBox.gfx, "include/assets/guibox.png", messageBox_destrect, 19998);

    SDL_Rect charToPrint_destRect = {0,0,0,0};
    ConstructDrawable(&g->charToPrint, g->charToPrint.gfx, "include/assets/BW_ASCII.png", charToPrint_destRect, 20000);

    MsgBoxShow(g, 0); //Turn messagebox on or off: 1= active, 0 = off
    MsgBoxText(g, ""); //Set text for messageBox
}

void UpdateGui(Gui* g){

    //Draw gui box
    Draw(g->d);

    //Render gui text
    RenderText(g, 160, 520, 1, "Gold:");
    char gold[100];
    gcvt(g->p->ent.Gold, 6, gold);
    RenderText(g, 220, 520, 1, gold);

    RenderText(g, 320, 520, 1, "HP: ");
    char health[100];
    gcvt(g->p->ent.health, 6, health);
    RenderText(g, 365, 520, 1, health);

    RenderText(g, 160, 540, 1, "Items:");
    RenderText(g, 235, 540, 1, g->p->ent.items[0]->Name);
    
    const Uint8 *Keys = SDL_GetKeyboardState(NULL);
    if(g->messageActive){

        if (Keys[SDL_SCANCODE_ESCAPE]) {
            MsgBoxShow(g, 0);
        }

        //Draw message box
        Draw(g->messageBox);

        //Draw message text
        RenderText(g, 65, 80, 0, g->message);
        
        RenderText(g, 65, 100, 0, "X:          Y:");

        char xPos[100];
        gcvt(g->p->ent.d.destrect.x, 6, xPos);
        RenderText(g, 65, 120, 0, xPos);

        char yPos[100];
        gcvt(g->p->ent.d.destrect.y, 6, yPos);
        RenderText(g, 185, 120, 0, yPos);
    }
    else
    { 
        if (Keys[SDL_SCANCODE_ESCAPE]) {
            MsgBoxShow(g, 1);
        }
    }
    

}

void RenderText(Gui* g, int x, int y, int b, char text[]){

    SDL_Rect destrect = {x, y, 17, 18};
     
    g->charToPrint.destrect = destrect;

    int xStart = x;

    int i = 0;

    while (1){
        /*TMP REMOVE DOTT
        if (strlen(text) -1 == i){
            if (text[i] == '.'){
                return;
            }
        }
        */
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

void MsgBoxShow(Gui* g, int messageActive){
    g->messageActive = messageActive;
}

void MsgBoxText(Gui* g, char message[201]){
    strcpy(g->message, message);
}