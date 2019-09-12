#include "../SDL2/SDL.h"

#define WINDOW_WIDTH 700
#define WINDOW_HEIGHT 700

typedef struct Graphics{
    SDL_Window* win;
    SDL_Renderer* rend;
}Graphics;

void ConstructGraphics(Graphics *gfx);
void DrawFilledRectangle(SDL_Renderer *r,const SDL_Rect *rect);
void DrawHollowRectangle(SDL_Renderer *r, const SDL_Rect *rect);
void DestroyGraphics(Graphics *gfx);
void BeginFrame(Graphics *gfx);
void EndFrame(Graphics *gfx);