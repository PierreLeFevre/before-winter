#include "include/SDL2/SDL.h"
#include "Graphics.h"

typedef struct Game{
    Graphics gfx;
}Game;

void ConstructGame(Game *g);
void DestroyGame(Game *g);

void Go(Game *g);

void UpdateLogic(Game *g);
void Draw(Game *g);