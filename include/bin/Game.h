#include "Drawable.h"
#include "Player.h"
#include "TileMap.h"
#include "Camera.h"
#include "Animal.h"
#include "Gui.h"
#include "DroppedItem.h"
#include "Keys.h"
#include "DateTime.h"
#include "QuickSlot.h"
#include "Plants.h"

#define MAXPLANTS 100
#define MAXDROPS 2
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

    Plant plants[MAXPLANTS];
    int nPlants;
    Gui gui;

    //TEMP
    int nDroppedItems;
    DroppedItem **droppedItems;
    //----
    DateTime dateTime;
} Game;
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

void CreateAllStandardItems(Game *g);
void EntityDeathEvent(Game *g, Entity *e);

// TMP
void CreatePlantsToPlayer(Game *g);
// TMP
int TryPlacePlant(Game *g, PlantEnum plant);
void TryHarvestPlant(Game *g, Plant *plant);
void DeletePlant(Game *g, Plant *plant);

void DrawableMerge(Drawable *DrawablesCurrentSort[], int l, int m, int r);
void DrawableMergeSort(Drawable *DrawablesCurrentSort[], int l, int r);
void ChangeActiveItem(Player *player, int index);
PlantEnum ItemToPlant(Item *i);