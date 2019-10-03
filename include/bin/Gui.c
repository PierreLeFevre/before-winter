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
    g->menuSelectedIndex = 0;
    g->menuSelectToggler = 0;

    g->invActive = 0;
    g->invToggler = 0;

    g->promptToggler = 0;

    SDL_Rect char_srcrect = {0,0,10000,10000};
    SDL_Rect charToPrint_destRect = {0,0,0,0};
    ConstructDrawable(&g->charToPrint, DT_GUI, g->charToPrint.gfx, SS_FONT, char_srcrect, charToPrint_destRect, 20000);

    SDL_Rect gui_srcrect = {0,0,400,80};
    SDL_Rect gui_destrect = {80, 512, 440, 88};
    ConstructDrawable(&g->d, DT_GUI,g->d.gfx, SS_GUI, gui_srcrect, gui_destrect, 19999);

    SDL_Rect menu_srcrect = {26,106,350,350};
    SDL_Rect menu_destrect = {-25, -25, 650, 650};
    ConstructDrawable(&g->menu, DT_GUI,g->d.gfx, SS_GUI, menu_srcrect, menu_destrect, 19998);

    SDL_Rect msgBox_srcrect = {0,80,400,400};
    SDL_Rect messageBox_destrect = {75, 50, 450, 450};
    ConstructDrawable(&g->messageBox, DT_GUI,g->d.gfx, SS_GUI, msgBox_srcrect, messageBox_destrect, 19997);

    SDL_Rect inv_srcrect = {0,80,400,400};
    SDL_Rect inv_destrect = {75, 50, 440, 440};
    ConstructDrawable(&g->inv, DT_GUI,g->d.gfx, SS_GUI, inv_srcrect, inv_destrect, 19995);

    SDL_Rect prompt_srcrect = {0,480,400,80};
    SDL_Rect prompt_destrect = {0, 0, 300, 60};
    ConstructDrawable(&g->promptBg, DT_GUI,g->d.gfx, SS_GUI, prompt_srcrect, prompt_destrect, 19994);
}

void UpdateGui(Gui* g){
    //FPS Counter
    g->last = g->now;

    g->now = SDL_GetTicks();
    double dT = 1/((double)(g->now-g->last)/1000);

    char strFPS[100];
    gcvt(round(dT), 6, strFPS);
    RenderText(g, 15, g->d.gfx->wHeight-25, 0, White, Bold, strFPS);

    
    GuiMenu(g);
    
    if (!g->menuActive){
        GuiBar(g);
        GuiInventory(g);
        GuiPrompt(g);
        GuiMsgBox(g);
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

        Draw(&g->charToPrint);

        if(text[i] != '\n')
        {
            x += 10;
        }

        i++;
    }
}

void MsgBoxShow(Gui* g, char message[201]){
    strcpy(g->message, message);
    g->messageActive = 1;
}

