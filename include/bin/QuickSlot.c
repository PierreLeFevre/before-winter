#include "QuickSlot.h"

void QuickSlotHandeling(Player *player)
{
    if (EventHandler("quickSlot0=")) //Empty hand
    {

        Item i = {{0}};
        player->activeItem = i;
        player->activeItemIndex = 10000; // något högt
    }
    if (EventHandler("quickSlot1="))
    {
        player->ent.items[0].d.destrect.x = player->activeItem.d.destrect.x;
        player->ent.items[0].d.destrect.y = player->activeItem.d.destrect.y;
        player->activeItem = player->ent.items[0];
        player->activeItemIndex = 0;
    }
    if (EventHandler("quickSlot2="))
    {
        player->ent.items[1].d.destrect.x = player->activeItem.d.destrect.x;
        player->ent.items[1].d.destrect.y = player->activeItem.d.destrect.y;
        player->activeItem = player->ent.items[1];
        player->activeItemIndex = 1;
    }
    if (EventHandler("quickSlot3="))
    {
        player->ent.items[2].d.destrect.x = player->activeItem.d.destrect.x;
        player->ent.items[2].d.destrect.y = player->activeItem.d.destrect.y;
        player->activeItem = player->ent.items[2];
        player->activeItemIndex = 2;
    }
    if (EventHandler("quickSlot4="))
    {
        player->ent.items[3].d.destrect.x = player->activeItem.d.destrect.x;
        player->ent.items[3].d.destrect.y = player->activeItem.d.destrect.y;
        player->activeItem = player->ent.items[3];
        player->activeItemIndex = 3;
    }
    if (EventHandler("quickSlot5="))
    {
        player->ent.items[4].d.destrect.x = player->activeItem.d.destrect.x;
        player->ent.items[4].d.destrect.y = player->activeItem.d.destrect.y;
        player->activeItem = player->ent.items[4];
        player->activeItemIndex = 4;
    }
    if (EventHandler("quickSlot6="))
    {
        player->ent.items[5].d.destrect.x = player->activeItem.d.destrect.x;
        player->ent.items[5].d.destrect.y = player->activeItem.d.destrect.y;
        player->activeItem = player->ent.items[5];
        player->activeItemIndex = 5;
    }
    if (EventHandler("quickSlot7="))
    {
        player->ent.items[6].d.destrect.x = player->activeItem.d.destrect.x;
        player->ent.items[6].d.destrect.y = player->activeItem.d.destrect.y;
        player->activeItem = player->ent.items[6];
        player->activeItemIndex = 6;
    }
    if (EventHandler("quickSlot8="))
    {
        player->ent.items[7].d.destrect.x = player->activeItem.d.destrect.x;
        player->ent.items[7].d.destrect.y = player->activeItem.d.destrect.y;
        player->activeItem = player->ent.items[7];
        player->activeItemIndex = 7;
    }
    if (EventHandler("quickSlot9="))
    {
        player->ent.items[8].d.destrect.x = player->activeItem.d.destrect.x;
        player->ent.items[8].d.destrect.y = player->activeItem.d.destrect.y;
        player->activeItem = player->ent.items[8];
        player->activeItemIndex = 8;
    }
}