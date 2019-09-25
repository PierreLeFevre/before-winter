#ifndef GUI_H
#define GUI_H

#include "Drawable.h"
#include "Player.h"
#include "FuncLib.h"

typedef struct Gui{
    Drawable d;
    Drawable charToPrint;
    Drawable messageBox;
    char message[101];
    int messageActive;
    Player* p;

}Gui;

void ConstructGui(Gui* g, Graphics* gfx, Player* p);
void UpdateGui(Gui* g);
void RenderText(Gui* g, int x, int y, int b, char text[]);

void MsgBoxShow(Gui* g, int messageActive);
void MsgBoxText(Gui* g, char message[101]);

#endif