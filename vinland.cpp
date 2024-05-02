#include <iostream>
#include <stack>

class baseCharacter
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

class mainCharacter : public baseCharacter
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
        weakness = "light\n";
        alive = true;
    }
};

class ally : public baseCharacter
{
public:
};

class enemies : public baseCharacter
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

std::string characterCreation();
void playerTurn(mainCharacter &mc, enemies &enemy1, enemies &enemy2, enemies &enemy3, enemies &enemy4, std::string items[]);
void playerAttack(mainCharacter &mc, enemies &enemy1, enemies &enemy2, enemies &enemy3, enemies &enemy4, bool &validSel);
void enemyTurn(enemies &currentEnemy, mainCharacter &mc, ally &ally1, ally &ally2, ally &ally3);
void enemyAttack(enemies &currentEnemy, mainCharacter &mc, ally &ally1, ally &ally2, ally &ally3);
void encounter(mainCharacter &mc, ally &ally1, ally &ally2, ally &ally3, enemies &enemy1, enemies &enemy2, enemies &enemy3, enemies &enemy4, std::string items[]);
void story();
void printCombatants(mainCharacter mc, ally ally1, ally ally2, ally ally3, enemies enemy1, enemies enemy2, enemies enemy3, enemies enemy4);
void logic();

int main()
{
    // Items
    std::string items[20];

    // Enemies:

    // Slime
    enemies slime;
    slime.alive = true;
    slime.name = "Slime";
    slime.hp = 6;
    slime.atk = 10;

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

std::string characterCreation()
{
    std::string name;

    std::cout << "Welcome to the world of Vinland, young traveler...\n"
              << '\n';
    std::cout << "Please, give me your name...\n";

    std::getline(std::cin, name);

    std::cout << "Ah... " << name << "... That is a nice name...\n"
              << "May you farewell in your journey...\n";

    return name;
}
void countBattleParticipants(int &numOfAllies, int &numOfEnemies, ally ally1, ally ally2, ally ally3, enemies enemy2, enemies enemy3, enemies enemy4) // Function to increase the number of battle participants excluding enemy1 and the mc (They are assumed to be in the battle already)
{
    if (ally3.alive) // Block of if statements to count how many allies we have
    {
        numOfAllies++;
    }
    if (ally2.alive)
    {
        numOfAllies++;
    }
    if (ally1.alive)
    {
        numOfAllies++;
    }
    if (enemy4.alive) // Block of if statements to count how many enemies we have
    {
        numOfEnemies++;
    }
    if (enemy3.alive)
    {
        numOfEnemies++;
    }
    if (enemy2.alive)
    {
        numOfEnemies++;
    }
}
void encounter(mainCharacter &mc, ally &ally1, ally &ally2, ally &ally3, enemies &enemy1, enemies &enemy2, enemies &enemy3, enemies &enemy4, std::string items[])
{
    int numOfAllies = 1;  // Number of allies in an encounter
    int numOfEnemies = 1; // Number of enemies in an encounter
    bool guarding;

    std::cout << "An enemy appears!\n";
    std::cout << "Battle Start!\n";

    countBattleParticipants(numOfAllies, numOfEnemies, ally1, ally2, ally3, enemy2, enemy3, enemy4);

    while (mc.alive && enemy1.alive)
    {
        for (int i = 1; i < numOfAllies + 1; i++)
        {
            switch (i)
            {
            case 1:
                if (mc.alive)
                {
                    playerTurn(mc, enemy1, enemy2, enemy3, enemy4, items);
                }
                break;
            case 2:
                if (ally1.alive)
                {
                    playerTurn(mc, enemy1, enemy2, enemy3, enemy4, items);
                }
                break;
            case 3:
                if (ally2.alive)
                    ;
                playerTurn(mc, enemy1, enemy2, enemy3, enemy4, items);
                break;
            case 4:
                if (ally3.alive)
                {
                    playerTurn(mc, enemy1, enemy2, enemy3, enemy4, items);
                }
                break;
            }
        }

        for (int i = 1; i < numOfEnemies + 1; i++)
        {
            switch (i)
            {
            case 1:
                enemyTurn(enemy1, mc, ally1, ally2, ally3);
                break;
            case 2:
                enemyTurn(enemy2, mc, ally1, ally2, ally3);
                break;
            case 3:
                enemyTurn(enemy3, mc, ally1, ally2, ally3);
                break;
            case 4:
                enemyTurn(enemy4, mc, ally1, ally2, ally3);
                break;
            }
        }
    }
}
void playerTurn(mainCharacter &mc, enemies &enemy1, enemies &enemy2, enemies &enemy3, enemies &enemy4, std::string items[])
{
    int dmgDelt;

    int selection;
    bool validSel = false;

    std::cout << "Your turn!\n";
    validSel = false;

    while (validSel == false)
    {
        std::cout << "1) Attack\n";
        std::cout << "2) Skill\n";
        std::cout << "3) Guard\n";
        std::cout << "4) Items\n";
        std::cin >> selection;

        switch (selection)
        {
        case 1:
            playerAttack(mc, enemy1, enemy2, enemy3, enemy4, validSel);
            break;
        case 2:
            std::cout << "Skills\n";
            for (int i = 0; i < mc.skillsHeld; i++)
            {
                std::cout << mc.skills[i];
            }
            break;
            // BREAK
        // CASE 3 FOR SWITCH 1
        case 3:
            std::cout << mc.name << " is guarding!\n";
            mc.guarding = true;
            validSel = true;
            break;
            // BREAK
        // CASE 4 FOR SWITCH 1
        case 4:
            std::cout << "Items\n";
            for (int i = 0; i < 20 / sizeof(items[0]); i++)
            {
                std::cout << items[i];
            }
            break;
            // BREAK
        // DEFAULT CASE FOR SWITCH 1
        default:
            std::cout << "Invalid selection!\n";
            break;
            // BREAK
        }
    }
}
void playerAttack(mainCharacter &mc, enemies &enemy1, enemies &enemy2, enemies &enemy3, enemies &enemy4, bool &validSel)
{
    int selection;

    std::cout << "[Target]\n";
    std::cout << "1) " << enemy1.name << '\n';
    std::cout << "(HP: " << enemy1.hp << ")\n";
    if (enemy2.alive)
    {
        std::cout << "2) " << enemy2.name << '\n';
        std::cout << "(HP: " << enemy2.hp << ")\n";
    }
    if (enemy3.alive)
    {
        std::cout << "3) " << enemy3.name << '\n';
        std::cout << "(HP: " << enemy3.hp << ")\n";
    }
    if (enemy4.alive)
    {
        std::cout << "4) " << enemy4.name << '\n';
        std::cout << "(HP: " << enemy4.hp << ")\n";
    }

    std::cout << "Which enemy would you like to target?\n";
    std::cin >> selection;
    // SWITCH 2
    switch (selection)
    {
    // CASE 1 FOR SWITCH 2
    case 1:
        std::cout << mc.name << " attacked " << enemy1.name << "!\n";
        enemy1.hp -= (mc.atk - enemy1.def);
        if (enemy1.hp <= 0)
        {
            std::cout << enemy1.name << " was defeated!\n";
            enemy1.alive = false;
            if (enemy2.alive)
            {
                enemy1 = enemy2;
                enemy2 = enemy3;
                enemy3 = enemy4;
                enemy4.alive = false;
            }
        }
        else
        {
            std::cout << enemy1.name << " has " << enemy1.hp << " HP remaining!\n";
        }
        validSel = true;
        break;
    // CASE 2 FOR SWITCH 2
    case 2:
        if (enemy2.alive)
        {
            std::cout << mc.name << " attacked " << enemy2.name << "!\n";
            enemy2.hp -= (mc.atk - enemy2.def);
            if (enemy2.hp <= 0)
            {
                std::cout << enemy2.name << " was defeated!\n";
                enemy2.alive = false;
                if (enemy3.alive)
                {
                    enemy2 = enemy3;
                    enemy3 = enemy4;
                    enemy4.alive = false;
                }
            }
            else
            {
                std::cout << enemy2.name << " has " << enemy2.hp << " HP remaining!\n";
            }
            validSel = true;
        }
        else
        {
            std::cout << "Invalid target!\n";
        }
        break;
    // CASE 3 FOR SWITCH 2
    case 3:
        if (enemy3.alive)
        {
            std::cout << mc.name << " attacked " << enemy3.name << "!\n";
            enemy3.hp -= (mc.atk - enemy3.def);
            if (enemy2.hp <= 0)
            {
                std::cout << enemy3.name << " was defeated!\n";
                enemy3.alive = false;
                if (enemy4.alive)
                {
                    enemy3 = enemy4;
                    enemy4.alive = false;
                }
            }
            else
            {
                std::cout << enemy3.name << " has " << enemy3.hp << " HP remaining!\n";
            }
            validSel = true;
        }
        else
        {
            std::cout << "Invalid target!\n";
        }
        break;
    // BREAK
    // CASE 4 FOR SWITCH 2
    case 4:
        if (enemy4.alive)
        {
            std::cout << mc.name << " attacked " << enemy4.name << "!\n";
            enemy4.hp -= (mc.atk - enemy4.def);
            if (enemy4.hp <= 0)
            {
                std::cout << enemy4.name << " was defeated!\n";
                enemy4.alive = false;
            }
            else
            {
                std::cout << enemy4.name << " has " << enemy4.hp << " HP remaining!\n";
            }
            validSel = true;
        }
        else
        {
            std::cout << "Invalid target!\n";
        }
        break;
        // BREAK
    default:
    {
        std::cout << "Invalid target!\n";
        break;
        // BREAK
    }
    }
}
void enemyAttack(enemies &currentEnemy, mainCharacter &mc, ally &ally1, ally &ally2, ally &ally3)
{
    int dmgDelt;
    if (mc.alive == false)
    {
        std::cout << "Defeat...\n";
        return;
    }
    if (currentEnemy.alive)
    {
        int enemyAct;
        enemyAct = 1;
        bool validAct = false;
        // SWITCH 1
        switch (enemyAct)
        {
        case 1:
            while (validAct == false)
            {
                enemyAct = 1;
                switch (enemyAct)
                {
                case 1:
                    if (currentEnemy.atk <= mc.def)
                    {
                        dmgDelt = 1;
                    }
                    else
                    {
                        dmgDelt = (currentEnemy.atk - mc.def);
                    }
                    if (mc.guarding && dmgDelt != 1)
                    {
                        dmgDelt /= 2;
                    }
                    mc.hp -= (dmgDelt);
                    std::cout << currentEnemy.name << " attacked " << mc.name << " for " << dmgDelt << " damage!\n";
                    if (mc.hp <= 0)
                    {
                        std::cout << mc.name << " has fainted!\n";
                        mc.alive = false;
                        return;
                    }
                    std::cout << mc.name << " has " << mc.hp << " health remaining!\n";
                    validAct = true;
                    break;
                case 2:
                    if (ally1.alive)
                    {
                        if (currentEnemy.atk <= ally1.def)
                        {
                            dmgDelt = 1;
                        }
                        else
                        {
                            dmgDelt = (currentEnemy.atk - ally1.def);
                        }
                        if (mc.guarding && dmgDelt != 1)
                        {
                            dmgDelt /= 2;
                        }
                        ally1.hp -= dmgDelt;
                        std::cout << currentEnemy.name << " attacked " << ally1.name << " for " << dmgDelt << " damage!\n";
                        if (ally1.hp <= 0)
                        {
                            std::cout << ally1.name << " has fainted!\n";
                            ally1.alive = false;
                        }
                        validAct = true;
                    }
                    break;
                case 3:
                    if (ally2.alive)
                    {
                        if (currentEnemy.atk <= ally2.def)
                        {
                            dmgDelt = 1;
                        }
                        else
                        {
                            dmgDelt = (currentEnemy.atk - ally2.def);
                        }
                        if (mc.guarding && dmgDelt != 1)
                        {
                            dmgDelt /= 2;
                        }
                        ally2.hp -= dmgDelt;
                        std::cout << currentEnemy.name << " attacked " << ally2.name << " for " << dmgDelt << " damage!\n";
                        if (ally2.hp <= 0)
                        {
                            std::cout << ally2.name << " has fainted!\n";
                            ally2.alive = false;
                        }
                        validAct = true;
                    }
                    break;
                case 4:
                    if (ally3.alive)
                    {
                        if (currentEnemy.atk <= ally3.def)
                        {
                            dmgDelt = 1;
                        }
                        else
                        {
                            dmgDelt = (currentEnemy.atk - ally3.def);
                        }
                        if (mc.guarding && dmgDelt != 1)
                        {
                            dmgDelt /= 2;
                        }
                        ally3.hp -= dmgDelt;
                        std::cout << currentEnemy.name << " attacked " << ally3.name << " for " << dmgDelt << " damage!\n";
                        if (ally3.hp <= 0)
                        {
                            std::cout << ally3.name << " has fainted!\n";
                            ally3.alive = false;
                        }
                        validAct = true;
                    }
                    break;
                default:
                    std::cout << "Error: Enemy has selected a number outside of 1-4\n";
                }
            }
        }
    }
}
void enemyTurn(enemies &currentEnemy, mainCharacter &mc, ally &ally1, ally &ally2, ally &ally3)
{
    enemyAttack(currentEnemy, mc, ally1, ally2, ally3);
}
void story()
{
    std::cout << "You wake up in an unfamiliar place.\n";
    std::cout << "Where am I?\n";
    std::cout << "Looking around, you see something approaching\n";
}
