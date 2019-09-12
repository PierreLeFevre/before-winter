#include "./include/bin/Game.h"

int main()
{
    int noExit = 1;
    Game g;
    ConstructGame(&g, &noExit);
    while(noExit){
        Go(&g);
    }
    DestroyGame(&g);
    return 0;
}