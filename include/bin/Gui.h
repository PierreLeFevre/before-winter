#ifndef GUI_H
#define GUI_H

#include "Drawable.h"
#include "Player.h"
#include "FuncLib.h"

typedef struct Gui{
    Drawable d;
    Drawable charToPrint;
    Drawable messageBox;
    char message[201];
    int messageActive;
    Player* p;

}Gui;

typedef enum Color{
    Black,
    White,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan
}Color;

typedef enum Format{
    Regular,
    Bold
}Format;

void ConstructGui(Gui* g, Graphics* gfx, Player* p);
void UpdateGui(Gui* g);
void RenderText(Gui* g, int x, int y, Color c, Format f, char text[]);

void MsgBoxShow(Gui* g, int messageActive);
void MsgBoxText(Gui* g, char message[201]);

#endif