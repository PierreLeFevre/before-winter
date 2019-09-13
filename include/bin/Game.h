#include "Drawable.h"
#include "Player.h"
#include "TileMap.h"
#include "Camera.h"

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
    Camera cam;
//----

    TileMap tileMap;
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