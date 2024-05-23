#include <iostream>
#include <vector>
#include <string>

// 5/9/24: Partially implemented skills (needs debugging), must fix issue with defeating enemies removing too many enemies
// 5/9/24: Implemented skills, their types, and "One More" mechanics. Also fixed and redid the enemy removal system to handle multi-target skills (Not yet implemented)
// 5/10/24: Cleaned up a bit of the code and began working on some constructors.
// 5/11/24: Put enemies into an array, broke one more mechanic
// 5/12/24: Fixed one more mechanic
// 5/13/24: Minor work on cleaning up code, sp management
// 5/17/24: (WIP) Implement other allies and put mc into the same array as them
// 5/22/2024: Implemented other allies (Must optimize and fix the examine function)

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
        std::string weakness = "NULL";
        bool alive = false;
        bool guarding = false;
        std::string status = "None";
        int recovery = 0;
    }
};

class ally : public baseCharacter // Ally class
{
public:
    ally()
    {
        name = "NULL";
        level = 1;
        hp = 15;
        sp = 20;
        atk = 7;
        def = 5;
        mgk = 3;
        weakness = "NULL";
        alive = false;
    }
    ally(int HP, int SP, int Atk, int Def, int Mgk, std::string Weakness, bool Alive)
    {
        hp = HP;
        sp = SP;
        atk = Atk;
        def = Def;
        mgk = Mgk;
        weakness = Weakness;
        alive = Alive;
    }
};

class enemy : public baseCharacter // Enemy class
{
public:
    enemy()
    {
        name = "NULL";
        level = 1;
        maxHP = 10;
        hp = 10;
        atk = 1;
        def = 0;
        mgk = 0;
    }
    enemy(std::string Name, int Level, int MaxHP, int HP, int Atk, int Def, int Mgk, std::string Weakness)
    {
        name = Name;
        level = Level;
        maxHP = MaxHP;
        hp = HP;
        atk = Atk;
        def = Def;
        mgk = Mgk;
        weakness = Weakness;
        alive = true;
    }
};
// Story Elements
std::string characterCreation();
void story();

// Battle Functions
void encounter(ally allies[], enemy enemies[], items itemList[]);

// Enemy Turn
void enemyTurn(enemy &currentEnemy, ally allies[]);
void enemyAttack(enemy &currentEnemy, ally allies[]);

// Player Turn
void playerTurn(ally &currentAlly, ally allies[], enemy enemies[], items itemList[]);
void attackTarget(ally &currentAlly, enemy enemies[], bool &validSel);
void skillTarget(ally &currentAlly, enemy enemies[], bool &validSel, ally allies[], items itemList[]);
void playerAttack(ally &currentAlly, enemy &selectedEnemy, enemy enemies[]);
void playerSkill(skills skill, ally &currentAlly, enemy &selectedEnemy, enemy enemies[], ally allies[], items itemList[]);
void examineCombatants(ally allies, enemy enemies[]);

