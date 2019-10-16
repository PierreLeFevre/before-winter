#include "TileMap.h"
#include "FuncLib.h"

#include "../SDL2/SDL_image.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

void ConstructTileMap(TileMap* tm, Graphics* gfx, const int nTiles_x, const int nTiles_y, const int topleft_x, const int topleft_y, char* map_file){
    tm->gfx = gfx;
    tm->tiles = (Tile*) malloc(sizeof(Tile) * nTiles_x * nTiles_y);
    tm->nTiles_x = nTiles_x;
    tm->nTiles_y = nTiles_y;
    tm->topleft_x = topleft_x;
    tm->topleft_y = topleft_y;
    tm->map_file = map_file;
    tm->nTiles_used = 0;
    tm->flowersOnGrassIntensity = 2;
    
	FILE* fileIO = fopen(map_file, "rb");
	fseek(fileIO, 0L, SEEK_END);
	long int numbytes = ftell(fileIO);
	fseek(fileIO, 0L, SEEK_SET);
    char* mapData = malloc(numbytes + 1);
	fread(mapData, 1, numbytes, fileIO);
    mapData[numbytes] = 0;
    RemoveCharacterFromArray(mapData, '\r', numbytes);
    RemoveCharacterFromArray(mapData, ' ', numbytes);
    fclose(fileIO);

    for(int i = 0; i < tm->nTiles_x * tm->nTiles_y;){
        if(*mapData == '*'){
            break;
        }
        else if(*mapData == ';' || *mapData == '\n'){
            mapData++;
            i++;
            continue;
        }
        else if(*mapData == ','){
            mapData++;
            continue;
        }

        char mapDataExtract[10];
        for(int j = 0; j < 10; j++) {mapDataExtract[j] = 0;}
        int iterations = 0;
        for(;*mapData != ',' && *mapData != '*' && *mapData != ';' && *mapData != '\n'; mapData++, iterations++){
            mapDataExtract[iterations] = *mapData;
        }
        
        char** ptr = NULL;
        int mapDataInt = strtol(mapDataExtract, ptr, 10);

        // ----------------------------------
        // ----- DEFAULT TILEPROPERTIES -----
        // ----------------------------------

        //Srcrect is full texture size
        SDL_Rect srcrect = {0,0,gfx->wWidth, gfx->wHeight};

        //Marks where the current tile is drawn
        SDL_Rect destrect = {
        tm->topleft_x + (int)(i % tm->nTiles_x) * TILE_WIDTH
        ,tm->topleft_y + (int)(i / tm->nTiles_x) * TILE_HEIGHT
        ,TILE_WIDTH
        ,TILE_HEIGHT
        };

        //Hitbox is the drawn texture
        SDL_Rect hitbox = destrect;

        //Row 1 = 10, Row 2 = 20....
        int z_index = (tm->topleft_y + (int)(i / tm->nTiles_x) * TILE_Z_INDEX_MAX);
        
        Drawable drawable;
        SpriteSheet season_sprite = SS_TILEMAP_SPRING;
        ConstructDrawable(&drawable, DT_Other, tm->gfx, season_sprite, srcrect, destrect, z_index);

        // ----------------------------------
        TileProperties tp = GetTilePropertiesData(tm, mapDataInt);
        ApplyTileProperties(tm, &tp, &drawable, &hitbox);
        DrawableChangeSpriteSheet(&drawable, season_sprite);


        Tile t;
        //"If new Tile"
        if(*(mapData - (iterations + 1)) == ';' || *(mapData - (iterations + 1)) == '\n'){
            ConstructTile(&t);
            tm->tiles[i] = t;
            tm->nTiles_used++;
        }
        else{
            t = tm->tiles[i];      
        }
        TileAddSprite(&t, drawable, hitbox, z_index);
        //Initiate every Drawable in every overlays-array

        // GRASS -> DIRT
        for(int j = 0; j < tile_overlay_enumsize; j++){
            Drawable overlay;
            SDL_Rect overlay_srcrect = srcrect;
            SDL_Rect overlay_destrect = destrect;
            int overlay_offset = 0;
            switch(j){
                case tile_overlay_left:
                    overlay_offset = 3;
                    overlay_srcrect.x = 66;
                    overlay_srcrect.y = 433;
                    overlay_srcrect.w = 6;
                    overlay_srcrect.h = 16;
                    overlay_destrect.x -= 7;
                    overlay_destrect.w = 12;
                    break;

                case tile_overlay_top_left_inner:
                    overlay_offset = 4;
                    overlay_srcrect.x = 68;
                    overlay_srcrect.y = 420;
                    overlay_srcrect.w = 16;
                    overlay_srcrect.h = 20;
                    overlay_destrect.y -= 6;
                    overlay_destrect.h += 6;
                    break;

                case tile_overlay_top:
                    overlay_offset = 3;
                    overlay_srcrect.x = 144;
                    overlay_srcrect.y = 410;
                    overlay_srcrect.w = 16;
                    overlay_srcrect.h = 6;
                    overlay_destrect.y -= 7;
                    overlay_destrect.h = 12;
                    break;

                case tile_overlay_top_right_inner:
                    overlay_offset = 4;
                    overlay_srcrect.x = 112;
                    overlay_srcrect.y = 420;
                    overlay_srcrect.w = 16;
                    overlay_srcrect.h = 16;
                    overlay_destrect.x += 12;
                    overlay_destrect.y -= 7;
                    overlay_destrect.h = 39;
                    break;
                    
                case tile_overlay_right:
                    overlay_offset = 3;
                    overlay_srcrect.x = 119;
                    overlay_srcrect.y = 433;
                    overlay_srcrect.w = 6;
                    overlay_srcrect.h = 16;
                    overlay_destrect.x += 27;
                    overlay_destrect.w = 12;
                    break;

                case tile_overlay_bottom_right_inner:
                    overlay_offset = 4;
                    overlay_srcrect.x = 113;
                    overlay_srcrect.y = 450;
                    overlay_srcrect.w = 12;
                    overlay_srcrect.h = 12;
                    overlay_destrect.x += 21;
                    overlay_destrect.y += 21;
                    overlay_destrect.w = 18;
                    overlay_destrect.h = 17;
                    break;
                    
                case tile_overlay_bottom:
                    overlay_offset = 3;
                    overlay_srcrect.x = 146;
                    overlay_srcrect.y = 436;
                    overlay_srcrect.w = 14;
                    overlay_srcrect.h = 6;
                    overlay_destrect.y += 25;
                    overlay_destrect.h = 12;
                    break;

                case tile_overlay_bottom_left_inner:
                    overlay_offset = 4;
                    overlay_srcrect.x = 66;
                    overlay_srcrect.y = 447;
                    overlay_srcrect.w = 12;
                    overlay_srcrect.h = 12;
                    overlay_destrect.x -= 7;
                    overlay_destrect.y += 17;
                    overlay_destrect.w = 22;
                    overlay_destrect.h = 22;
                    break;
                default:
                    break;  
            }
            ConstructDrawable(&overlay, DT_Other, tm->gfx, season_sprite, overlay_srcrect, overlay_destrect, t.drawables[0].z_index + overlay_offset);
            t.overlays[tile_overlay_grass_to_dirt][j] = overlay;
        }
        
        // ANYTHING -> WATER
        for(int j = 0; j < tile_overlay_enumsize; j++){
            Drawable overlay;
            SDL_Rect overlay_srcrect = srcrect;
            SDL_Rect overlay_destrect = destrect;
            int overlay_offset = 0;
            switch(j){
                case tile_overlay_left:
                    overlay_offset = 1;
                    overlay_srcrect.x = 128;
                    overlay_srcrect.y = 464;
                    overlay_srcrect.w = 16;
                    overlay_srcrect.h = 16;
                    break;

                case tile_overlay_top_left_inner:
                    overlay_offset = 2;
                    overlay_srcrect.x = 128;
                    overlay_srcrect.y = 448;
                    overlay_srcrect.w = 16;
                    overlay_srcrect.h = 16;
                    break;

                case tile_overlay_top_left_outer:
                    overlay_offset = 2;
                    overlay_srcrect.x = 48;
                    overlay_srcrect.y = 384;
                    overlay_srcrect.w = 16;
                    overlay_srcrect.h = 16;
                    break;

                case tile_overlay_top:
                    overlay_offset = 1;
                    overlay_srcrect.x = 144;
                    overlay_srcrect.y = 448;
                    overlay_srcrect.w = 16;
                    overlay_srcrect.h = 16;
                    break;

                case tile_overlay_top_right_inner:
                    overlay_offset = 2;
                    overlay_srcrect.x = 160;
                    overlay_srcrect.y = 448;
                    overlay_srcrect.w = 16;
                    overlay_srcrect.h = 16;
                    break;

                case tile_overlay_top_right_outer:
                    overlay_offset = 2;
                    overlay_srcrect.x = 64;
                    overlay_srcrect.y = 384;
                    overlay_srcrect.w = 16;
                    overlay_srcrect.h = 16;
                    break;
                    
                case tile_overlay_right:
                    overlay_offset = 1;
                    overlay_srcrect.x = 160;
                    overlay_srcrect.y = 464;
                    overlay_srcrect.w = 16;
                    overlay_srcrect.h = 16;
                    break;

                case tile_overlay_bottom_right_inner:
                    overlay_offset = 2;
                    overlay_srcrect.x = 160;
                    overlay_srcrect.y = 480;
                    overlay_srcrect.w = 16;
                    overlay_srcrect.h = 16;
                    break;

                case tile_overlay_bottom_right_outer:
                    overlay_offset = 2;
                    overlay_srcrect.x = 144;
                    overlay_srcrect.y = 192;
                    overlay_srcrect.w = 16;
                    overlay_srcrect.h = 16;
                    break;
                    
                case tile_overlay_bottom:
                    overlay_offset = 1;
                    overlay_srcrect.x = 144;
                    overlay_srcrect.y = 480;
                    overlay_srcrect.w = 16;
                    overlay_srcrect.h = 16;
                    break;

                case tile_overlay_bottom_left_inner:
                    overlay_offset = 2;
                    overlay_srcrect.x = 128;
                    overlay_srcrect.y = 480;
                    overlay_srcrect.w = 16;
                    overlay_srcrect.h = 16;
                    break;

                case tile_overlay_bottom_left_outer:
                    overlay_offset = 2;
                    overlay_srcrect.x = 128;
                    overlay_srcrect.y = 192;
                    overlay_srcrect.w = 16;
                    overlay_srcrect.h = 16;
                    break;
                default:
                    break;  
            }
            ConstructDrawable(&overlay, DT_Other, tm->gfx, season_sprite, overlay_srcrect, overlay_destrect, t.drawables[0].z_index + overlay_offset);
            t.overlays[tile_overlay_anything_to_water][j] = overlay;
        }
        tm->tiles[i] = t;
    }
    FixTileTransitions(tm);
}

