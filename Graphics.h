#include "include/SDL2/SDL.h"

typedef struct Graphics{
    SDL_Window* win;
    SDL_Renderer* rend;
}Graphics;

void ConstructGraphics(Graphics *gfx);
void DestroyGraphics(Graphics *gfx);
void BeginFrame(Graphics *gfx);
void EndFrame(Graphics *gfx);