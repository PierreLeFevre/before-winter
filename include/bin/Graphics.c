#include "Graphics.h"
#include <stdio.h>
#include "../SDL2/SDL_image.h"

void ConstructGraphics(Graphics *gfx){
    gfx->wWidth = WINDOW_WIDTH;
    gfx->wHeight = WINDOW_HEIGHT;
    gfx->wFullscreen = 0;
    gfx->textures = (SDL_Texture **)malloc(sizeof(SDL_Texture*) * 10);


    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Error initalizing SDL: %s\n", SDL_GetError());
        return;
    }
    gfx->win = SDL_CreateWindow("Before Winter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT,0);
    if(!gfx->win){
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }
    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    gfx->rend = SDL_CreateRenderer(gfx->win, -1, render_flags);
    if(!gfx->rend){
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(gfx->win);
        SDL_Quit();
        return;
    }
    
    SDL_Surface* surf;
    //TILEMAP
    surf = IMG_Load("include/assets/unpacked/maps/spring_outdoorsTileSheet.png");
    if(!surf){
        printf("Error creating surface (spring_outdoorsTileSheet.png): %s\n", SDL_GetError());
    }
    gfx->textures[SS_TILEMAP] = SDL_CreateTextureFromSurface(gfx->rend, surf);
    if(!gfx->textures[SS_TILEMAP]){
        printf("Error creating texture (spring_outdoorsTileSheet.png): %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surf);

    //PLAYER
    surf = IMG_Load("include/assets/unpacked/Characters/Leah.png"); 
    if(!surf){
        printf("Error creating surface (Leah.png): %s\n", SDL_GetError());
    }
    gfx->textures[SS_PLAYER] = SDL_CreateTextureFromSurface(gfx->rend, surf);
    if(!gfx->textures[SS_PLAYER]){
        printf("Error creating texture (Leah.png): %s\n", SDL_GetError());
    }

    //GUI
    SDL_FreeSurface(surf);
        surf = IMG_Load("include/assets/GUI.png"); 
    if(!surf){
        printf("Error creating surface (GUI.png): %s\n", SDL_GetError());
    }
    gfx->textures[SS_GUI] = SDL_CreateTextureFromSurface(gfx->rend, surf);
    if(!gfx->textures[SS_GUI]){
        printf("Error creating texture (GUI.png): %s\n", SDL_GetError());
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
void DestroyGraphics(Graphics *gfx){
    SDL_DestroyRenderer(gfx->rend);
    SDL_DestroyWindow(gfx->win);
    free(gfx->textures);
}

void BeginFrame(Graphics *gfx){    
    SDL_RenderClear(gfx->rend);
}

void EndFrame(Graphics *gfx){    
    SDL_RenderPresent(gfx->rend);    
}