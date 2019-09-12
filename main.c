#include "./include/bin/Game.h"
#include <stdio.h>
int main()
{
    int noExit = 1;
    Game g;
    ConstructGame(&g, &noExit);
    
    while(g.noExit){
        Go(&g);
    }
    DestroyGame(&g);
    return 0;
}