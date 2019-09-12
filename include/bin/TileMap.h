#include "Tile.h"

#define TILES_X 10
#define TILES_Y 10
#define TILE_WIDTH WINDOW_WIDTH / TILES_X
#define TILE_HEIGHT WINDOW_HEIGHT / TILES_Y

typedef struct TileMap{
    Tile tiles[TILES_X][TILES_Y];
}TileMap;

void ConstructTileMap(TileMap* tm, Graphics* gfx);
void DrawTileMap(TileMap* tm);