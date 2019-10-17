#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdio.h>
#include "Gui.h"

#include <errno.h>

void ConstructGui(Gui *g, Graphics *gfx, Player *p, DateTime *dT)
{
    g->d.gfx = gfx;
    g->charToPrint.gfx = gfx;
    g->messageBox.gfx = gfx;
    g->menu.gfx = gfx;
    g->inv.gfx = gfx;
    g->promptBg.gfx = gfx;
    g->shaders.gfx = gfx;
    g->shopBg.gfx = gfx;

    g->p = p;

    g->messageActive = 0;

    g->menuActive = 0;
    g->menuToggler = 0;
    g->menuSelectedIndex = 0;
    g->menuSelectToggler = 0;

    g->saveSlot = 1;

    g->shopActive = 0;
    g->shoptoggler = 0;
    g->shopPage = 0;
    g->shopMaxIndex = 1;
    g->shopSelectedIndex = 0;
    g->shopSelectToggler = 0;

    g->invActive = 0;
    g->invToggler = 0;
    g->invSelectedIndex = 0;
    g->invSelectToggler = 0;
    g->invHighlightedIndex = 0;
    g->invMovingState = 0;

    for (int i = 0; i < 100; i++)
    {
        g->shopOrder[i] = 0;
    }

    g->promptToggler = 0;

    g->dT = dT;

    SDL_Rect shader_src = {0, 0, 10000, 10000};
    SDL_Rect shader_destRect = {0, 0, g->d.gfx->wWidth, g->d.gfx->wHeight};
    ConstructDrawable(&g->shaders, DT_GUI, g->charToPrint.gfx, SS_SHADER, shader_src, shader_destRect, 20000);

    SDL_Rect char_srcrect = {0, 0, 10000, 10000};
    SDL_Rect charToPrint_destRect = {0, 0, 0, 0};
    ConstructDrawable(&g->charToPrint, DT_GUI, g->charToPrint.gfx, SS_FONT, char_srcrect, charToPrint_destRect, 20000);

    SDL_Rect gui_srcrect = {0, 0, 400, 80};
    SDL_Rect gui_destrect = {80, 512, 440, 88};
    ConstructDrawable(&g->d, DT_GUI, g->d.gfx, SS_GUI, gui_srcrect, gui_destrect, 19999);

    SDL_Rect menu_srcrect = {100, 106, 50, 350};
    SDL_Rect menu_destrect = {-25, -25, 300, 300};
    ConstructDrawable(&g->menu, DT_GUI, g->d.gfx, SS_GUI, menu_srcrect, menu_destrect, 19998);

    SDL_Rect msgBox_srcrect = {0, 80, 400, 400};
    SDL_Rect messageBox_destrect = {75, 50, 450, 450};
    ConstructDrawable(&g->messageBox, DT_GUI, g->d.gfx, SS_GUI, msgBox_srcrect, messageBox_destrect, 19997);

    SDL_Rect shop_srcrect = {100, 106, 50, 350};
    SDL_Rect shop_destrect = {-25, -25, 425, 300};
    ConstructDrawable(&g->shopBg, DT_GUI, g->d.gfx, SS_GUI, shop_srcrect, shop_destrect, 19996);

    SDL_Rect inv_srcrect = {100, 106, 50, 350};
    SDL_Rect inv_destrect = {-25, 0, 425, 300};
    ConstructDrawable(&g->inv, DT_GUI, g->d.gfx, SS_GUI, inv_srcrect, inv_destrect, 19995);

    SDL_Rect prompt_srcrect = {0, 480, 400, 80};
    SDL_Rect prompt_destrect = {0, 0, 300, 60};
    ConstructDrawable(&g->promptBg, DT_GUI, g->d.gfx, SS_GUI, prompt_srcrect, prompt_destrect, 19994);
}

