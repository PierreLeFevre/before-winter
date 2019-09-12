#include "Drawable.h"

typedef struct Player{
    Drawable d;
    float x_vel;
    float y_vel;
    char moveDir;

    char* img_path;
}Player;

void UpdatePlayer(Player* player);
void MovePlayer(Player* player);