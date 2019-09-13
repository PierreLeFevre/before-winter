#include "Tile.h"

typedef struct TileMap{
    Tile* tiles;
    int nTiles_x;
    int nTiles_y;
    int tile_width;
    int tile_height;
    int topleft_x;
    int topleft_y;
    char* fullBackground;
}TileMap;

void ConstructTileMap(TileMap* tm, Graphics* gfx, const int nTiles_x, const int nTiles_y, const int topleft_x, const int topleft_y, char* fullBackground);
void DrawTileMap(TileMap* tm);

void UpdateTileMap(TileMap* tm);

void ChangeTileMapImage(TileMap* tm, const char* IMG_PATH);