void UpdateGui(Gui *g)
{
    //Draw shaders on game to represent lighting at different times of day
    GuiShaders(g);

    

    //FPS Counter
    g->last = g->now;

    g->now = SDL_GetTicks();
    double dT = 1 / ((double)(g->now - g->last) / 1000);

    char strFPS[100];
    gcvt(round(dT), 6, strFPS);
    RenderText(g, 15, g->d.gfx->wHeight - 25, 0, White, Bold, strFPS);

    GuiBar(g);
    SortInventory(g);
    GuiPrompt(g);
    GuiMsgBox(g);

    if(!g->invActive && !g->menuActive)
    GuiShop(g);
    
    if(!g->shopActive && !g->menuActive)
    GuiInventory(g);
    
    if(!g->invActive && !g->shopActive)
    GuiMenu(g);

    SDL_SetWindowFullscreen(g->d.gfx->win, g->d.gfx->wFullscreen);
}

void RenderText(Gui *g, int x, int y, int w, Color c, Format f, char text[])
{

    SDL_Rect destrect = {x, y, 17, 18};

    g->charToPrint.destrect = destrect;

    int xStart = x;

    int i = 0;

    while (1)
    {
        /*TMP REMOVE DOTT
        if (strlen(text) -1 == i){
            if (text[i] == '.'){
                return;
            }
        }
        */
        if (text[i] == '\0')
        {
            break;
        }

        if (text[i] == '\n')
        {
            y += 18;
            x = xStart;
        }

        if (text[i] == '$' && text[i + 1] == '$')
        {
            f = text[i + 2] - 48;
            c = text[i + 3] - 48;
            i += 4;
        }

        if (x - xStart >= w && w != 0)
        {
            y += 18;
            x = xStart;
        }

        g->charToPrint.destrect.x = x;
        g->charToPrint.destrect.y = y;
        g->charToPrint.destrect.w = 17;
        g->charToPrint.destrect.h = 18;

        g->charToPrint.srcrect.x = 17 * (text[i] - 32);
        g->charToPrint.srcrect.y = f * 18 + 2 * c * 18;
        g->charToPrint.srcrect.w = 17;
        g->charToPrint.srcrect.h = 18;

        Draw(&g->charToPrint);

        if (text[i] != '\n')
        {
            x += 10;
        }

        i++;
    }
}

void MsgBoxShow(Gui *g, char message[201])
{
    strcpy(g->message, message);
    g->messageActive = 1;
}

void GuiShaders(Gui *g)
{
    if (g->dT->hour > 16)
    {
        g->shaders.srcrect.x = 16;
        g->shaders.srcrect.y = 48;
        g->shaders.srcrect.w = 16;
        g->shaders.srcrect.h = 16;
        if (g->dT->hour > 18)
        {
            g->shaders.srcrect.y = 32;
        }
        if (g->dT->hour > 20)
        {
            g->shaders.srcrect.y = 16;
        }
        if (g->dT->hour > 22)
        {
            g->shaders.srcrect.y = 0;
        }
    }
    else
    {
        g->shaders.srcrect.w = 0;
        g->shaders.srcrect.h = 0;
    }

    g->shaders.destrect.x = 0;
    g->shaders.destrect.y = 0;
    g->shaders.destrect.w = g->d.gfx->wWidth;
    g->shaders.destrect.h = g->d.gfx->wHeight;

    Draw(&g->shaders);
}

void GuiBar(Gui *g)
{
    //Draw gui box
    g->d.destrect.x = g->d.gfx->wWidth / 2 - g->d.destrect.w / 2;
    int x = g->d.destrect.x;
    g->d.destrect.y = g->d.gfx->wHeight - g->d.destrect.h;
    int y = g->d.destrect.y;
    Draw(&g->d);

    //Render gui text

    char guiDateTime[100];
    switch (g->dT->season)
    {
    case Spring:
        sprintf(guiDateTime, "Spring, Day %d  %d:%d", g->dT->day, g->dT->hour, g->dT->min);
        break;
    case Summer:
        sprintf(guiDateTime, "Summer, Day %d  %d:%d", g->dT->day, g->dT->hour, g->dT->min);
        break;
    case Fall:
        sprintf(guiDateTime, "Fall, Day %d  %d:%d", g->dT->day, g->dT->hour, g->dT->min);
        break;
    case Winter:
        sprintf(guiDateTime, "Winter, Day %d  %d:%d", g->dT->day, g->dT->hour, g->dT->min);
        break;
    }

    RenderText(g, x + 50, y + 15, 0, White, Bold, guiDateTime);

    if (g->dT->hour >= 22 && g->dT->hour < 23)
    {
        AlertGui(g, 2, "It will soon be night.");
    }

    RenderText(g, x + 50, y + 40, 0, Yellow, Bold, "Gold:");
    char gold[100];
    gcvt(g->p->ent.Gold, 6, gold);
    RenderText(g, x + 100, y + 40, 0, Yellow, Regular, gold);

    char health[100];
    gcvt(g->p->ent.health, 6, health);
    if (g->p->ent.health > 20)
    {
        RenderText(g, x + 250, y + 40, 0, White, Bold, "HP:");
        RenderText(g, x + 300, y + 40, 0, Green, Bold, health);
    }
    else
    {
        RenderText(g, x + 250, y + 40, 0, Red, Bold, "HP:");
        RenderText(g, x + 300, y + 40, 0, Red, Bold, health);
    }

    RenderText(g, x + 50, y + 65, 0, White, Bold, "Equipped:");
    RenderText(g, x + 150, y + 65, 0, White, Regular, g->p->activeItem.Name);
}

