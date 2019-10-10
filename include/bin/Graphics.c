#include "Graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include "FuncLib.h"
#include "../SDL2/SDL_image.h"

void ConstructGraphics(Graphics *gfx)
{
    gfx->wWidth = Get_Option("WINDOW_WIDTH=");
    gfx->wHeight = Get_Option("WINDOW_HEIGHT=");
    gfx->wFullscreen = 0;
    gfx->textures = (SDL_Texture **)malloc(sizeof(SDL_Texture *) * 10);

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Error initalizing SDL: %s\n", SDL_GetError());
        return;
    }
    gfx->win = SDL_CreateWindow("Before Winter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, gfx->wWidth, gfx->wHeight, 0);
    if (!gfx->win)
    {
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    gfx->rend = SDL_CreateRenderer(gfx->win, -1, render_flags);
    if (!gfx->rend)
    {
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(gfx->win);
        SDL_Quit();
        return;
    }

    SDL_Surface *surf;
    //TILEMAP SPRING
    surf = IMG_Load("include/assets/unpacked/maps/spring_outdoorsTileSheet.png");
    if (!surf)
    {
        printf("Error creating surface (spring_outdoorsTileSheet.png): %s\n", SDL_GetError());
    }
    gfx->textures[SS_TILEMAP_SPRING] = SDL_CreateTextureFromSurface(gfx->rend, surf);
    if (!gfx->textures[SS_TILEMAP_SPRING])
    {
        printf("Error creating texture (spring_outdoorsTileSheet.png): %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surf);

    //TILEMAP SUMMER
    surf = IMG_Load("include/assets/unpacked/maps/summer_outdoorsTileSheet.png");
    if (!surf)
    {
        printf("Error creating surface (summer_outdoorsTileSheet.png): %s\n", SDL_GetError());
    }
    gfx->textures[SS_TILEMAP_SUMMER] = SDL_CreateTextureFromSurface(gfx->rend, surf);
    if (!gfx->textures[SS_TILEMAP_SUMMER])
    {
        printf("Error creating texture (summer_outdoorsTileSheet.png): %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surf);

    //TILEMAP FALL
    surf = IMG_Load("include/assets/unpacked/maps/fall_outdoorsTileSheet.png");
    if (!surf)
    {
        printf("Error creating surface (fall_outdoorsTileSheet.png): %s\n", SDL_GetError());
    }
    gfx->textures[SS_TILEMAP_FALL] = SDL_CreateTextureFromSurface(gfx->rend, surf);
    if (!gfx->textures[SS_TILEMAP_FALL])
    {
        printf("Error creating texture (fall_outdoorsTileSheet.png): %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surf);

    //PLAYER
    surf = IMG_Load("include/assets/unpacked/Characters/robin.png");
    if (!surf)
    {
        printf("Error creating surface (Leah.png): %s\n", SDL_GetError());
    }
    gfx->textures[SS_PLAYER] = SDL_CreateTextureFromSurface(gfx->rend, surf);
    if (!gfx->textures[SS_PLAYER])
    {
        printf("Error creating texture (Leah.png): %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surf);

    //Plants
    surf = IMG_Load("include/assets/unpacked/TileSheets/crops.png");
    if (!surf)
    {
        printf("Error creating surface (Plants): %s\n", SDL_GetError());
    }
    gfx->textures[SS_PLANT] = SDL_CreateTextureFromSurface(gfx->rend, surf);
    if (!gfx->textures[SS_PLANT])
    {
        printf("Error creating texture (Plants): %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surf);

    //GUI
    surf = IMG_Load("include/assets/gui.png");
    if (!surf)
    {
        printf("Error creating surface (GUI.png): %s\n", SDL_GetError());
    }
    gfx->textures[SS_GUI] = SDL_CreateTextureFromSurface(gfx->rend, surf);
    if (!gfx->textures[SS_GUI])
    {
        printf("Error creating texture (GUI.png): %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surf);

    //Font
    surf = IMG_Load("include/assets/font.png");
    if (!surf)
    {
        printf("Error creating surface (font.png): %s\n", SDL_GetError());
    }
    gfx->textures[SS_FONT] = SDL_CreateTextureFromSurface(gfx->rend, surf);
    if (!gfx->textures[SS_FONT])
    {
        printf("Error creating texture (font.png): %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surf);

    //SPRING OBJECTS
    surf = IMG_Load("include/assets/unpacked/maps/springobjects.png");
    if (!surf)
    {
        printf("Error creating surface (item.png): %s\n", SDL_GetError());
    }
    gfx->textures[SS_ITEM] = SDL_CreateTextureFromSurface(gfx->rend, surf);
    if (!gfx->textures[SS_ITEM])
    {
        printf("Error creating texture (item.png): %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surf);   
    
    //SHADERS
    surf = IMG_Load("include/assets/shaders.png");
    if (!surf)
    {
        printf("Error creating surface (shaders.png): %s\n", SDL_GetError());
    }
    gfx->textures[SS_SHADER] = SDL_CreateTextureFromSurface(gfx->rend, surf);
    if (!gfx->textures[SS_SHADER])
    {
        printf("Error creating texture (shaders.png): %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surf);

    //TRANSPARENT
    surf = IMG_Load("include/assets/LIGHTW_TRANSPARENCY.png");
    if (!surf)
    {
        printf("Error creating surface (LIGHTW_TRANSPARENCY.png): %s\n", SDL_GetError());
    }
    gfx->textures[SS_TRANSPARENT] = SDL_CreateTextureFromSurface(gfx->rend, surf);
    if (!gfx->textures[SS_TRANSPARENT])
    {
        printf("Error creating texture (LIGHTW_TRANSPARENCY.png): %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surf);
}

void DrawFilledRectangle(SDL_Renderer *r, const SDL_Rect *rect)
{
    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    SDL_RenderFillRect(r, rect);
}
void DrawHollowRectangle(SDL_Renderer *r, const SDL_Rect *rect)
{
    SDL_SetRenderDrawColor(r, 255, 0, 0, 255);
    SDL_RenderFillRect(r, rect);
}
void DestroyGraphics(Graphics *gfx)
{
    SDL_DestroyRenderer(gfx->rend);
    SDL_DestroyWindow(gfx->win);
    free(gfx->textures);
}

void BeginFrame(Graphics *gfx)
{
    SDL_RenderClear(gfx->rend);
}

void EndFrame(Graphics *gfx)
{
    SDL_RenderPresent(gfx->rend);
}