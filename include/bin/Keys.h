typedef struct Keys
{
    /*movment*/
    int UP[2];
    int DOWN[2];
    int RIGHT[2];
    int LEFT[2];
    /*interaction*/
    int testkey;
    int inventroy;
    int harvestTemp;
    int meny;
    int quickSlot[9];

} Keys;
typedef struct Pressed
{
    /*movment*/
    int UP;
    int DOWN;
    int RIGHT;
    int LEFT;
    /*interaction*/
    int testkey;
    int inventroy;
    int harvestTemp;
    int meny;
    int quickSlot[9];

} Pressed;