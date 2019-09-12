#include "./include/bin/Game.h"

int main()
{
    int noExit = 1;
    Game g;
    
    ConstructGame(&g, &noExit);
    
    g.tm.topleft_x = 0;
    g.tm.topleft_y = 0;

    while(noExit){
        Go(&g);
    }
    DestroyGame(&g);
    return 0;
}