void DestroyTileMap(TileMap* tm){
    free(tm->tiles);
    tm->tiles = NULL;
}

void FixTileTransitions(TileMap* tm){
    Tile* ts = tm->tiles;
    for(int i = 0; i < tm->nTiles_x * tm->nTiles_y ; i++){ 
        // --------- GRASS -> DIRT ------------
        if(ts[i].drawables[0].type == DT_Dirt || (ts[i].drawables[0].type == DT_Water)){
            // ---- SIDES ----
            // left
            
            if(i % tm->nTiles_x != 0)
            ts[i - 1].drawables[0].type == DT_Grass 
            ? 
            ts[i].overlays_used[tile_overlay_grass_to_dirt][tile_overlay_left] = 1 : 0;

            // top
            if(i > tm->nTiles_x)
            ts[i - tm->nTiles_x].drawables[0].type == DT_Grass 
            ? 
            ts[i].overlays_used[tile_overlay_grass_to_dirt][tile_overlay_top] = 1 : 0;

            // right
            if(i < tm->nTiles_used )
            ts[i + 1].drawables[0].type == DT_Grass 
            ? 
            ts[i].overlays_used[tile_overlay_grass_to_dirt][tile_overlay_right] = 1 : 0;

            // bottom
            if(i < tm->nTiles_used - tm->nTiles_x)
            ts[i + tm->nTiles_x].drawables[0].type  == DT_Grass 
            ? 
            ts[i].overlays_used[tile_overlay_grass_to_dirt][tile_overlay_bottom] = 1 : 0;

            // ---- CORNERS ----
            // top-left
            ts[i].overlays_used[tile_overlay_grass_to_dirt][tile_overlay_left] && ts[i].overlays_used[tile_overlay_grass_to_dirt][tile_overlay_top] 
            ? 
            ts[i].overlays_used[tile_overlay_grass_to_dirt][tile_overlay_top_left_inner] = 1 : 0;

            // top-right
            ts[i].overlays_used[tile_overlay_grass_to_dirt][tile_overlay_top] && ts[i].overlays_used[tile_overlay_grass_to_dirt][tile_overlay_right]  
            ? 
            ts[i].overlays_used[tile_overlay_grass_to_dirt][tile_overlay_top_right_inner] = 1 : 0;

            // bottom-right
            ts[i].overlays_used[tile_overlay_grass_to_dirt][tile_overlay_right] && ts[i].overlays_used[tile_overlay_grass_to_dirt][tile_overlay_bottom] 
            ?
            ts[i].overlays_used[tile_overlay_grass_to_dirt][tile_overlay_bottom_right_inner] = 1 : 0;

            // bottom-left
            ts[i].overlays_used[tile_overlay_grass_to_dirt][tile_overlay_bottom] && ts[i].overlays_used[tile_overlay_grass_to_dirt][tile_overlay_left] 
            ? 
            ts[i].overlays_used[tile_overlay_grass_to_dirt][tile_overlay_bottom_left_inner]  = 1 : 0;
        }
        
        // --------- WATER -> ANYTHING ------------
        if(ts[i].drawables[0].type == DT_Water){
            //outside corners
            int top_left_not_water = 0;
            int top_right_not_water = 0;
            int bottom_right_not_water = 0;
            int bottom_left_not_water = 0;
            if(i > tm->nTiles_x && i % tm->nTiles_x != 0)
            ts[i - tm->nTiles_x - 1].drawables[0].type != DT_Water  
            ?
            top_left_not_water = 1 : 0;

            if(i > tm->nTiles_x && i % tm->nTiles_x != 0)
            ts[i - tm->nTiles_x + 1].drawables[0].type != DT_Water  
            ? 
            top_right_not_water = 1 : 0;

            if(i < tm->nTiles_used - tm->nTiles_x && i % tm->nTiles_x != 0)
            ts[i + tm->nTiles_x + 1].drawables[0].type != DT_Water  
            ? 
            bottom_right_not_water = 1 : 0;

            if(i < tm->nTiles_used - tm->nTiles_x && i % tm->nTiles_x != 1)
            ts[i + tm->nTiles_x - 1].drawables[0].type != DT_Water  
            ? 
            bottom_left_not_water = 1 : 0;

            // ---- SIDES ----
            // left
            if(i % tm->nTiles_x != 0)
            ts[i - 1].drawables[0].type != DT_Water 
            ? 
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_left] = 1 : 0;

            // top
            if(i > tm->nTiles_x)
            ts[i - tm->nTiles_x].drawables[0].type != DT_Water  
            ? 
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_top] = 1 : 0;

            // right
            if(((i % tm->nTiles_x) - tm->nTiles_x) != 0 && i < tm->nTiles_used)
            ts[i + 1].drawables[0].type != DT_Water  
            ? 
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_right] = 1 : 0;

            // bottom
            if(i < tm->nTiles_used)
            ts[i + tm->nTiles_x].drawables[0].type != DT_Water  
            ? 
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_bottom] = 1 : 0;


            // ---- CORNERS ----
            // top-left
            // - inner
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_left] && 
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_top] 
            ? 
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_top_left_inner] = 1 : 0;
            // - outer
            top_left_not_water && 
            !ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_left] && 
            !ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_top] 
            ? 
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_top_left_outer] = 1 : 0;

            // top-right
            // - inner
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_top] && 
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_right] 
            ? 
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_top_right_inner] = 1 : 0;
            // - outer
            top_right_not_water && 
            !ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_top] && 
            !ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_right]
            ? 
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_top_right_outer] = 1 : 0;

            // bottom-right
            // - inner
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_right] && 
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_bottom] 
            ? 
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_bottom_right_inner] = 1 : 0;
            // - outer
            bottom_right_not_water && 
            !ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_right] && 
            !ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_bottom]
            ? 
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_bottom_right_outer] = 1 : 0;

            // bottom-left
            // - inner
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_bottom] 
            && ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_left] 
            ? 
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_bottom_left_inner] = 1 : 0;
            // - outer
            bottom_left_not_water && 
            !ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_bottom] && 
            !ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_left]
            ?
            ts[i].overlays_used[tile_overlay_anything_to_water][tile_overlay_bottom_left_outer] = 1 : 0;

        }
    }
}

