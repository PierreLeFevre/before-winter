#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"

typedef struct TileMap{
    Graphics* gfx;
    Tile* tiles;
    char* map_file;
    Drawable sprite_sheet;
    int nTiles_x;
    int nTiles_y;
    int tile_width;
    int tile_height;
    int topleft_x;
    int topleft_y;

    int nTiles_used;

    int flowersOnGrassIntensity;

    SDL_Rect player_home_rect;
}TileMap;

typedef struct TileProperties{
    DrawableType type;

    int drawable_x_correct;
    int drawable_y_correct;
    int hitbox_x_correct;
    int hitbox_y_correct;

    SDL_Rect destrect_offset;
    SDL_Rect srcrect;
    SDL_Rect hitbox_offset;

    int z_index_offset;
}TileProperties;

typedef enum MapDataConverter{
    TRANSPARENT = 0,
    DIRT=1,
    SAND=3,
    GRASS=5,
    TREE=11,
    WATER=15,
    PLAYER_HOME=51,
    PLAYER_HOME_ROOF=52,
    PIER=55,
    PIER_EXTENSION=56
}MapDataConverter;

void ConstructTileMap(TileMap* tm, Graphics* gfx, const int nTiles_x, const int nTiles_y, const int topleft_x, const int topleft_y, char* map_file);
void DestroyTileMap(TileMap* tm);

void FixTileTransitions(TileMap* tm);

void DrawTileMap(TileMap* tm);

void TileMapChangeSpriteSheet(TileMap* tm, SpriteSheet spritesheet);

TileProperties GetTilePropertiesData(TileMap* tm, const MapDataConverter mdc);

void ApplyTileProperties(TileMap* tm, TileProperties* tp, Drawable* drawable, SDL_Rect* hitbox);


#endif