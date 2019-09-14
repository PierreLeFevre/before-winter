#include "Tile.h"

typedef struct TileMap{
    Tile* tiles;
    int nTiles_x;
    int nTiles_y;
    int tile_width;
    int tile_height;
    int topleft_x;
    int topleft_y;
    char* mapFile;
}TileMap;

typedef struct TileImage{
    char* filePath;
    int height;
    int y_offset;
}TileImage;

typedef enum MapDataConverter{
    MUD,
    GRASS
}MapDataConverter;

void ConstructTileMap(TileMap* tm, Graphics* gfx, const int nTiles_x, const int nTiles_y, const int topleft_x, const int topleft_y, char* fullBackground);

TileImage GetTileImageData(const MapDataConverter mdc);