
#include <stdio.h>
#include "include\SDL2\SDL.h"
#include "include\SDL2\SDL_timer.h"
#include "include\SDL2\SDL_image.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define SCROLL_SPEED 300
#define SPEED 550

int main()
{
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Error initalizing SDL: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* win = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480 ,0);
    if(!win){
        printf("Error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    SDL_Renderer* rend = SDL_CreateRenderer(win, -1, render_flags);
    if(!rend){
        printf("Error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface = IMG_Load("1.jpg");
    if(!surface){
        printf("Error creating surface: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }    

    SDL_Texture* tex = SDL_CreateTextureFromSurface(rend, surface);
    SDL_FreeSurface(surface);
    if(!tex){
        printf("Error creating texture: %s\n", SDL_GetError());
        SDL_DestroyRenderer(rend);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    SDL_Rect dest;
    dest.x = 10;
    dest.y = 10; 
    dest.w = 100;
    dest.h = 100;   

    SDL_Rect src;
    src.x = 10;
    src.y = 10;
    src.w = 200;
    src.h = 200;

    float x_pos = 10;
    float y_pos = 10;
    float x_vel = SPEED;
    float y_vel = SPEED;


    int close_requsted = 0;
    while(!close_requsted){

        SDL_Event event;
        while(SDL_PollEvent(&event)){
            switch(event.type){
            case SDL_QUIT:
                close_requsted = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:

                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    break;                
                default:
                    break;
                }
                break;
            }
        }


        x_pos += x_vel / 60;
        y_pos += y_vel / 60;
        

        if(x_pos <= 0){
            x_vel *= -1;
            x_pos = 0;
        }else if(x_pos + dest.w > WINDOW_WIDTH){  
            x_vel *= -1;          
            x_pos = WINDOW_WIDTH - dest.w;
        }
        if(y_pos <= 0){
            y_vel *= -1;
            y_pos = 0;
        }else if(y_pos + dest.h > WINDOW_HEIGHT){
            y_vel *= -1;            
            y_pos = WINDOW_HEIGHT - dest.h;
        }

        dest.x = (int)x_pos;
        dest.y = (int)y_pos;

        SDL_RenderClear(rend);
        SDL_RenderCopy(rend, tex, &src, &dest);
        SDL_RenderPresent(rend);

        SDL_Delay(1000 / 60);
    }
    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(win);


    return 0;
}