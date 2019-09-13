#include "Drawable.h"

typedef struct Player{
    Drawable d;
    int x_pos_currCoord;
    int y_pos_currCoord;
    int x_pos_destCoord;
    int y_pos_destCoord;
    float x_vel;
    float y_vel;
    int x_dir;
    int y_dir;

    char* img_path;
}Player;

void ConstructPlayer(Player* player, Graphics* gfx);
void UpdatePlayer(Player* player);
void UpdatePlayerDirection(Player* player);
void MovePlayer(Player* player);

void DrawPlayer(Player* player);
void AnimatePlayer(Player* player);