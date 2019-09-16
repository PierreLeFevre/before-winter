#include "Drawable.h"
#include "Player.h"
#include "TileMap.h"
#include "Camera.h"
#include "Entity.h"

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
    Drawable* RenderList[5000];
//----

    TileMap tileMap;
    Player player;
    Entity entities[ENTITY_LENGTH];
}Game;
void Input(SDL_Event *e, GameState gs, Game *g);
void ConstructGame(Game *g, int* noExit);
void DestroyGame(Game *g);

void Go(Game *g);

void UpdateLogic(Game *g);
void Render(Game *g);

void HandleEvents(Game* g);

void AddToRenderList(Game* g, Drawable* d, int* nToRender);
void RenderList(Game* g, int* nToRender);
void SortRenderList(Game* g, int* nToRender);