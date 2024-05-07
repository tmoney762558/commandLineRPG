#include <iostream>

class baseCharacter // Base character class
{
public:
    std::string name = "NULL";
    int level;
    int maxHP = 0;
    int hp = 0;
    int atk;
    int def;
    int mgk;
    int skillsHeld;
    std::string skills[10];
    std::string skillAffinity[10];
    std::string weakness;
    bool alive = false;
    bool guarding = false;
};

class mainCharacter : public baseCharacter // Main character class
{
public:
    mainCharacter()
    {
        name;
        level = 1;
        hp = 10;
        atk = 5;
        def = 5;
        mgk = 5;
        weakness = "curse";
        alive = true;
    }
};

class ally : public baseCharacter // Ally class
{
public:
};

class enemies : public baseCharacter // Enemy class
{
public:
    enemies()
    {
        level = 1;
        maxHP = 10;
        hp = 10;
        atk = 2;
        def = 0;
        mgk = 0;
    }
};