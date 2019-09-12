#include "Drawable.h"
#include "TileMap.h"
#include "Player.h"

typedef enum GameState 
{Startmenu} 
GameState;

typedef struct Game{
    Graphics gfx;
    int CurrentGameState;
    TileMap tm;
    Player player;
    SDL_Event event;

    int* noExit;
}Game;

void ConstructGame(Game *g, int* noExit);
void DestroyGame(Game *g);

void Go(Game *g);

void UpdateLogic(Game *g);
void Render(Game *g);

void HandleEvents(Game* g);