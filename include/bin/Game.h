#include "Drawable.h"
#include "TileMap.h"

typedef enum GameState 
{Startmenu} 
GameState;

typedef struct Game{
    Graphics gfx;
    int CurrentGameState;
    TileMap tm;
}Game;

void ConstructGame(Game *g);
void DestroyGame(Game *g);

void Go(Game *g, SDL_Event *event);

void UpdateLogic(Game *g);
void Render(Game *g);

void Input();