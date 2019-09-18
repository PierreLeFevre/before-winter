#include "Drawable.h"
#include "Player.h"
#include "TileMap.h"
#include "Camera.h"
#include "Animal.h"
typedef enum GameState
{
    Startmenu,
    Level1
} GameState;

typedef struct Game
{
    //BASE
    int *noExit;
    int CurrentGameState;
    Graphics gfx;
    SDL_Event event;
    Camera cam;
    Drawable** RenderList;
    int nToRender;
    //----

    TileMap tileMap;
    Tile** GoodTiles;
    int nGoodTiles;
    Player player;
    Animal animals[10];
    Item items[10];
}Game;
void Input(SDL_Event *e, GameState gs, Game *g);
void ConstructGame(Game *g, int *noExit);
void DestroyGame(Game *g);

void Go(Game *g);

void UpdateLogic(Game *g);
void Render(Game *g);

void HandleEvents(Game *g);

void CalculateGoodTiles(Game *g);

void AddToRenderList(Game *g, Drawable *d);
void AddTileMapToRenderList(Game *g);
void RenderList(Game *g);
void SortRenderList(Game *g);

int check_collision(SDL_Rect A, SDL_Rect B);