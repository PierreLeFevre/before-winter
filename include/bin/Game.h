#include "Drawable.h"
#include "TileMap.h"
#include "Player.h"
#include "Animal.h"

typedef enum GameState 
{Startmenu,
Level1} 
GameState;

typedef struct Game{
//BASE
    int* noExit;
    int CurrentGameState;
    Graphics gfx;
    SDL_Event event;
//----

    TileMap tileMapMAIN;
    TileMap tileMapBackground;
    Player player;
    Animal animal;
}Game;
void Input(SDL_Event *e, GameState gs, Game *g);
void ConstructGame(Game *g, int* noExit);
void DestroyGame(Game *g);

void Go(Game *g);

void UpdateLogic(Game *g);
void Render(Game *g);

void HandleEvents(Game* g);