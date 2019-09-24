#ifndef GUI_H
#define GUI_H

#include "Drawable.h"
#include "Player.h"
#include "FuncLib.h"

typedef struct Gui{
    Drawable d;
    Drawable charToPrint;
    Player* p;

}Gui;

void ConstructGui(Gui* g, Graphics* gfx, Player* p);
void UpdateGui(Gui* g);
void DrawGuiBoxes(Gui* g);
void RenderText(Gui* g, int x, int y, int b, char text[]);

#endif