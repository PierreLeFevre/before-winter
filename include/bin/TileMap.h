#include "Tile.h"
#include "Camera.h"
#define TILE_Z_INDEX_MAX 100
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
    int drawable_height;
    int drawable_y_offset;
    
    int hitbox_x_offset;
    int hitbox_y_offset;
    int hitbox_width;
    int htibox_height;
}TileImage;

typedef enum MapDataConverter{
    MUD,
    GRASS,
    TREE
}MapDataConverter;

void ConstructTileMap(TileMap* tm, Graphics* gfx, const int nTiles_x, const int nTiles_y, const int topleft_x, const int topleft_y, char* fullBackground);
TileImage GetTileImageData(const MapDataConverter mdc);

void AddTileMapToRenderList(TileMap* tm, Camera* cam, Drawable** RenderList, int* nToRender);