void SortInventory(Gui *g)
{
    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        for (int j = (i + 1); j < INVENTORY_SIZE; j++)
        {
            if (g->p->ent.items[i].exists)
            {
                if (strcmp(g->p->ent.items[i].Name, g->p->ent.items[j].Name) == 0)
                {
                    g->p->ent.items[j].exists = 0;
                    strcpy(g->p->ent.items[j].Name, "");
                    g->p->ent.items[i].amount += g->p->ent.items[j].amount;
                    g->p->ent.items[j].amount = 0;
                }
            }
        }
    }

    g->p->ent.n_items = 0;
    for (int i = 0; i < INVENTORY_SIZE; i++)
    {
        if (!g->p->ent.items[i].exists)
        {
            break;
        }
        g->p->ent.n_items += 1;
    }
}

void GuiInventory(Gui *g)
{
    if (g->invToggler > 20)
    {
        if (g->invActive)
        {
            g->invSelectToggler++;

            if (EventHandler("inventory="))
            {
                g->invActive = 0;
                g->invToggler = 0;
            }
            else
            {
                g->inv.destrect.x = g->inv.gfx->wWidth - 400;
                int x = g->inv.destrect.x;
                g->inv.destrect.h = g->inv.gfx->wHeight;
                Draw(&g->inv);

                RenderText(g, x + (g->inv.destrect.w / 2) - 50, 25, 0, White, Bold, "Inventory:");
                int rows = 0;

                for (int i = 0; i < g->p->ent.n_items; i++)
                {
                    //RenderText(g, x+25, (y+50 + 20 * i), 0, White, Regular, g->p->ent.items[i].Name);

                    g->p->ent.items[i].d.destrect.x = x + 32;
                    g->p->ent.items[i].d.destrect.y = 50 + 36 * rows;
                    g->p->ent.items[i].d.destrect.w = 32;
                    g->p->ent.items[i].d.destrect.h = 32;

                    if (g->p->ent.items[i].exists != 0)
                    {
                        Draw(&g->p->ent.items[i].d);

                        char inventoryText[200];
                        sprintf(inventoryText, "%d: [%d] %s", i+1, g->p->ent.items[i].amount, g->p->ent.items[i].Name);
                        if(g->invMovingState){
                            if(i == g->invHighlightedIndex){
                                RenderText(g, x + 80, 50 + 9 + 36 * rows, 0, Cyan, Bold, inventoryText);
                            }else{
                                RenderText(g, x + 80, 50 + 9 + 36 * rows, 0, White, Regular, inventoryText);
                            }
                        }else{
                            RenderText(g, x + 80, 50 + 9 + 36 * rows, 0, White, Bold, inventoryText);
                        }
                    }

                    rows++;
                }

                if (g->invSelectToggler >= 5)
                {
                    if (EventHandler("1DOWN="))
                    {
                        if(g->invSelectedIndex < g->p->ent.n_items -1)
                        g->invSelectedIndex++;
                        g->invSelectToggler = 0;
                    }
                    if (EventHandler("1UP="))
                    {
                        if (g->invSelectedIndex >= 1)
                        g->invSelectedIndex--;
                        g->invSelectToggler = 0;
                    }
                    if (EventHandler("Select=")){
                        if(g->invMovingState){
                            Item temp = g->p->ent.items[g->invSelectedIndex];
                            g->p->ent.items[g->invSelectedIndex] = g->p->ent.items[g->invHighlightedIndex];
                            g->p->ent.items[g->invHighlightedIndex] = temp;
                            g->invMovingState = 0;
                        }else{
                            g->invHighlightedIndex = g->invSelectedIndex;
                            g->invMovingState = 1;
                        }
                        g->invSelectToggler = 0;
                    }
                }

                RenderText(g, x+5, 50 + 9 + 36 * g->invSelectedIndex, 0, White, Bold, ">");
                RenderText(g, g->d.gfx->wWidth - 70, 50 + 9 + 36 * g->invSelectedIndex, 0, White, Bold, "[Enter]");
            }
        }
        else
        {
            if (EventHandler("inventory="))
            {
                g->invActive = 1;
                g->invToggler = 0;
            }
        }
    }

    g->invToggler += 1;
}

