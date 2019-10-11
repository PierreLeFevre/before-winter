#ifndef GUI_H
#define GUI_H

#include "Drawable.h"
#include "Player.h"
#include "FuncLib.h"
#include "DateTime.h"
#include "Plants.h"
#include "saveLoadExit.h"

typedef struct Gui
{
    Drawable d;
    Drawable menu;
    Drawable inv;
    Drawable shaders;
    Drawable shopBg;

    Drawable charToPrint;

    Drawable messageBox;
    char message[201];
    int messageActive;

    int menuActive;
    int menuToggler;
    int menuSelectedIndex;
    int menuSelectToggler;
    int saveSlot;

    int shopActive;
    int shoptoggler;
    int shopPage;
    int shopSelectedIndex;
    int shopMaxIndex;
    int shopSelectToggler;
    int shopOrder[100];

    int invActive;
    int invToggler;

    Drawable promptBg;
    char promptText[100];
    int promptToggler;
    int promptInit;

    ExitData extidata;

    Player *p;

    Uint32 last;
    Uint32 now;

    DateTime *dT;
} Gui;

typedef enum Color
{
    Black,   // 0
    White,   // 1
    Red,     // 2
    Green,   // 3
    Yellow,  // 4
    Blue,    // 5
    Magenta, // 6
    Cyan     // 7
} Color;

typedef enum Format
{
    Regular,
    Bold
} Format;

void ConstructGui(Gui *g, Graphics *gfx, Player *p, DateTime *d);
void UpdateGui(Gui *g);
void SortInventory(Gui *g);
void RenderText(Gui *g, int x, int y, int w, Color c, Format f, char text[]);
// each char 15 wide.

void MsgBoxShow(Gui *g, char message[201]);
void MsgBoxHide(Gui *g);

void GuiShaders(Gui *g);

void GuiBar(Gui *g);
void GuiInventory(Gui *g);
void GuiMenu(Gui *g);
void GuiShop(Gui *g);
void GuiPrompt(Gui *g);
void GuiMsgBox(Gui *g);
void AlertGui(Gui *g, int timer, char promptText[20]);

#endif