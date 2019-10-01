#include "./include/bin/Game.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int noExit = 1;
    Game g;

    ConstructGame(&g, &noExit);
    while (noExit)
    {
        Go(&g); //THIS IS A init() FUNKTION
    }
    DestroyGame(&g);
    return 0;
}