void GuiMenu(Gui *g)
{
    g->menu.destrect.h = g->d.gfx->wHeight + 50;
    //int y = g->d.destrect.h/2;

    //Draw debug window
    if (g->menuToggler > 20)
    {
        if (g->menuActive)
        {
            g->menuSelectToggler += 1;

            if (EventHandler("meny="))
            {
                g->menuActive = 0;
                g->menuToggler = 0;
            }
            if (g->menuSelectToggler >= 5)
            {
                if (EventHandler("1DOWN="))
                {
                    switch (g->menuSelectedIndex)
                    {
                    case 16:
                        break;
                    case 4:
                    case 9:
                        g->menuSelectedIndex += 3;
                        break;
                    case 14:
                        g->menuSelectedIndex += 2;
                        break;
                    default:
                        g->menuSelectedIndex += 1;
                        break;
                    }
                }

                if (EventHandler("1UP="))
                {
                    switch (g->menuSelectedIndex)
                    {
                    case 0:
                        break;
                    case 3:
                    case 7:
                        g->menuSelectedIndex -= 3;
                        break;

                    case 16:
                        g->menuSelectedIndex -= 2;
                        break;
                    default:
                        g->menuSelectedIndex -= 1;
                        break;
                    }
                }

                if (EventHandler("1LEFT="))
                {
                    switch (g->menuSelectedIndex)
                    {
                    case 0:
                        if (g->saveSlot > 1)
                        {
                            g->saveSlot -= 1;
                        }
                        break;
                    case 7:
                        g->p->ent.movement_speed -= 1;
                        break;
                    case 8:
                        g->p->ent.friction -= .1;
                        break;
                    case 9:
                        g->dT->timeScale -= 10;
                        break;
                    case 12:
                        g->d.gfx->wWidth -= 10;
                        SDL_SetWindowSize(g->d.gfx->win, g->d.gfx->wWidth, g->d.gfx->wHeight);
                        break;
                    case 13:
                        g->d.gfx->wHeight -= 10;
                        SDL_SetWindowSize(g->d.gfx->win, g->d.gfx->wWidth, g->d.gfx->wHeight);
                        break;
                    default:
                        break;
                    }
                }
                if (EventHandler("1RIGHT="))
                {
                    switch (g->menuSelectedIndex)
                    {
                    case 0:
                        if (g->saveSlot < 5)
                        {
                            g->saveSlot += 1;
                        }
                        break;
                    case 7:
                        g->p->ent.movement_speed += 1;
                        break;
                    case 8:
                        g->p->ent.friction += .1;
                        break;
                    case 9:
                        g->dT->timeScale += 10;
                        break;
                    case 12:
                        g->d.gfx->wWidth += 10;
                        SDL_SetWindowSize(g->d.gfx->win, g->d.gfx->wWidth, g->d.gfx->wHeight);
                        break;
                    case 13:
                        g->d.gfx->wHeight += 10;
                        SDL_SetWindowSize(g->d.gfx->win, g->d.gfx->wWidth, g->d.gfx->wHeight);
                        break;
                    default:
                        break;
                    }
                }
                if (EventHandler("Select="))
                {
                    char saveFilePath[21];
                    sprintf(saveFilePath, "Saves/save%d.sav", g->saveSlot);
                    switch (g->menuSelectedIndex)
                    {
                    case 1:
                        g->exitdata.exitInitialized = SDL_TRUE;
                        break;
                    case 2:
                        saveToFile(saveFilePath, &g->p->ent.x_pos, &g->p->ent.y_pos);
                        g->exitdata.exitInitialized = SDL_TRUE;
                        break;
                    case 3:
                        saveToFile(saveFilePath, &g->p->ent.x_pos, &g->p->ent.y_pos);
                        break;
                    case 4:
                        loadFromFile(saveFilePath, &g->p->ent.x_pos, &g->p->ent.y_pos);
                        break;
                    case 14:
                        if (g->d.gfx->wFullscreen)
                        {
                            g->d.gfx->wFullscreen = 0;
                        }
                        else
                        {
                            g->d.gfx->wFullscreen = 1;
                        }
                        break;
                    case 16:
                        //// SAVE OPTIONS
                        break;
                    }
                }

                g->menuSelectToggler = 0;
            }

            Draw(&g->menu);

            RenderText(g, 5, 118 + g->menuSelectedIndex * 18, 0, White, Bold, ">");
            if ((g->menuSelectedIndex >= 1 && g->menuSelectedIndex <= 4) || g->menuSelectedIndex > 13)
            {
                RenderText(g, 205, 118 + g->menuSelectedIndex * 18, 0, White, Bold, "[Enter]");
            }
            else
            {
                RenderText(g, 215, 118 + g->menuSelectedIndex * 18, 0, White, Bold, "[<][>]");
            }

            RenderText(g, 30, 40, 0, White, Bold, "~~~~~~~~ MENU ~~~~~~~~");

            char saveGame[100];
            sprintf(saveGame, "~~~ Game\nSlot: [%d]\nQuit\nSave & Quit\nSave\nLoad", g->saveSlot);
            RenderText(g, 20, 100, 0, White, Bold, saveGame);

            char playerOptions[100];
            sprintf(playerOptions, "~~~ Player Options\nSpeed: [%.f]\nFriction: [%.1f]\nTimescale: [%d]", g->p->ent.movement_speed, g->p->ent.friction, g->dT->timeScale);
            RenderText(g, 20, 226, 0, White, Bold, playerOptions);

            char graphicsOptions[100];
            sprintf(graphicsOptions, "~~~ Window Options\nWidth: [%d]\nHeight: [%d]", g->d.gfx->wWidth, g->d.gfx->wHeight);
            RenderText(g, 20, 316, 0, White, Bold, graphicsOptions);

            if (!g->d.gfx->wFullscreen)
            {
                RenderText(g, 20, 370, 0, White, Bold, "Fullscreen mode");
            }
            else
            {
                RenderText(g, 20, 370, 0, White, Bold, "Windowed mode");
            }

            RenderText(g, 20, 406, 0, White, Bold, "Save options");
        }
        else
        {
            if (EventHandler("meny="))
            {
                g->menuSelectToggler = 0;
                g->menuActive = 1;
                g->menuToggler = 0;
            }
        }
    }

    g->menuToggler += 1;
}

