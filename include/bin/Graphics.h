#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "../SDL2/SDL.h"

#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000

#define TILE_WIDTH 60
#define TILE_HEIGHT 60

#define TILE_Z_INDEX_MIN -100
#define TILE_Z_INDEX_MAX 100

typedef struct Graphics{
    SDL_Window* win;
    SDL_Renderer* rend;
    SDL_Rect camera;
}Graphics;

void ConstructGraphics(Graphics *gfx);
void DrawFilledRectangle(SDL_Renderer *r,const SDL_Rect *rect);
void DrawHollowRectangle(SDL_Renderer *r, const SDL_Rect *rect);
void DestroyGraphics(Graphics *gfx);
void BeginFrame(Graphics *gfx);
void EndFrame(Graphics *gfx);

#endif