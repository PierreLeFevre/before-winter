#include "Drawable.h"
#include "Player.h"
#include "TileMap.h"
#include "Camera.h"
#include "Animal.h"
#include "Gui.h"
#include "DroppedItem.h"
#include "Keys.h"

#define MAXPLANTS 100

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
    Drawable **RenderList;
    int nToRender;
    //----

    TileMap tileMap;
    Tile **GoodTiles;
    int nGoodTiles;
    Player player;
    Animal animals[100];
    int n_animals;

    Item CoreItems[100];
    int BuyItemCooldown;

    Plant plants[MAXPLANTS];
    int nPlants;
    Gui gui;
    Keys keys;
    Pressed Key_Pressed;

    //TEMP
    Item item;
    DroppedItem d_item;
    //----
} Game;
void Input(SDL_Event *e, GameState gs, Game *g);
void ConstructGame(Game *g, int *noExit);
void DestroyGame(Game *g);

void Go(Game *g);

void UpdateLogic(Game *g);
void Render(Game *g);

void HandleEvents(Game *g);
void Key_Options(Game *g);

void CalculateGoodTiles(Game *g);

void AddToRenderList(Game *g, Drawable *d);
void AddTileMapToRenderList(Game *g);
void RenderList(Game *g);
void SortRenderList(Game *g);

void CreateAllStandardItems(Game *g);
void EntityDeathEvent(Game *g, Entity *e);

void TryPlacePlant(Game *g, PlantEnum plant);
void TryHarvestPlant(Game *g, Plant *plant);
void DeletePlant(Game *g,Plant *plant);