void GuiShop(Gui *g)
{
    g->shopBg.destrect.h = g->d.gfx->wHeight + 50;

    if (g->shoptoggler > 20)
    {
        if (g->shopActive)
        {
            Draw(&g->shopBg);

            if (EventHandler("shop="))
            {
                g->shopActive = 0;
                g->shoptoggler = 0;
                g->shopSelectToggler = 0;
            }

            if (EventHandler("1UP=") && g->shopSelectToggler > 20)
            {
                switch (g->shopSelectedIndex)
                {
                case 0:
                    break;
                default:
                    g->shopSelectedIndex -= 1;
                    break;
                }
                g->shopSelectToggler = 0;
            }

            if (EventHandler("1DOWN=") && g->shopSelectToggler > 20)
            {
                if (g->shopSelectedIndex != g->shopMaxIndex)
                {
                    g->shopSelectedIndex += 1;
                }
                g->shopSelectToggler = 0;
            }

            g->shopSelectToggler += 1;

            RenderText(g, 5, 140 + g->shopSelectedIndex * 18, 0, White, Bold, ">");

            switch (g->shopPage)
            {
            case 0:
                g->shopMaxIndex = 1;
                //MAIN HOME PAGE ----- PAGE 0
                RenderText(g, 20, 100, 0, White, Bold, "Welcome home!");

                //Options
                RenderText(g, 20, 140, 0, White, Bold, "Go to sleep");
                RenderText(g, 20, 158, 0, White, Bold, "Go to the store");
                RenderText(g, 20, g->d.gfx->wHeight - 58, 0, White, Bold, "Press [F] to exit");
                if (g->dT->hour == 23 && g->dT->min == 55){
                    g->dT->timeScale = 2;
                }

                //
                if (EventHandler("Select=") && g->shopSelectToggler > 20)
                {
                    switch (g->shopSelectedIndex)
                    {
                    case 0:
                        g->dT->timeScale = 2000;
                        break;
                    case 1:
                        g->shopPage = 1;
                    }
                    g->shopSelectedIndex = 0;
                    g->shopSelectToggler = 0;
                }

                RenderText(g, 330, 140 + g->shopSelectedIndex * 18, 0, White, Bold, "[Enter]");
                break;

            case 1:
                g->shopMaxIndex = 1;
                //SHOP HOME PAGE ----- PAGE 1
                RenderText(g, 20, 100, 0, White, Bold, "Welcome to the store!");

                //Options
                RenderText(g, 20, 140, 0, White, Bold, "Buy seeds");
                RenderText(g, 20, 160, 0, White, Bold, "Sell plants");

                //
                if (EventHandler("Select=") && g->shopSelectToggler > 20)
                {
                    switch (g->shopSelectedIndex)
                    {
                    case 0:
                        g->shopPage = 2;
                        break;
                    case 1:
                        g->shopPage = 3;
                    }
                    g->shopSelectedIndex = 0;
                    g->shopSelectToggler = 0;
                }

                RenderText(g, 330, 140 + g->shopSelectedIndex * 18, 0, White, Bold, "[Enter]");
                break;
            case 2:
                g->shopMaxIndex = 8;
                //BUY SEEDS PAGE ----- PAGE 3
                RenderText(g, 20, 100, 0, White, Bold, "Please place your order.");

                //Options
                char shopOrderString[200];
                sprintf(shopOrderString, "Parsnip seeds [%d]\nCauliflwr seeds [%d]\nGarlic seeds [%d]\nRhubarb seeds [%d]\nTomato seeds [%d]\nWheat seeds[%d]\nCoffee beans [%d]\nStrawberry seeds [%d]\nPlace order", g->shopOrder[0], g->shopOrder[1], g->shopOrder[2], g->shopOrder[3], g->shopOrder[4], g->shopOrder[5], g->shopOrder[6], g->shopOrder[7]);
                RenderText(g, 20, 140, 0, White, Bold, shopOrderString);

                if (EventHandler("1LEFT=") && g->shopSelectToggler > 20)
                {
                    if (g->shopOrder[g->shopSelectedIndex] >= 6)
                        g->shopOrder[g->shopSelectedIndex] -= 6;
                    g->shopSelectToggler = 0;
                }

                if (EventHandler("1RIGHT=") && g->shopSelectToggler > 20)
                {
                    if (g->shopOrder[g->shopSelectedIndex] <= 30)
                        g->shopOrder[g->shopSelectedIndex] += 6;
                    g->shopSelectToggler = 0;
                }

                if (g->shopSelectedIndex > 7)
                {
                    RenderText(g, 330, 140 + g->shopSelectedIndex * 18, 0, White, Bold, "[Enter]");
                }
                else
                {
                    RenderText(g, 340, 140 + g->shopSelectedIndex * 18, 0, White, Bold, "[<][>]");
                }

                if (EventHandler("Select=") && g->shopSelectToggler > 20 && g->shopSelectedIndex == 8)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        if (g->shopOrder[i])
                        {
                            g->p->ent.Gold -= g->p->ent.items[i].Cost * g->shopOrder[i];
                            g->p->ent.items[g->p->ent.n_items] = SeedToItem(g->d.gfx, i, g->shopOrder[i]);
                            g->p->ent.n_items++;
                            SortInventory(g);
                        }
                    }
                    g->shopSelectToggler = 0;
                }

                break;

            case 3:
                g->shopMaxIndex = g->p->ent.n_items - 1;
                SortInventory(g);
                RenderText(g, 20, 100, 0, White, Bold, "Sell plants");

                int rows = 0;

                for (int i = 0; i < g->p->ent.n_items; i++)
                {
                    if (g->p->ent.items[i].exists != 0)
                    {
                        char inventoryText[200];
                        sprintf(inventoryText, "[%d] $$14(%d)$$11 %s", g->p->ent.items[i].amount, g->p->ent.items[i].SellValue, g->p->ent.items[i].Name);
                        if(g->invMovingState){
                            if(i == g->invHighlightedIndex){
                                RenderText(g, 20, 140 + 18 * rows, 0, Cyan, Bold, inventoryText);
                            }else{
                                RenderText(g, 20, 140 + 18 * rows, 0, White, Regular, inventoryText);
                            }
                        }else{
                            RenderText(g, 20, 140 + 18 * rows, 0, White, Bold, inventoryText);
                        }
                    }

                    rows++;
                }

                if (EventHandler("Select=") && g->shopSelectToggler > 20)
                {
                    if (g->p->ent.items[g->shopSelectedIndex].amount > 1)
                    {
                        g->p->ent.items[g->shopSelectedIndex].amount -= 1;
                        g->p->ent.Gold += g->p->ent.items[g->shopSelectedIndex].SellValue;
                    }else{
                        g->p->ent.items[g->shopSelectedIndex].exists = 0;
                        g->p->ent.Gold += g->p->ent.items[g->shopSelectedIndex].SellValue;
                    }
                    g->shopSelectToggler = 0;
                }

                g->shopSelectToggler++;
                break;
            
            }

            g->shopSelectToggler += 1;
        }
        else
        {
            //Opens Home-menu if player is next to home
            SDL_Rect home = {20*TILE_WIDTH, 9*TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT};
            if(SDL_HasIntersection(&g->p->ent.interaction_hitbox, &home)){
                g->shopActive = 1;
                g->shopPage = 0;
                g->shoptoggler = 0;
            }
        }
    }

    g->shoptoggler += 1;
}

