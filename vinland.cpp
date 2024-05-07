#include <iostream>
#include "functions.h"

int main()
{
    // Items
    std::string items[20];

    // Enemies:

    // Slime
    enemies slime;
    slime.alive = true;
    slime.name = "Slime";
    slime.hp = 5;
    slime.atk = 1;

    // Battle Participants
    mainCharacter mc;
    ally ally1;
    ally ally2;
    ally ally3;
    enemies enemy1 = slime;
    enemies enemy2 = slime;
    enemies enemy3 = slime;
    enemies enemy4 = slime;

    mc.name = characterCreation();
    story();
    encounter(mc, ally1, ally2, ally3, enemy1, enemy2, enemy3, enemy4, items); // Encounter is called

    return 0;
}
