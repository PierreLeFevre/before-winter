#include "Tile.h"
#include "Camera.h"

typedef struct TileMap{
    Graphics* gfx;
    Tile* tiles;
    int nTiles_x;
    int nTiles_y;
    int tile_width;
    int tile_height;
    int topleft_x;
    int topleft_y;
    char* mapFile;
}TileMap;

typedef struct TileProperties{
    char* filePath;
    int drawable_x_offset;
    int drawable_y_offset;
    int drawable_width_offset;
    int drawable_height_offset;
    
    int hitbox_x_offset;
    int hitbox_y_offset;
    int hitbox_width_offset;
    int hitbox_height_offset;

    int z_index_offset;
}TileProperties;

typedef enum MapDataConverter{
    MUD,
    GRASS,
    TREE
}MapDataConverter;

void ConstructTileMap(TileMap* tm, Graphics* gfx, const int nTiles_x, const int nTiles_y, const int topleft_x, const int topleft_y, char* fullBackground);
TileProperties GetTilePropertiesData(const MapDataConverter mdc);

void ApplyTileProperties(TileMap* tm, TileProperties* tp, Drawable* d, SDL_Rect* srcrect, SDL_Rect* hitbox, int index);
