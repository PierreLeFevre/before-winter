#include "Graphics.h"
#include <stdio.h>

void ConstructGraphics(Graphics *gfx){
    gfx->wWidth = WINDOW_WIDTH;
    gfx->wHeight = WINDOW_HEIGHT;
    
    gfx->wFullscreen = 0;

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
}

void BeginFrame(Graphics *gfx){    
    SDL_RenderClear(gfx->rend);
}

void EndFrame(Graphics *gfx){    
    SDL_RenderPresent(gfx->rend);    
}