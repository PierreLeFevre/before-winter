#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "Gui.h"

void ConstructGui(Gui* g, Graphics* gfx, Player* p){
    g->d.gfx = gfx;
    g->charToPrint.gfx = gfx;
    g->messageBox.gfx = gfx;
    g->menu.gfx = gfx;
    g->inv.gfx = gfx;
    g->promptBg.gfx = gfx;

    g->p = p;

    g->messageActive = 0;

    g->menuActive = 0;
    g->menuToggler = 0;

    g->invActive = 0;
    g->invToggler = 0;

    g->promptToggler = 0;

    SDL_Rect charToPrint_destRect = {0,0,0,0};
    ConstructDrawable(&g->charToPrint, g->charToPrint.gfx, "include/assets/BW_ASCII_COLOR.png", charToPrint_destRect, 20000);

    SDL_Rect gui_destrect = {80, 512, 440, 88};
    ConstructDrawable(&g->d, g->d.gfx, "include/assets/GuiBottom.png", gui_destrect, 19999);

    SDL_Rect menu_destrect = {-25, -25, 650, 650};
    ConstructDrawable(&g->menu, g->menu.gfx, "include/assets/guibox.png", menu_destrect, 19998);

    SDL_Rect messageBox_destrect = {75, 50, 450, 450};
    ConstructDrawable(&g->messageBox, g->messageBox.gfx, "include/assets/guibox.png", messageBox_destrect, 19997);

    SDL_Rect inv_destrect = {75, 50, 450, 450};
    ConstructDrawable(&g->inv, g->inv.gfx, "include/assets/guibox.png", inv_destrect, 19995);

    SDL_Rect prompt_destrect = {0, 0, 300, 60};
    ConstructDrawable(&g->promptBg, g->promptBg.gfx, "include/assets/GuiTop.png", prompt_destrect, 19994);


    MsgBoxShow(g, 0); //Turn messagebox on or off: 1= active, 0 = off
    MsgBoxText(g, ""); //Set text for messageBox
}

void UpdateGui(Gui* g){
    
    //Draw message box
    if(g->messageActive){
        //Draw msgBox background
        Draw(g->messageBox);
        
        //Draw message text
        RenderText(g, 65, 80, 0, Red, Bold, g->message);
    }
    
    GuiMenu(g);
    
    if (!g->menuActive){
        GuiBar(g);
        GuiInventory(g);
        GuiPrompt(g);
    }
}

void RenderText(Gui* g, int x, int y, int w, Color c, Format f, char text[]){

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

        if(text[i] == '$' && text[i+1] == '$')
        {
            f = text[i+2] - 48;
            c = text[i+3] - 48;
            i += 4;
        }

        if(x-xStart >= w && w != 0)
        {
            y+=18;
            x = xStart;
        }
        
        g->charToPrint.destrect.x = x;
        g->charToPrint.destrect.y = y;
        g->charToPrint.destrect.w = 17;
        g->charToPrint.destrect.h = 18;

        g->charToPrint.srcrect.x = 17 * ( text[i] - 32);
        g->charToPrint.srcrect.y = f * 18 + 2 * c * 18;
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

void GuiBar(Gui* g){    
    //Draw gui box
    Draw(g->d);

    //Render gui text

    RenderText(g, 120, 525, 0, White, Bold, "Spring, Day 15");
    RenderText(g, 320, 525, 0, White, Bold, "Clear $$1716C");

    RenderText(g, 120, 550, 0, Yellow, Bold, "Gold:");
    char gold[100];
    gcvt(g->p->ent.Gold, 6, gold);
    RenderText(g, 180, 550, 0, Yellow, Regular, gold);

    char health[100];
    gcvt(g->p->ent.health, 6, health);
    if(g->p->ent.health > 20)
    {
        RenderText(g, 320, 550, 0, White, Bold, "HP:");
        RenderText(g, 365, 550, 0, Green, Bold, health);
    }
    else
    {
        RenderText(g, 320, 550, 0, Red, Bold, "HP:");
        RenderText(g, 365, 550, 0, Red, Bold, health);
    }

    RenderText(g, 120, 575, 0, White, Bold, "Equipped:");
    RenderText(g, 220, 575, 0, White, Regular, g->p->activeItem.Name);
}

void GuiInventory(Gui* g){
    //Draw debug window
    const Uint8 *Keys = SDL_GetKeyboardState(NULL);
    if (g->invToggler > 20)
    {
        if(g->invActive){

            if (Keys[SDL_SCANCODE_E]){
                g->invActive = 0;
                g->invToggler = 0;
            }
            else
            {
                Draw(g->inv);
                
                RenderText(g, 90, 100, 0, White, Bold, "Inventory:");
                
                for (int i = 0; i < 10; i++)
                { 
                    RenderText(g, 90, (120 + 20 * i), 0, White, Regular, g->p->ent.items[i].Name);
                }
                
            }
        }
        else
        { 
            if (Keys[SDL_SCANCODE_E]) {
                g->invActive = 1;
                g->invToggler = 0;
            }
        }
    }

    g->invToggler += 1;
}

void GuiMenu(Gui* g){
    //Draw debug window
    const Uint8 *Keys = SDL_GetKeyboardState(NULL);
    if (g->menuToggler > 20)
    {
        if(g->menuActive){

            if (Keys[SDL_SCANCODE_ESCAPE]){
                g->menuActive = 0;
                g->menuToggler = 0;
            }

            Draw(g->menu);

            RenderText(g, 240, 40, 0, White, Bold, "~~~ MENU ~~~");

            RenderText(g, 65, 100, 0, White, Bold, "~~~ Game Options");


            RenderText(g, 65, 200, 0, White, Bold, "~~~ Graphics Options");


            RenderText(g, 65, 300, 0, White, Bold, "~~~ Debug Info");

            RenderText(g, 65, 330, 0, White, Bold, "X:          Y:");

            char xPos[100];
            gcvt(g->p->ent.d.destrect.x, 6, xPos);
            RenderText(g, 95, 330, 0, White, Regular, xPos);

            char yPos[100];
            gcvt(g->p->ent.d.destrect.y, 6, yPos);
            RenderText(g, 215, 330, 0, White, Regular, yPos);
        }
        else
        { 
            if (Keys[SDL_SCANCODE_ESCAPE]) {
                g->menuActive = 1;
                g->menuToggler = 0;
            }
        }
    }

    g->menuToggler += 1;
}

void GuiPrompt(Gui* g){
    
    if(g->promptToggler > 0)
    {
        float percentage;
        int total = g->promptInit;
        int current = g->promptToggler;
        float y = 0;


        percentage = 100 - (float)current / total * 100.0;

        if (percentage <= 33){
            y = - 45 + 15*(percentage/100*12);
        }
        else if (percentage > 33 && percentage <= 66){
            y = 15;
        }
        else if (percentage > 66){
            y = - 45 + 15*((100 - percentage)/100*12);
        }

        g->promptBg.destrect.y = y - 30;

        Draw(g->promptBg);
        RenderText(g, 20, round(y) - 7, 0, White, Bold, g->promptText);

        g->promptToggler -= 1;
    }
}

void AlertGui(Gui* g, int timer, char promptText[100]){
    strcpy(g->promptText, promptText);
    g->promptToggler = 60*timer;
    g->promptInit = g->promptToggler;
}