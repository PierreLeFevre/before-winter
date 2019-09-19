#ifndef GUI_H
#define GUI_H

#include "Drawable.h"

typedef struct Gui{
    Drawable d;

}Gui;

void ConstructGui(Gui* g, Graphics* gfx);
void UpdateGui(Gui* g);
void RenderText(Gui* g, int x, int y, int b, char text[]);

#endif