void TileMapChangeSpriteSheet(TileMap* tm, SpriteSheet spritesheet){
    for(int i = 0; i < tm->nTiles_used; i++){
        for(int j = 0; j < tm->tiles[i].currentSpriteAmmount; j++){
            DrawableChangeSpriteSheet(&tm->tiles[i].drawables[j], spritesheet);
        }
        for(int j = 0; j < tile_overlay_types_enumsize; j++){
            for(int k = 0; k < tile_overlay_enumsize; k++){
                DrawableChangeSpriteSheet(&tm->tiles[i].overlays[j][k], spritesheet);
            }
        }
    }
}


TileProperties GetTilePropertiesData(TileMap* tm, const MapDataConverter mdc){
    TileProperties tp;
     //--- Default ---
    tp.type = DT_Other;

    tp.destrect_offset.x = 0;
    tp.destrect_offset.y = 0;
    tp.drawable_x_correct = 0;
    tp.drawable_y_correct = 0;
    tp.destrect_offset.w = 0;
    tp.destrect_offset.h = 0;

    tp.srcrect.x = 0;
    tp.srcrect.y = 0;
    tp.srcrect.w = 10000;
    tp.srcrect.h = 10000;

    tp.hitbox_offset.x = 0;
    tp.hitbox_offset.y = 0;
    tp.hitbox_x_correct = 0;
    tp.hitbox_y_correct = 0;
    tp.hitbox_offset.w = 0;
    tp.hitbox_offset.h = 0;
    
    tp.z_index_offset = 0;
    //----------------
    switch(mdc){
        case DIRT:
            tp.type = DT_Dirt;
            tp.srcrect.x = 80;
            tp.srcrect.y = 400;
            tp.srcrect.w = 16;
            tp.srcrect.h = 16;
            break;
        case GRASS:
            tp.type = DT_Grass; 
            int randomNum = rand() % (2000 / tm->flowersOnGrassIntensity);
            if(randomNum >= 0 &&  randomNum < 20){
                tp.srcrect.x = 0;
                tp.srcrect.y = 96;
            }else if(randomNum >= 20 &&  randomNum < 22){
                tp.srcrect.x = 16;
                tp.srcrect.y = 96;
            }else if(randomNum >= 40 &&  randomNum < 42){
                tp.srcrect.x = 32;
                tp.srcrect.y = 96;
            }else{
                tp.srcrect.x = 0;
                tp.srcrect.y = 112;
            }
            tp.srcrect.w = 16;
            tp.srcrect.h = 16;
            break;
        case SAND:
            tp.type = DT_Sand;
            tp.srcrect.x = 128;
            tp.srcrect.y = 272;
            tp.srcrect.w = 16;
            tp.srcrect.h = 16;
            break;
        case TREE:
            tp.destrect_offset.w += TILE_WIDTH * 2;
            tp.destrect_offset.h += TILE_HEIGHT * 4;
            tp.destrect_offset.x -= TILE_WIDTH;

            tp.hitbox_offset.w -= TILE_WIDTH * 2;
            tp.hitbox_offset.h -= TILE_HEIGHT * 4;
            tp.hitbox_offset.x += TILE_WIDTH;
            tp.z_index_offset += 90;

            tp.srcrect.x = 48;
            tp.srcrect.y = 0;
            tp.srcrect.w = 48;
            tp.srcrect.h = 96;
            break;
        case WATER:
            tp.type = DT_Water;
            tp.z_index_offset -= 500;
            tp.srcrect.x = 128;
            tp.srcrect.y = 208;
            tp.srcrect.w = 16;
            tp.srcrect.h = 16;
            break;
        case PLAYER_HOME:
            tp.type = DT_Player_Home;
            tp.z_index_offset += 5;
            tp.srcrect.x = 64;
            tp.srcrect.y = 512;
            tp.srcrect.w = 80;
            tp.srcrect.h = 80;
            tp.destrect_offset.w += TILE_WIDTH * 4;
            tp.destrect_offset.h += TILE_HEIGHT * 4;
            break;
        case PLAYER_HOME_ROOF:
            tp.type = DT_Player_Home;
            tp.z_index_offset += 5000;
            tp.srcrect.x = 240;
            tp.srcrect.y = 736;
            tp.srcrect.w = 80;
            tp.srcrect.h = 16;
            tp.destrect_offset.y -= TILE_WIDTH * 5;
            tp.destrect_offset.w += TILE_HEIGHT * 4;
            break;
        case PIER:
            tp.type = DT_Pier;
            tp.z_index_offset = -300;
            tp.srcrect.x = 176;
            tp.srcrect.y = 1040;
            tp.srcrect.w = 80;
            tp.srcrect.h = 64;
            tp.destrect_offset.w += TILE_WIDTH * 4;
            tp.destrect_offset.h += TILE_HEIGHT * 3;
            break;
        case PIER_EXTENSION:
            tp.type = DT_Pier;
            tp.z_index_offset = -300;
            tp.srcrect.x = 176;
            tp.srcrect.y = 1072;
            tp.srcrect.w = 80;
            tp.srcrect.h = 32;
            tp.destrect_offset.w += TILE_WIDTH * 4;
            tp.destrect_offset.h += TILE_HEIGHT * 2;
            break;
        case PLANK_BRIDGE:
            tp.type = DT_Pier;
            tp.z_index_offset = 2;
            tp.srcrect.x = 64;
            tp.srcrect.y = 496;
            tp.srcrect.w = 64;
            tp.srcrect.h = 16;
            tp.destrect_offset.w += TILE_WIDTH * 3;
            tp.hitbox_offset.w -= TILE_WIDTH * 4;
            tp.hitbox_offset.h -= TILE_WIDTH;
            break;
        case TRANSPARENT:
            tp.type = DT_Transparent;
            tp.srcrect.x = 0;
            tp.srcrect.y = 0;
            tp.srcrect.w = 1;
            tp.srcrect.h = 1;
            break;
        default:
            break;
    }
    //Because we inevitably draw from the top-left corner
    tp.drawable_y_correct -= tp.destrect_offset.h;
    tp.hitbox_y_correct -= tp.hitbox_offset.h;
    //--------------------------------------------------
    return tp;
}

void ApplyTileProperties(TileMap* tm, TileProperties* tp, Drawable* drawable, SDL_Rect* hitbox){
    drawable->type = tp->type;

    drawable->destrect.x += tp->drawable_x_correct + tp->destrect_offset.x;
    drawable->destrect.y += tp->drawable_y_correct + tp->destrect_offset.y;
    drawable->destrect.w += tp->destrect_offset.w;
    drawable->destrect.h += tp->destrect_offset.h;

    drawable->srcrect.x = tp->srcrect.x;
    drawable->srcrect.y = tp->srcrect.y;
    drawable->srcrect.w = tp->srcrect.w;
    drawable->srcrect.h = tp->srcrect.h;

    *hitbox = drawable->destrect;
    hitbox->x += tp->hitbox_x_correct + tp->hitbox_offset.x;
    hitbox->y += tp->hitbox_y_correct + tp->hitbox_offset.y;
    hitbox->w += tp->hitbox_offset.w;
    hitbox->h += tp->hitbox_offset.h;

    drawable->z_index += tp->z_index_offset + Map(tp->destrect_offset.y, 0, TILE_HEIGHT, 0, TILE_Z_INDEX_MAX); 
}