void GuiMsgBox(Gui *g)
{
    g->messageBox.destrect.x = g->messageBox.gfx->wWidth / 2 - g->messageBox.destrect.w / 2;
    int x = g->messageBox.destrect.x;
    g->messageBox.destrect.y = g->messageBox.gfx->wHeight / 2 - g->messageBox.destrect.h / 2;
    int y = g->messageBox.destrect.y;

    if (g->messageActive)
    {

        if (EventHandler("Select="))
        {
            g->messageActive = 0;
        }

        //Draw message box
        if (g->messageActive)
        {
            //Draw msgBox background
            Draw(&g->messageBox);

            //Draw message text
            RenderText(g, x + 25, y + 25, 0, White, Regular, g->message);

            RenderText(g, x + g->messageBox.destrect.w / 2 - 15 * 12 * .5, y + g->messageBox.destrect.h - 25, 0, White, Bold, "[RETURN] To close");
        }
    }
}

void GuiPrompt(Gui *g)
{

    if (g->promptToggler > 0)
    {
        float percentage;
        int total = g->promptInit;
        int current = g->promptToggler;
        float y = 0;

        percentage = 100 - (float)current / total * 100.0;

        if (percentage <= 33)
        {
            y = -45 + 15 * (percentage / 100 * 12);
        }
        else if (percentage > 33 && percentage <= 66)
        {
            y = 15;
        }
        else if (percentage > 66)
        {
            y = -45 + 15 * ((100 - percentage) / 100 * 12);
        }

        g->promptBg.destrect.y = y - 30;

        Draw(&g->promptBg);
        RenderText(g, 20, round(y) - 7, 0, White, Bold, g->promptText);

        g->promptToggler -= 1;
    }
}

void AlertGui(Gui *g, int timer, char promptText[100])
{
    errno = 0;
    strcpy(g->promptText, promptText);
    g->promptToggler = 60 * timer;
    g->promptInit = g->promptToggler;
    if (errno != 0)
    {
        printf("Gui.c AlertGui %s\n", strerror(errno));
    }
}