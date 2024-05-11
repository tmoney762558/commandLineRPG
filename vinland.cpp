#include <iostream>
#include <vector>
#include <string>

// 5/9/24: Partially implemented skills (needs debugging), must fix issue with defeating enemies removing too many enemies
// 5/9/24: Implemented skills, their types, and "One More" mechanics. Also fixed and redid the enemy removal system to handle multi-target skills (Not yet implemented)

struct skills
{
    std::string name;
    std::string type;
    int dmg;
    int spCost;
    std::string affinity;
    std::string statusEffect;

    skills()
    {
    }

    skills(std::string Name, std::string Type, int Dmg, int SpCost, std::string Affinity, std::string StatusEffect)
    {
        name = Name;
        type = Type;
        dmg = Dmg;
        spCost = SpCost;
        affinity = Affinity;
        statusEffect = StatusEffect;
    }
};

struct items
{
    std::string name;
    std::string type;
};

class baseCharacter // Base character class
{
public:
    std::string name = "NULL";
    int level;
    int maxHP;
    int hp;
    int sp;
    int atk;
    int def;
    int mgk;
    int skillsHeld;
    skills skills[10];
    std::string weakness;
    bool alive;
    bool guarding;
    std::string status;
    int recovery;

    baseCharacter()
    {
        std::string name = "NULL";
        int level = 1;
        int maxHP = 1;
        int hp = 1;
        int sp = 1;
        int atk = 1;
        int def = 1;
        int mgk = 1;
        int skillsHeld = 0;
        std::string weakness = "fire";
        bool alive = false;
        bool guarding = false;
        std::string status;
        int recovery = 0;
    }
};

class mainCharacter : public baseCharacter // Main character class
{
public:
    mainCharacter()
    {
        name = "NULL";
        level = 1;
        hp = 15;
        atk = 7;
        def = 3;
        mgk = 3;
        weakness = "curse";
        alive = true;
    }
};

class ally : public baseCharacter // Ally class
{
public:
    ally()
    {
        name;
        level = 1;
        hp = 50;
        atk = 10;
        def = 5;
        mgk = 5;
        weakness = "fire";
        alive = false;
    }

    ally(int Level)
    {
        level = Level;
    }
};

class enemies : public baseCharacter // Enemy class
{
public:
    enemies()
    {
        level = 1;
        maxHP = 10;
        hp = 10;
        atk = 1;
        def = 0;
        mgk = 0;
    }
};

std::string characterCreation();
void enemyTurn(enemies &currentEnemy, mainCharacter &mc, ally &ally1, ally &ally2, ally &ally3);
void enemyAttack(enemies &currentEnemy, mainCharacter &mc, ally &ally1, ally &ally2, ally &ally3);
void encounter(mainCharacter mc, ally ally1, ally ally2, ally ally3, enemies enemy1, enemies enemy2, enemies enemy3, enemies enemy4, items itemList[]);
void story();
void countBattleParticipants(int &numOfAllies, int &numOfEnemies, mainCharacter mc, ally ally1, ally ally2, ally ally3, enemies enemy2, enemies enemy3, enemies enemy4);

// playerTurn

void playerTurn(mainCharacter &mc, ally &ally1, ally &ally2, ally &ally3, enemies &enemy1, enemies &enemy2, enemies &enemy3, enemies &enemy4, items itemList[]);
void attackTarget(mainCharacter &mc, enemies &enemy1, enemies &enemy2, enemies &enemy3, enemies &enemy4, bool &validSel);
void skillTarget(mainCharacter &mc, enemies &enemy1, enemies &enemy2, enemies &enemy3, enemies &enemy4, bool &validSel, ally &ally1, ally &ally2, ally &ally3, items itemList[]);
void playerAttack(mainCharacter &mc, enemies &selectedEnemy, enemies &enemy1, enemies &enemy2, enemies &enemy3, enemies &enemy4);
void playerSkill(skills skill, mainCharacter &mc, enemies &selectedEnemy, enemies &enemy1, enemies &enemy2, enemies &enemy3, enemies &enemy4, ally &ally1, ally &ally2, ally &ally3, items itemList[]);
void examineCombatants(mainCharacter mc, ally ally1, ally ally2, ally ally3, enemies enemy1, enemies enemy2, enemies enemy3, enemies enemy4);