void GuiBar(Gui* g){    
    //Draw gui box
    g->d.destrect.x = g->d.gfx->wWidth/2 - g->d.destrect.w/2;
    int x = g->d.destrect.x;
    g->d.destrect.y = g->d.gfx->wHeight - g->d.destrect.h;
    int y = g->d.destrect.y;
    Draw(&g->d);

    //Render gui text

    RenderText(g, x+50, y+15, 0, White, Bold, "Spring, Day 15");
    RenderText(g, x+250, y+15, 0, White, Bold, "Clear $$1716C");

    RenderText(g, x+50, y+40, 0, Yellow, Bold, "Gold:");
    char gold[100];
    gcvt(g->p->ent.Gold, 6, gold);
    RenderText(g, x+100, y+40, 0, Yellow, Regular, gold);

    char health[100];
    gcvt(g->p->ent.health, 6, health);
    if(g->p->ent.health > 20)
    {
        RenderText(g, x+250, y+40, 0, White, Bold, "HP:");
        RenderText(g, x+300, y+40, 0, Green, Bold, health);
    }
    else
    {
        RenderText(g, x+250, y+40, 0, Red, Bold, "HP:");
        RenderText(g, x+300, y+40, 0, Red, Bold, health);
    }

    RenderText(g, x+50, y+65, 0, White, Bold, "Equipped:");
    RenderText(g, x+150, y+65, 0, White, Regular, g->p->activeItem.Name);
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
                g->inv.destrect.x = g->inv.gfx->wWidth/2 - g->inv.destrect.w/2;
                int x = g->inv.destrect.x;
                g->inv.destrect.y = g->inv.gfx->wHeight/2 - g->inv.destrect.h/2;
                int y = g->inv.destrect.y;
                Draw(&g->inv);

                Draw(&g->inv);
                
                RenderText(g, x + (g->inv.destrect.w /2) - 50, y+25, 0, White, Bold, "Inventory:");
                int rows = 0;
                int xOffset;
                
                for (int i = 0; i < INVENTORY_SIZE; i++)
                { 
                    if (i%10 == 0)
                    {
                        rows++;
                        xOffset = 0;
                    }
                    //RenderText(g, x+25, (y+50 + 20 * i), 0, White, Regular, g->p->ent.items[i].Name);

                    g->p->ent.items[i].d.destrect.x = x + 50 + 36 * xOffset;
                    g->p->ent.items[i].d.destrect.y = y + 50 + 36 * rows;
                    g->p->ent.items[i].d.destrect.w = 32;
                    g->p->ent.items[i].d.destrect.h = 32;

                    Draw(&g->p->ent.items[i].d);

                    xOffset++;
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
    g->menu.destrect.w = g->d.gfx->wWidth + 50;
    int x = g->d.destrect.w/2;
    g->menu.destrect.h = g->d.gfx->wHeight + 50;
    //int y = g->d.destrect.h/2;

    //Draw debug window
    const Uint8 *Keys = SDL_GetKeyboardState(NULL);
    if (g->menuToggler > 20)
    {
        if(g->menuActive){
            g->menuSelectToggler += 1;

            if (Keys[SDL_SCANCODE_ESCAPE]){
                g->menuActive = 0;
                g->menuToggler = 0;
            }
            if(g->menuSelectToggler >= 5){

                if (Keys[SDL_SCANCODE_DOWN]){
                    if(g->menuSelectedIndex != 3){

                        if(g->menuSelectedIndex < 8)
                        g->menuSelectedIndex += 1;
                    
                    }
                    else{
                        g->menuSelectedIndex += 2;
                    }
                }
                
                if (Keys[SDL_SCANCODE_UP]){
                    if(g->menuSelectedIndex != 5){

                        if(g->menuSelectedIndex > 0)
                        g->menuSelectedIndex -= 1;
                    
                    }
                    else{
                        g->menuSelectedIndex -= 2;
                    }
                }

                if (Keys[SDL_SCANCODE_LEFT]){
                    switch (g->menuSelectedIndex)
                    {
                    case 0:
                        g->p->ent.movement_speed -= 5;
                        break;
                    case 1:
                        g->p->ent.friction -= .1;
                        break;
                    case 5:
                        g->d.gfx->wWidth -= 10;
                        SDL_SetWindowSize(g->d.gfx->win, g->d.gfx->wWidth, g->d.gfx->wHeight);    
                        break;
                    case 6:
                        g->d.gfx->wHeight -= 10;
                        SDL_SetWindowSize(g->d.gfx->win, g->d.gfx->wWidth, g->d.gfx->wHeight);    
                        break;
                    case 7:
                        g->d.gfx->wFullscreen = 0;
                        break;
                    default:
                        break;
                    }
                }
                if (Keys[SDL_SCANCODE_RIGHT]){
                    switch (g->menuSelectedIndex)
                    {
                    case 0:
                        g->p->ent.movement_speed += 5;
                        break;
                    case 1:
                        g->p->ent.friction += .1;
                        break;
                    case 5:
                        g->d.gfx->wWidth += 10;
                        SDL_SetWindowSize(g->d.gfx->win, g->d.gfx->wWidth, g->d.gfx->wHeight);    
                        break;
                    case 6:
                        g->d.gfx->wHeight += 10;
                        SDL_SetWindowSize(g->d.gfx->win, g->d.gfx->wWidth, g->d.gfx->wHeight);    
                        break;
                    case 7:
                        g->d.gfx->wFullscreen = 1;
                        break;
                    default:
                        break;
                    }                    
                }
                if (Keys[SDL_SCANCODE_RETURN]){
                    switch (g->menuSelectedIndex)
                    {
                    case 2:
                        saveToFile();
                        break;
                    case 3:
                        loadFromFile();
                        break;
                    }
                }

                g->menuSelectToggler = 0;
            }


            Draw(&g->menu);

            SDL_Rect selectRect = {100, 120 + g->menuSelectedIndex * 20, 300, 20};
            SDL_SetRenderDrawColor(g->d.gfx->rend, 255, 255, 255, 1);
            SDL_RenderDrawRect(g->d.gfx->rend, &selectRect);

            RenderText(g, x-90, 40, 0, White, Bold, "~~~ MENU ~~~");

            RenderText(g, 65, 100, 0, White, Bold, "~~~ Game Options");

            RenderText(g, 65, 120, 0, White, Bold, "    Player Speed");
            char playerSpeed[100];
            gcvt(g->p->ent.movement_speed, 6, playerSpeed);
            RenderText(g, 275, 120, 0, White, Regular, playerSpeed);

            RenderText(g, 65, 140, 0, White, Bold, "    Player Friction");
            char playerFriction[100];
            gcvt(g->p->ent.friction, 6, playerFriction);
            RenderText(g, 275, 140, 0, White, Regular, playerFriction);

            RenderText(g, 65, 160, 0, White, Bold, "    Save to file");
            RenderText(g, 65, 180, 0, White, Bold, "    Load from file");


            RenderText(g, 65, 200, 0, White, Bold, "~~~ Graphics Options");
            RenderText(g, 65, 220, 0, White, Bold, "    Window width");
            char wWidth[100];
            gcvt(g->d.gfx->wWidth, 6, wWidth);
            RenderText(g, 275, 220, 0, White, Regular, wWidth);

            RenderText(g, 65, 240, 0, White, Bold, "    Window height");
            char wHeight[100];
            gcvt(g->d.gfx->wHeight, 6, wHeight);
            RenderText(g, 275, 240, 0, White, Regular, wHeight);

            RenderText(g, 65, 260, 0, White, Bold, "    Fullscreen");

            if(g->d.gfx->wFullscreen){
                SDL_SetWindowFullscreen(g->d.gfx->win, 1);
                RenderText(g, 275, 260, 0, White, Regular, "ON");
            }else{
                SDL_SetWindowFullscreen(g->d.gfx->win, 0);
                RenderText(g, 275, 260, 0, White, Regular, "OFF");
            }


            RenderText(g, 65, 300, 0, White, Bold, "~~~ Debug Info");

            RenderText(g, 125, 340, 0, White, Bold, "X:          Y:");

            char xPos[100];
            gcvt(g->p->ent.d.destrect.x, 6, xPos);
            RenderText(g, 170, 340, 0, White, Regular, xPos);

            char yPos[100];
            gcvt(g->p->ent.d.destrect.y, 6, yPos);
            RenderText(g, 275, 340, 0, White, Regular, yPos);

            RenderText(g, 190, 560, 0, White, Bold, "[L/-] [UP/DOWN] [R/+]");
        }
        else
        { 
            if (Keys[SDL_SCANCODE_ESCAPE]) {
                g->menuSelectedIndex = 0;
                g->menuSelectToggler = 0;
                g->menuActive = 1;
                g->menuToggler = 0;
            }
        }
    }

    g->menuToggler += 1;
}

void GuiMsgBox(Gui* g){
    g->messageBox.destrect.x = g->messageBox.gfx->wWidth/2 - g->messageBox.destrect.w/2;
    int x = g->messageBox.destrect.x;
    g->messageBox.destrect.y = g->messageBox.gfx->wHeight/2 - g->messageBox.destrect.h/2;
    int y = g->messageBox.destrect.y;

    const Uint8 *Keys = SDL_GetKeyboardState(NULL);
    if(g->messageActive){

        if (Keys[SDL_SCANCODE_RETURN]){
            g->messageActive = 0;
        }

        //Draw message box
        if(g->messageActive){
            //Draw msgBox background
            Draw(&g->messageBox);
            
            //Draw message text
            RenderText(g, x+25, y+25, 0, White, Regular, g->message);

            RenderText(g, x + g->messageBox.destrect.w/2 - 15*12*.5, y + g->messageBox.destrect.h - 25, 0, White, Bold, "[RETURN] To close");
        }    
    }
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

        Draw(&g->promptBg);
        RenderText(g, 20, round(y) - 7, 0, White, Bold, g->promptText);

        g->promptToggler -= 1;
    }
}

void AlertGui(Gui* g, int timer, char promptText[100]){
    strcpy(g->promptText, promptText);
    g->promptToggler = 60*timer;
    g->promptInit = g->promptToggler;
}