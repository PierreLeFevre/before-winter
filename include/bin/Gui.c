#include <stdlib.h>
#include <string.h>

#include "Gui.h"

void ConstructGui(Gui* g, Graphics* gfx, Player* p){
    g->d.gfx = gfx;
    g->charToPrint.gfx = gfx;
    g->messageBox.gfx = gfx;
    g->menu.gfx = gfx;
    g->inv.gfx = gfx;

    g->p = p;

    g->messageActive = 0;

    g->menuActive = 0;
    g->menuToggler = 0;

    g->invActive = 0;
    g->invToggler = 0;

    g->promptToggler = 0;

    SDL_Rect charToPrint_destRect = {0,0,0,0};
    ConstructDrawable(&g->charToPrint, g->charToPrint.gfx, "include/assets/BW_ASCII_COLOR.png", charToPrint_destRect, 20000);

    SDL_Rect gui_destrect = {100, 500, 400, 100};
    ConstructDrawable(&g->d, g->d.gfx, "include/assets/guibox.png", gui_destrect, 19999);

    SDL_Rect menu_destrect = {50, 50, 500, 400};
    ConstructDrawable(&g->menu, g->menu.gfx, "include/assets/guibox.png", menu_destrect, 19998);

    SDL_Rect messageBox_destrect = {50, 50, 500, 400};
    ConstructDrawable(&g->messageBox, g->messageBox.gfx, "include/assets/guibox.png", messageBox_destrect, 19997);

    SDL_Rect inv_destrect = {50, 50, 500, 400};
    ConstructDrawable(&g->inv, g->inv.gfx, "include/assets/guibox.png", inv_destrect, 19995);


    MsgBoxShow(g, 0); //Turn messagebox on or off: 1= active, 0 = off
    MsgBoxText(g, ""); //Set text for messageBox
}

void UpdateGui(Gui* g){

    //Draw gui box
    Draw(g->d);

    //Render gui text
    RenderText(g, 160, 520, 0, Black, Regular, "Gold:");
    char gold[100];
    gcvt(g->p->ent.Gold, 6, gold);
    RenderText(g, 220, 520, 0, Green, Bold, gold);

    RenderText(g, 320, 520, 0, Black, Bold, "HP:");
    char health[100];
    gcvt(g->p->ent.health, 6, health);
    RenderText(g, 365, 520, 0, Red, Regular, health);

    RenderText(g, 160, 540, 0, Black, Bold, "Hand:");
    RenderText(g, 220, 540, 0, Black, Regular, g->p->activeItem.Name);
    
    //Draw message box
    if(g->messageActive){
        //Draw msgBox background
        Draw(g->menu);
        
        //Draw message text
        RenderText(g, 65, 80, 0, Red, Bold, g->message);
    }

    GuiInventory(g);
    GuiMenu(g);
    GuiPrompt(g);
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

void GuiInventory(Gui* g){
    //Draw debug window
    const Uint8 *Keys = SDL_GetKeyboardState(NULL);
    if (g->invToggler > 20)
    {
        if(g->invActive){

            if (Keys[SDL_SCANCODE_E]){
                g->invActive = 0;
                g->invToggler = 0;

                guiPingToggler(g, 3, "halloj");
            }
            else
            {
                Draw(g->menu);
                
                RenderText(g, 65, 100, 0, Black, Bold, "Inventory:");
                
                for (int i = 0; i < 10; i++)
                { 
                    RenderText(g, 65, (120 + 20 * i), 0, Black, Regular, g->p->ent.items[i].Name);
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
            
            RenderText(g, 65, 100, 0, Black, Bold, "X:          Y:");

            char xPos[100];
            gcvt(g->p->ent.d.destrect.x, 6, xPos);
            RenderText(g, 95, 100, 0, Black, Regular, xPos);

            char yPos[100];
            gcvt(g->p->ent.d.destrect.y, 6, yPos);
            RenderText(g, 215, 100, 0, Black, Regular, yPos);

            RenderText(g, 70, 160, 460, Black, Regular, "$$00hello $$10world $$01hello $$11world $$02hello $$12world $$03hello $$13world $$04hello $$14world $$05hello $$15world $$07hello $$17world");
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
        RenderText(g, 15, 15, 0, Black, Bold, g->promptText);
        g->promptToggler -= 1;
    }    
}

void guiPingToggler(Gui* g, int timer, char promptText[20]){
    strcpy(g->promptText, promptText);
    g->promptToggler = 60*timer;
}