int main()
{
    mainCharacter mc;
    ally ally1;
    ally ally2;
    ally ally3;
    enemies enemy1;
    enemies enemy2;
    enemies enemy3;
    enemies enemy4;

    // Items

    items itemList[20];

    // Slime
    enemies slime;
    slime.alive = true;
    slime.name = "Slime";
    slime.hp = 10;
    slime.atk = 0;
    slime.weakness = "fire";

    // Minotaur
    enemies minotaur;
    minotaur.alive = true;
    minotaur.name = "Minotaur";
    minotaur.hp = 10;
    minotaur.atk = 0;

    // Skills
    skills agi = skills("Agi", "mgk", 5, 3, "fire", "burn");

    mc.skills[0] = agi;
    mc.skillsHeld = 1;

    mc.name = characterCreation();
    story();
    encounter(mc, ally1, ally2, ally3, slime, slime, slime, slime, itemList); // Encounter is called

    return 0;
}

std::string characterCreation() // Character creation function
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

void countBattleParticipants(int &numOfAllies, int &numOfEnemies, mainCharacter mc, ally ally1, ally ally2, ally ally3, enemies enemy2, enemies enemy3, enemies enemy4) // Function to increase the number of battle participants excluding enemy1 and the mc (They are assumed to be in the battle already)
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
void encounter(mainCharacter mc, ally ally1, ally ally2, ally ally3, enemies enemy1, enemies enemy2, enemies enemy3, enemies enemy4, items itemList[])
{
    int numOfAllies = 1;  // Number of allies in an encounter
    int numOfEnemies = 1; // Number of enemies in an encounter

    std::cout << "An enemy appears!\n";
    std::cout << "Battle Start!\n";
    if (!mc.alive || !enemy1.alive)
    {
        std::cerr << "MC or Enemy 1 is not alive!\n";
        return;
    }

    countBattleParticipants(numOfAllies, numOfEnemies, mc, ally1, ally2, ally3, enemy2, enemy3, enemy4);

    while (mc.alive && enemy1.alive)
    {
        for (int i = 1; i < numOfAllies + 1; i++)
        {
            switch (i)
            {
            case 1:
                if (mc.alive)
                {
                    playerTurn(mc, ally1, ally2, ally3, enemy1, enemy2, enemy3, enemy4, itemList);
                }
                break;
            case 2:
                if (ally1.alive)
                {
                    playerTurn(mc, ally1, ally2, ally3, enemy1, enemy2, enemy3, enemy4, itemList);
                }
                break;
            case 3:
                if (ally2.alive)
                {
                    playerTurn(mc, ally1, ally2, ally3, enemy1, enemy2, enemy3, enemy4, itemList);
                }

                break;
            case 4:
                if (ally3.alive)
                {
                    playerTurn(mc, ally1, ally2, ally3, enemy1, enemy2, enemy3, enemy4, itemList);
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
    currentEnemy.status = "None";
    enemyAttack(currentEnemy, mc, ally1, ally2, ally3);
}
void story()
{
    std::cout << "You wake up in an unfamiliar place.\n";
    std::cout << "Where am I?\n";
    std::cout << "Looking around, you see something approaching\n";
}
void examineCombatants(mainCharacter mc, ally ally1, ally ally2, ally ally3, enemies enemy1, enemies enemy2, enemies enemy3, enemies enemy4)
{
    std::cout << "[Examine]\n\n";
    std::cout << "[Allies]\n";
    std::cout << "1) " << mc.name << '\n';
    std::cout << "2) " << ally1.name << '\n';
    std::cout << "3) " << ally2.name << '\n';
    std::cout << "4) " << ally3.name << '\n';
    std::cout << '\n';

    std::cout << "[Enemies]\n";
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
    }
    std::cout << '\n';
}
void playerTurn(mainCharacter &mc, ally &ally1, ally &ally2, ally &ally3, enemies &enemy1, enemies &enemy2, enemies &enemy3, enemies &enemy4, items itemList[])
{
    int dmgDelt;
    std::string type;
    skills selectedSkill;

    int selection;
    bool validSel = false;

    std::cout << "Your turn!\n";
    validSel = false;

    while (validSel == false)
    {
        std::cout << "[Actions]\n";
        std::cout << "1) Attack\n";
        std::cout << "2) Skill\n";
        std::cout << "3) Guard\n";
        std::cout << "4) Items\n";
        std::cout << "5) Examine\n";
        std::cin >> selection;

        switch (selection)
        {
        case 1:
            attackTarget(mc, enemy1, enemy2, enemy3, enemy4, validSel);
            break;
        case 2:
            skillTarget(mc, enemy1, enemy2, enemy3, enemy4, validSel, ally1, ally2, ally3, itemList);
            break;
        case 3:
            std::cout << mc.name << " is guarding!\n";
            mc.guarding = true;
            validSel = true;
            break;
        case 4:
            std::cout << "[Items]\n";
            for (int i = 0; i < 20 / sizeof(itemList[i]); i++)
            {
                std::cout << itemList[i].name;
            }
            break;
        case 5:
            examineCombatants(mc, ally1, ally2, ally3, enemy1, enemy2, enemy3, enemy4);
            break;
        default:
            std::cout << "Invalid selection!\n";
            break;
        }
    }
}
void attackTarget(mainCharacter &mc, enemies &enemy1, enemies &enemy2, enemies &enemy3, enemies &enemy4, bool &validSel)
{
    int selection = 0;
    int counter = 0;

    std::cout << "[TARGET]\n";
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
    std::cout << "5) [Back]\n";

    std::cout << "Which enemy would you like to target?\n";
    std::cin >> selection;
    while (validSel == false)
    {
        switch (selection)
        {
        case 1:
            playerAttack(mc, enemy1, enemy1, enemy2, enemy3, enemy4);
            validSel = true;
            break;
        case 2:
            if (enemy2.alive)
            {
                playerAttack(mc, enemy2, enemy1, enemy2, enemy3, enemy4);
                validSel = true;
            }
            else
            {
                std::cout << "Invalid selection!\n";
            }
            break;
        case 3:
            if (enemy3.alive)
            {
                playerAttack(mc, enemy3, enemy1, enemy2, enemy3, enemy4);
                validSel = true;
            }
            else
            {
                std::cout << "Invalid selection!\n";
            }
            break;
        case 4:
            if (enemy4.alive)
            {
                playerAttack(mc, enemy4, enemy1, enemy2, enemy3, enemy4);
                validSel = true;
            }
            else
            {
                std::cout << "Invalid selection!\n";
            }
            break;
        case 5:
            return;
        }
    }
}
void skillTarget(mainCharacter &mc, enemies &enemy1, enemies &enemy2, enemies &enemy3, enemies &enemy4, bool &validSel, ally &ally1, ally &ally2, ally &ally3, items itemList[])
{
    int selection = 0;
    int skillSelection = 0;
    int backPos = 0;

    while (!validSel)
    {
        std::cout << "[Skills]\n";
        for (int i = 0; i < mc.skillsHeld; i++)
        {
            std::cout << i + 1 << ") " << mc.skills[i].name << '\n';
            backPos = i + 1;
        }
        std::cout << "(" << backPos + 1 << " <-- Back\n";
        std::cin >> selection;
        if (selection == backPos + 1)
        {
            return; // Go back to previous menu
        }
        std::cout << "[TARGET]\n";
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
        std::cout << "5) [Back]\n";

        std::cout << "Which enemy would you like to target?\n";
        std::cin >> skillSelection;

        switch (skillSelection)
        {
        case 1:
            if (enemy1.alive)
            {
                playerSkill(mc.skills[selection - 1], mc, enemy1, enemy1, enemy2, enemy3, enemy4, ally1, ally2, ally3, itemList);
                validSel = true;
            }
            break;
        case 2:
            if (enemy2.alive)
            {
                playerSkill(mc.skills[selection - 1], mc, enemy2, enemy1, enemy2, enemy3, enemy4, ally1, ally2, ally3, itemList);
                validSel = true;
            }
            else
            {
                std::cout << "Invalid selection!\n";
            }
            break;
        case 3:
            if (enemy3.alive)
            {
                playerSkill(mc.skills[selection - 1], mc, enemy3, enemy1, enemy2, enemy3, enemy4, ally1, ally2, ally3, itemList);
                validSel = true;
            }
            else
            {
                std::cout << "Invalid selection!\n";
            }
            break;
        case 4:
            if (enemy4.alive)
            {
                playerSkill(mc.skills[selection - 1], mc, enemy4, enemy1, enemy2, enemy3, enemy4, ally1, ally2, ally3, itemList);
                validSel = true;
            }
            else
            {
                std::cout << "Invalid selection!\n";
            }
            break;
        case 5:
            return;
        default:
            std::cerr << "Invalid selection!\n";
            break;
        }
    }
}
void playerAttack(mainCharacter &mc, enemies &selectedEnemy, enemies &enemy1, enemies &enemy2, enemies &enemy3, enemies &enemy4)
{
    int dmgDelt = 0;

    dmgDelt = mc.atk - selectedEnemy.def;
    std::cout << mc.name << " attacked " << selectedEnemy.name << " for " << dmgDelt << " damage!\n";
    selectedEnemy.hp -= dmgDelt;

    if (selectedEnemy.hp <= 0)
    {
        std::cout << selectedEnemy.name << " was defeated!\n";
        selectedEnemy.alive = false;

        if (!enemy1.alive && enemy2.alive)
        {
            enemy1 = enemy2;
            enemy2.alive = false;
        }
        if (!enemy2.alive && enemy3.alive)
        {
            if (!enemy1.alive)
            {
                enemy1 = enemy3;
                enemy3.alive = false;
            }
            else
            {
                enemy2 = enemy3;
                enemy3.alive = false;
            }
        }
        if (!enemy3.alive && enemy4.alive)
        {
            if (!enemy1.alive)
            {
                enemy1 = enemy4;
                enemy4.alive = false;
            }
            else
            {
                enemy3 = enemy4;
                enemy4.alive = false;
            }
        }
        if (enemy4.alive)
        {
            enemy4.alive = false;
        }
    }
    else
    {
        std::cout << selectedEnemy.name << " has " << selectedEnemy.hp << " HP remaining!\n";
    }
}
void playerSkill(skills skill, mainCharacter &mc, enemies &selectedEnemy, enemies &enemy1, enemies &enemy2, enemies &enemy3, enemies &enemy4, ally &ally1, ally &ally2, ally &ally3, items itemList[])
{
    int dmgDelt = 0;

    dmgDelt = (skill.dmg + (mc.mgk * 1.2)) - selectedEnemy.def;
    std::cout << mc.name << " used " << skill.name << " on " << selectedEnemy.name << "!\n";
    std::cout << mc.name << " delt " << dmgDelt << " damage!\n";
    selectedEnemy.hp -= dmgDelt;

    if (selectedEnemy.hp <= 0)
    {
        std::cout << selectedEnemy.name << " was defeated!\n";
        selectedEnemy.alive = false;

        if (!enemy1.alive && enemy2.alive)
        {
            enemy1 = enemy2;
            enemy2.alive = false;
        }
        if (!enemy2.alive && enemy3.alive)
        {
            if (!enemy1.alive)
            {
                enemy1 = enemy3;
                enemy3.alive = false;
            }
            else
            {
                enemy2 = enemy3;
                enemy3.alive = false;
            }
        }
        if (!enemy3.alive && enemy4.alive)
        {
            if (!enemy1.alive)
            {
                enemy1 = enemy4;
                enemy4.alive = false;
            }
            else
            {
                enemy3 = enemy4;
                enemy4.alive = false;
            }
        }
        if (enemy4.alive)
        {
            enemy4.alive = false;
        }
    }

    else
    {
        std::cout << selectedEnemy.name << " has " << selectedEnemy.hp << " HP remaining!\n";
    }

    if (skill.affinity == selectedEnemy.weakness && selectedEnemy.status != "downed")
    {
        selectedEnemy.status = "downed";
        std::cout << "You hit the enemy's weakness!\n";
        std::cout << "[ONE MORE!]\n";
        playerTurn(mc, ally1, ally2, ally3, enemy1, enemy2, enemy3, enemy4, itemList);
    }
}
