#ifndef GUI_H
#define GUI_H

#include "Drawable.h"
#include "Player.h"
#include "FuncLib.h"

typedef struct Gui{
    Drawable d;
    Drawable menu;
    Drawable inv;

    Drawable charToPrint;

    Drawable messageBox;
    char message[201];
    int messageActive;

    int menuActive;
    int menuToggler;

    int invActive;
    int invToggler;

    char promptText[20];
    int promptToggler;
    
    Player* p;

}Gui;

typedef enum Color{
    Black,  // 0
    White,  // 1
    Red,    // 2
    Green,  // 3
    Yellow, // 4
    Blue,   // 5
    Magenta,// 6
    Cyan    // 7
}Color;

typedef enum Format{
    Regular,
    Bold
}Format;

void ConstructGui(Gui* g, Graphics* gfx, Player* p);
void UpdateGui(Gui* g);
void RenderText(Gui* g, int x, int y, int w, Color c, Format f, char text[]);

void MsgBoxShow(Gui* g, int messageActive);
void MsgBoxText(Gui* g, char message[201]);
void GuiInventory(Gui* g);
void GuiMenu(Gui* g);
void GuiPrompt(Gui* g);
void guiPingToggler(Gui* g, int timer, char promptText[20]);

#endif