#include "Drawable.h"

typedef struct Player{
    Drawable d;
    float x_vel;
    float y_vel;
    int x_dir;
    int y_dir;
    int animationState; //0-2
    int dir; //0: down; 1: up; 2: left; 3: right; 

    char* img_path;
}Player;

void ConstructPlayer(Player* player, Graphics* gfx);
void UpdatePlayer(Player* player);
void UpdatePlayerDirection(Player* player);
void MovePlayer(Player* player);

void DrawPlayer(Player* player);
void AnimatePlayer(Player* player);