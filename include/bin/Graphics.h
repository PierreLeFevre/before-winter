#ifndef GRAPHICS_H
#define GRAPHICS_H
#include "../SDL2/SDL.h"

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700

typedef struct Graphics{
    SDL_Window* win;
    SDL_Renderer* rend;
}Graphics;

void ConstructGraphics(Graphics *gfx);
void DestroyGraphics(Graphics *gfx);
void BeginFrame(Graphics *gfx);
void EndFrame(Graphics *gfx);

#endif