int main()
{
    enemy enemies[4];
    ally allies[4];
    allies[0] = ally(20, 20, 7, 5, 5, "curse", true);
    allies[1] = ally(1, 20, 7, 5, 5, "bless", true);
    allies[2] = ally(20, 20, 7, 5, 5, "fire", true);
    allies[3] = ally(20, 20, 7, 5, 5, "ice", true);

    // Items

    items itemList[20];

    // Slime
    enemy slime = enemy("Slime", 1, 5, 5, 3, 1, 0, "fire");

    // Minotaur
    enemy minotaur = enemy("Minotaur", 1, 20, 20, 7, 3, 2, "elec");

    // Skills
    skills agi = skills("Agi", "mgk", 5, 3, "fire", "burn");

    allies[0].skills[0] = agi;
    allies[0].skillsHeld = 1;
    allies[1].name = "Ally 2";
    allies[1].skills[0] = agi;
    allies[1].skillsHeld = 1;
    allies[2].name = "Ally 3";
    allies[2].skills[0] = agi;
    allies[2].skillsHeld = 1;
    allies[3].name = "Ally 4";
    allies[3].skills[0] = agi;
    allies[3].skillsHeld = 1;

    enemies[0] = slime;
    enemies[1] = minotaur;
    enemies[2] = slime;
    enemies[3] = minotaur;

    allies[0].name = characterCreation();
    story();
    encounter(allies, enemies, itemList); // Encounter is called

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
void encounter(ally allies[], enemy enemies[], items itemList[])
{
    std::cout << "An enemy appears!\n";
    std::cout << "Battle Start!\n";
    if (!allies[0].alive || !enemies[0].alive)
    {
        std::cerr << "MC or Enemy 1 is not alive!\n";
        return;
    }

    while (allies[0].alive && enemies[0].alive)
    {
        // playerTurn
        for (int i = 0; i < 4; i++)
        {
            playerTurn(allies[i], allies, enemies, itemList);
        }
        // enemyTurn
        for (int i = 0; i < 4; i++)
        {
            if (!allies[0].alive) // Check if main character is alive before preceding
            {
                return;
            }
            enemyTurn(enemies[i], allies);
        }
    }
}
void enemyAttack(enemy &currentEnemy, ally allies[])
{
    int dmgDelt = 0;
    int target = 0;

    bool validAct = false;
    while (validAct == false)
    {
        int target = (rand() % 4);
        if (!allies[target].alive)
        {
            // Redo if target is not alive
        }
        else
        {
            if (currentEnemy.atk <= allies[target].def)
            {
                dmgDelt = 1;
            }
            else
            {
                dmgDelt = (currentEnemy.atk - allies[target].def);
            }
            if (allies[target].guarding && dmgDelt != 1)
            {
                dmgDelt /= 2;
                allies[target].guarding = false;
            }
            allies[target].hp -= (dmgDelt);
            std::cout << currentEnemy.name << " attacked " << allies[target].name << " for " << dmgDelt << " damage!\n";
            if (allies[target].hp <= 0)
            {
                std::cout << allies[target].name << " has fainted!\n";
                allies[target].alive = false;
                return;
            }
            std::cout << allies[target].name << " has " << allies[target].hp << " health remaining!\n";
            validAct = true;
            break;
            if (currentEnemy.atk <= allies[target].def)
            {
                dmgDelt = 1;
            }
            else
            {
                dmgDelt = (currentEnemy.atk - allies[target].def);
            }
            if (allies[target].guarding && dmgDelt != 1)
            {
                dmgDelt /= 2;
                allies[target].guarding = false;
            }
            allies[target].hp -= (dmgDelt);
            std::cout << currentEnemy.name << " attacked " << allies[target].name << " for " << dmgDelt << " damage!\n";
            if (allies[target].hp <= 0)
            {
                std::cout << allies[target].name << " has fainted!\n";
                allies[target].alive = false;

                for (int i = 0; i < 4; i++)
                {
                    if (!allies[i].alive)
                    {
                        int search = i;
                        while (!allies[search].alive)
                        {
                            if (search < 4)
                            {
                                search++;
                            }
                        }
                        allies[search] = allies[i];
                    }
                }
                return;
            }
            std::cout << allies[target].name << " has " << allies[target].hp << " health remaining!\n";
            validAct = true;
        }
    }
}
void enemyTurn(enemy &currentEnemy, ally allies[])
{
    currentEnemy.status = "None";
    enemyAttack(currentEnemy, allies);
    if (!allies[0].alive)
    {
        return;
    }
}
void story()
{
    std::cout << "You wake up in an unfamiliar place.\n";
    std::cout << "Where am I?\n";
    std::cout << "Looking around, you see something approaching\n";
}
void examineCombatants(ally allies[], enemy enemies[])
{
    std::cout << "[Examine]\n\n";
    std::cout << "[Allies]\n";

    for (int i = 0; i < 4; i++)
    {
        if (allies[i].alive)
        {
            std::cout << i + 1 << ") " << allies[i].name << '\n';
            std::cout << "(HP: " << allies[i].hp << ")\n";
            std::cout << "(SP: " << allies[i].sp << ")\n";
        }
    }
    std::cout << '\n'
              << "[Enemies]\n";

    for (int i = 0; i < 4; i++)
    {
        if (enemies[i].alive)
        {
            std::cout << i + 1 << ") " << enemies[i].name << '\n';
            std::cout << "(HP: " << enemies[i].hp << ")\n";
            std::cout << "(SP: " << enemies[i].sp << ")\n";
        }
    }
}
void playerTurn(ally &currentAlly, ally allies[], enemy enemies[], items itemList[])
{
    int dmgDelt;
    std::string type;
    skills selectedSkill;

    int selection;
    bool validSel = false;

    std::cout << currentAlly.name << "'s turn!\n";
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
            attackTarget(currentAlly, enemies, validSel);
            break;
        case 2:
            skillTarget(currentAlly, enemies, validSel, allies, itemList);
            break;
        case 3:
            std::cout << currentAlly.name << " is guarding!\n";
            currentAlly.guarding = true;
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
            examineCombatants(allies, enemies);
            break;
        default:
            std::cerr << "Invalid selection!\n";
            break;
        }
    }
}
void attackTarget(ally &currentAlly, enemy enemies[], bool &validSel)
{
    int selection = 0;
    int counter = 0;

    std::cout << "[TARGET]\n";
    std::cout << "1) " << enemies[0].name << '\n';
    std::cout << "(HP: " << enemies[0].hp << ")\n";
    if (enemies[1].alive)
    {
        std::cout << "2) " << enemies[1].name << '\n';
        std::cout << "(HP: " << enemies[1].hp << ")\n";
    }
    if (enemies[2].alive)
    {
        std::cout << "3) " << enemies[2].name << '\n';
        std::cout << "(HP: " << enemies[2].hp << ")\n";
    }
    if (enemies[3].alive)
    {
        std::cout << "4) " << enemies[3].name << '\n';
        std::cout << "(HP: " << enemies[3].hp << ")\n";
    }
    std::cout << "5) [Back]\n";

    std::cout << "Which enemy would you like to target?\n";
    std::cin >> selection;
    while (validSel == false)
    {
        switch (selection)
        {
        case 1:
            playerAttack(currentAlly, enemies[0], enemies);
            validSel = true;
            break;
        case 2:
            if (enemies[1].alive)
            {
                playerAttack(currentAlly, enemies[1], enemies);
                validSel = true;
            }
            else
            {
                std::cout << "Invalid selection!\n";
            }
            break;
        case 3:
            if (enemies[2].alive)
            {
                playerAttack(currentAlly, enemies[2], enemies);
                validSel = true;
            }
            else
            {
                std::cout << "Invalid selection!\n";
            }
            break;
        case 4:
            if (enemies[3].alive)
            {
                playerAttack(currentAlly, enemies[3], enemies);
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
void skillTarget(ally &currentAlly, enemy enemies[], bool &validSel, ally allies[], items itemList[])
{
    int selection = 0;
    int skillSelection = 0;
    int backPos = 0;

    while (!validSel)
    {
        std::cout << "[Skills]\n";
        std::cout << "[Current SP: " << currentAlly.sp << "]\n";
        for (int i = 0; i < currentAlly.skillsHeld; i++)
        {
            std::cout << i + 1 << ") " << currentAlly.skills[i].name << " (SP Cost: " << currentAlly.skills[i].spCost << ")\n";
            backPos = i + 1;
        }
        std::cout << "(" << backPos + 1 << " <-- Back\n";
        std::cin >> selection;
        if (currentAlly.skills[selection - 1].spCost > currentAlly.sp)
        {
            std::cout << "You don't have enough sp!\n";
        }
        else if (selection == backPos + 1)
        {
            return; // Go back to previous menu
        }
        else
        {
            std::cout << "[TARGET]\n";
            std::cout << "1) " << enemies[0].name << '\n';
            std::cout << "(HP: " << enemies[0].hp << ")\n";
            if (enemies[1].alive)
            {
                std::cout << "2) " << enemies[1].name << '\n';
                std::cout << "(HP: " << enemies[1].hp << ")\n";
            }
            if (enemies[2].alive)
            {
                std::cout << "3) " << enemies[2].name << '\n';
                std::cout << "(HP: " << enemies[2].hp << ")\n";
            }
            if (enemies[3].alive)
            {
                std::cout << "4) " << enemies[3].name << '\n';
                std::cout << "(HP: " << enemies[3].hp << ")\n";
            }
            std::cout << "5) [Back]\n";

            std::cout << "Which enemy would you like to target?\n";
            std::cin >> skillSelection;

            switch (skillSelection)
            {
            case 1:
                playerSkill(currentAlly.skills[selection - 1], currentAlly, enemies[0], enemies, allies, itemList);
                validSel = true;
                break;
            case 2:
                if (enemies[1].alive)
                {
                    playerSkill(currentAlly.skills[selection - 1], currentAlly, enemies[1], enemies, allies, itemList);
                    validSel = true;
                }
                else
                {
                    std::cout << "Invalid selection!\n";
                }
                break;
            case 3:
                if (enemies[2].alive)
                {
                    playerSkill(currentAlly.skills[selection - 1], currentAlly, enemies[2], enemies, allies, itemList);
                    validSel = true;
                }
                else
                {
                    std::cout << "Invalid selection!\n";
                }
                break;
            case 4:
                if (enemies[3].alive)
                {
                    playerSkill(currentAlly.skills[selection - 1], currentAlly, enemies[3], enemies, allies, itemList);
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
}
void playerAttack(ally &currentAlly, enemy &selectedEnemy, enemy enemies[])
{
    int dmgDelt = 0;

    dmgDelt = currentAlly.atk - selectedEnemy.def;
    std::cout << currentAlly.name << " attacked " << selectedEnemy.name << " for " << dmgDelt << " damage!\n";
    selectedEnemy.hp -= dmgDelt;

    if (selectedEnemy.hp <= 0)
    {
        std::cout << selectedEnemy.name << " was defeated!\n";
        selectedEnemy.alive = false;

        if (!enemies[0].alive && enemies[1].alive)
        {
            enemies[0] = enemies[1];
            enemies[1].alive = false;
        }
        if (!enemies[1].alive && enemies[2].alive)
        {
            if (!enemies[0].alive)
            {
                enemies[0] = enemies[2];
                enemies[2].alive = false;
            }
            else
            {
                enemies[1] = enemies[2];
                enemies[2].alive = false;
            }
        }
        if (!enemies[2].alive && enemies[3].alive)
        {
            if (!enemies[0].alive)
            {
                enemies[0] = enemies[3];
                enemies[3].alive = false;
            }
            else
            {
                enemies[2] = enemies[3];
                enemies[3].alive = false;
            }
        }
        if (enemies[3].alive)
        {
            enemies[3].alive = false;
        }
    }
    else
    {
        std::cout << selectedEnemy.name << " has " << selectedEnemy.hp << " HP remaining!\n";
    }
}
void playerSkill(skills skill, ally &currentAlly, enemy &selectedEnemy, enemy enemies[], ally allies[], items itemList[])
{
    int dmgDelt = 0;
    bool oneMore = false;

    currentAlly.sp -= skill.spCost;
    dmgDelt = (skill.dmg + (currentAlly.mgk * 1.2)) - selectedEnemy.def;
    std::cout << currentAlly.name << " used " << skill.name << " on " << selectedEnemy.name << "!\n";
    std::cout << currentAlly.name << " delt " << dmgDelt << " damage!\n";
    selectedEnemy.hp -= dmgDelt;

    if (skill.affinity == selectedEnemy.weakness && selectedEnemy.status != "downed")
    {
        selectedEnemy.status = "downed";
        oneMore = true;
    }

    if (selectedEnemy.hp <= 0)
    {
        std::cout << selectedEnemy.name << " was defeated!\n";
        selectedEnemy.alive = false;

        if (!enemies[0].alive && enemies[1].alive)
        {
            enemies[0] = enemies[1];
            enemies[1].alive = false;
        }
        if (!enemies[1].alive && enemies[2].alive)
        {
            if (!enemies[0].alive)
            {
                enemies[0] = enemies[2];
                enemies[2].alive = false;
            }
            else
            {
                enemies[1] = enemies[2];
                enemies[2].alive = false;
            }
        }
        if (!enemies[2].alive && enemies[3].alive)
        {
            if (!enemies[0].alive)
            {
                enemies[0] = enemies[3];
                enemies[3].alive = false;
            }
            else
            {
                enemies[2] = enemies[3];
                enemies[3].alive = false;
            }
        }
        if (enemies[3].alive)
        {
            enemies[3].alive = false;
        }
    }
    else
    {
        std::cout << selectedEnemy.name << " has " << selectedEnemy.hp << " HP remaining!\n";
    }
    if (oneMore == true)
    {
        std::cout << "You hit the enemy's weakness!\n";
        std::cout << "[ONE MORE!]\n";
        playerTurn(currentAlly, allies, enemies, itemList);
        oneMore = false;
    }
}
