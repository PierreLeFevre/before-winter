#include "Tile.h"

#define TILE_WIDTH 50
#define TILE_HEIGHT 50

typedef struct TileMap{
    Tile* tiles;
    int tiles_x;
    int tiles_y;
    int tile_width;
    int tile_height;
    int topleft_x;
    int topleft_y;
    float angle;
}TileMap;

void ConstructTileMap(TileMap* tm, Graphics* gfx, const int tiles_x, const int tiles_y, const int topleft_x, const int topleft_y);
void DrawTileMap(TileMap* tm);

void UpdateTileMap(TileMap* tm);