#include "Drawable.h"

typedef struct Player{
    Drawable d;
    float x_vel;
    float y_vel;
    int x_dir;
    int y_dir;
    int animationState;

    SDL_Rect hitbox;

    char *img_path;
}Player;

void ConstructPlayer(Player* player, Graphics* gfx);
void UpdatePlayer(Player* player);
void UpdatePlayerDirection(Player* player);
void MovePlayer(Player* player);

void DrawPlayer(Player* player);
void AnimatePlayer(Player* player);