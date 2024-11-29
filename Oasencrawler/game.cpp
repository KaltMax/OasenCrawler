#include "game.hpp"
#include <iostream>
#include <string>

// Constructor für die Game Klasse
// Initialisiert den Spieler, die Welt und den Gegner
Game::Game(int playerHP, int playerRP, int worldWidth, int worldHeight)
    : player(playerHP, playerRP), world(worldWidth, worldHeight) {
}

// Main game loop that manages the gameplay
void Game::run() {
    bool running = true;
    while (running) {
        // Spielwelt anzeigen
        world.showWorld();
        // Spieler-Stats anzeigen
        player.showStats();
        // Einlesen des Spielzuges
        char move = input();
        // Den Spieler bewegen und Events abhandeln
        movePlayer(move);
        // Move Enemy
        moveEnemy();
        // Prüfen, ob eine der Abbruchbedingungen erfüllt ist
        running = !gameOver();
    }
}
// Charakterauswahl
void Game::chooseCharacter() {
    clearScreen();
    std::cout << "Choose your Character!\n" << std::endl;

    std::cout << "The Warrior" << std::endl;
    player.printWarrior();
    std::cout << "The Warrior's combat prowess increases the chance to block Damage on DANGER-fields.\n" << std::endl;

    std::cout << "The Rogue" << std::endl;
    player.printRogue();
    std::cout << "The swiftnes and agility of the Rogue provides him with a chance to dodge the attacks of the ENEMY.\n" << std::endl;

    std::cout << "The Sorcerer" << std::endl;
    player.printSorcerer();
    std::cout << "The Sorcerer's mastery of magical arts grants a chance to reclaim a Life-Point from ancient Relics.\n" << std::endl;

    while (true) {
        char input = ' ';
        std::cout << "Enter 'w' for Warrior, 'r' for Rogue or 's' for Sorcerer: \n" << std::endl;
        std::cin >> input;
        // Setzte den bool für den ausgewählten Charakter auf true
        if (input == 'w') {
            player.warrior = true;
            break;
        }
        else if (input == 'r') {
            player.rogue = true;
            break;
        }
        else if (input == 's') {
            player.sorcerer = true;
            break;
        }
        else {
            std::cout << "Invalid Input! Try again!\n" << std::endl;
        }
    }
    clearScreen();
}

char Game::input() {
    char move = ' ';
    while (true) {
        int newX = player.playerX;
        int newY = player.playerY;
        // Eingabeprompt
        std::cout << "What's your next move?" << std::endl;
        std::cout << "up(w), right(d), down(s), left(a)" << std::endl;
        std::cin >> move;
        std::cin.ignore();

        // Eingabeüberprüfung
        switch (move) {
        case 'w':
            newY--;
            break;
        case 'd':
            newX++;
            break;
        case 's':
            newY++;
            break;
        case 'a':
            newX--;
            break;
        default:
            std::cout << "\n" << "Invalid input! Try again!" << "\n" << std::endl;
            continue;
        }
        // Überprüfung, ob die Bewegung im Rahmen der Spielwelt ist
        if (newX >= 0 && newX < world.getWidth() && newY >= 0 && newY < world.getHeight()) {
            return move;
        }
        else {
            std::cout << "\n" << "You can't move out of the world. Try again!" << "\n" << std::endl;
        }
    }
}

void Game::movePlayer(char move) {
    // Setzt das Feld, auf dem sich der Spieler vor der Bewegung findet auf EMPTY
    world.setFieldTypeToEmpty(player.playerX, player.playerY);

    // Den Spieler bewegen
    switch (move) {
        case 'w':
            player.playerY--;
            break;
        case 'd':
            player.playerX++;
            break;
        case 's':
            player.playerY++;
            break;
        case 'a':
            player.playerX--;
            break;
    }
    // Den Typen des Feldes ermitteln
    enum FieldType eventType = world.getFieldType(player.playerX, player.playerY);
    // Den Spieler auf der neuen Position in der Spielwelt setzen
    world.setFieldTypeToPlayer(player.playerX, player.playerY);
    // Abhandeln des jeweiligen Events
    events(eventType);
    // Prüfen, ob der Gegner auf dem Feld ist
    if (player.playerX == world.enemy.enemyX && player.playerY == world.enemy.enemyY) {
        enemyEncounter();
    }
}

void Game::moveEnemy() {
    int enemyX = world.enemy.enemyX;
    int enemyY = world.enemy.enemyY;
    int playerX = player.playerX;
    int playerY = player.playerY;
    int worldWidth = world.getWidth();
    int worldHeight = world.getHeight();

    // Randomizer, um zu entscheiden, ob sich der Gegner gezielt auf den Spieler zubewegt, oder sich 2 Felder random in eine Richtung bewegt
    int moveType = rand() % 100;

    if (moveType < 80) { // 80%ige Chance sich strategisch in Richtung Spieler zu bewegen
        int distanceX = std::abs(enemyX - playerX);
        int distanceY = std::abs(enemyY - playerY);

        if (distanceX > distanceY) {
            if (enemyX < playerX) {
                enemyX++;
            }
            else if (enemyX > playerX) {
                enemyX--;
            }
        }
        else {
            if (enemyY < playerY) {
                enemyY++;
            }
            else if (enemyY > playerY) {
                enemyY--;
            }
        }
    }
    else { // 20% Chance, dass der Gegner sich 2 Felder in eine random Richtung bewegt
        int direction = rand() % 4; // Random Entscheidung, in welche Richtung sich der Gegner bewegt
        switch (direction) {
        case 0:
            if (enemyX > 1) {
                enemyX -= 2;
                break;
            }
        case 1:
            if (enemyX < worldWidth - 2) {
                enemyX += 2;
                break;
            }
        case 2:
            if (enemyY > 1) {
                enemyY -= 2;
                break;
            }
        case 3:
            if (enemyY < worldHeight - 2) {
                enemyY += 2;
                break;
            }
        }
    }

    // Die Position des Gegners wird upgedated 
    world.setEnemyOnFieldFalse(world.enemy.enemyX, world.enemy.enemyY);
    world.enemy.enemyX = enemyX;
    world.enemy.enemyY = enemyY;
    world.setEnemyOnFieldTrue(enemyX, enemyY);

    // Falls der Gegner den Spieler erreicht hat, wird das enemyEncounter Event ausgelöst
    if (player.playerX == world.enemy.enemyX && player.playerY == world.enemy.enemyY) {
        enemyEncounter();
    }
}

void Game::events(enum FieldType eventType) {
    clearScreen();
    switch (eventType) {
        case EMPTY:
            empty();
            break;
        case RELIC:
            relic();
            break;
        case DANGER:
            danger();
            break;
        case WELL:
            well();
            break;
    }
}

bool Game::gameOver() {
    if (player.lifePoints <= 0) {
        dead();
        return true;
    }
    else if (world.getRelicCount() == 0) {
        allRelics();
        return true;
    }
    return false;
}

bool Game::playAgain() {
    while (true) {
        std::string againInput = "";
        std::cout << "If you want to play Again press ENTER. If you are weak and want to quit press 'q'" << std::endl;
        std::getline(std::cin, againInput);
        if (againInput.empty()) {
            return true;
        }
        else if (againInput == "q") {
            clearScreen();
            theEnd();
            std::cout << "Press ENTER to close the game!\n";
            std::cin.get();
            return false;
        }
    }
}

void Game::regenerateWorld() {
    // Setze die Koordinaten des Spielers und des Gegners wieder auf das erste bzw. letzte Feld
    int width = world.getWidth();
    int height = world.getHeight();
    player.playerX = 0;
    player.playerY = 0;
    world.enemy.enemyX = width - 1;
    world.enemy.enemyY = height - 1;
    // Create a new game world with the specified dimensions
    world.initializeWorld();
}

void Game::empty() {
    clearScreen();
    std::cout <<
        "    .    _    +     .  ______   .          .\n"
        " (      /|\\      .    |      \\      .   +\n"
        "     . |||||     _    | |   | | ||         .\n"
        ".      |||||    | |  _| | | | |_||    .\n"
        "   /\\  ||||| .  | | |   | |      |       .\n"
        "__||||_|||||____| |_|_____________\\__________\n"
        ". |||| |||||  /\\   _____      _____  .   .\n"
        "  |||| ||||| ||||   .   .  .         ________\n"
        " . \\|`-'|||| ||||    __________       .    .\n"
        "    \\__ |||| ||||      .          .     .\n"
        " __    ||||`-'|||  .       .    __________\n"
        ".    . |||| ___/  ___________             .\n"
        "   . _ ||||| . _               .   _________\n"
        "_   ___|||||__  _ \\\\--//    .          _\n"
        "     _ `---'    .)=\\oo|=(.   _   .   .    .\n"
        "_  ^      .  -    . \\.| \n\n";
    std::cout << "Endless sands stretch before you, their silence broken only by the haunting howls carried on the wind...\n" << std::endl;
    enterToContinue();
}

void Game::relic() {
    clearScreen();
    std::cout << "                       \\ : /" << std::endl;
    std::cout << "                    '-: __ :-'" << std::endl;
    std::cout << "                    -:  )(_ :--" << std::endl;
    std::cout << "                    -' |r-_i'-" << std::endl;
    std::cout << "            ,sSSSSs,   (2-,7" << std::endl;
    std::cout << "            sS';:'`Ss   )-j" << std::endl;
    std::cout << "           ;K e (e s7  /  (" << std::endl;
    std::cout << "            S, ''  SJ (  ;/" << std::endl;
    std::cout << "            sL_~~_;(S_)  _7" << std::endl;
    std::cout << "|,          'J)_.-' />'-' `Z" << std::endl;
    std::cout << "j J         /-;-A'-'|'--'-j\\" << std::endl;
    std::cout << " L L        )  |/   :    /  \\" << std::endl;
    std::cout << "  \\ \\       | | |    '._.'|  L" << std::endl;
    std::cout << "   \\ \\      | | |       | \\  J" << std::endl;
    std::cout << "    \\ \\    _/ | |       |  ',|" << std::endl;
    std::cout << "     \\ L.,' | | |       |   |/" << std::endl;
    std::cout << "    _;-r-<_.| \\=\\    __.;  _/" << std::endl;
    std::cout << "      {_}\"  L-'  '--'   / /|" << std::endl;
    std::cout << "            |   ,      |  \\|" << "\n" << std::endl;
    std::cout << "Amid whispers of the past, you uncover the remains of an ancient ruin." << std::endl;
    std::cout << "Your eyes catch a glint beneath the rubble. With eager hands, you unearth a relic steeped in history." << std::endl;
    std::cout << "A surge of triumph fills you - Congratulations, you've earned 1 Relic-Point!\n\n" << std::endl;
    
    // Erhöhre die RP um 1
    player.relicPoints++;

    // Falls der Charakter ein Sorcerer ist, hat er eine 20%ige Chance einen Lebenspunkt zu erhalten
    if (player.sorcerer) {
        int chance = rand() % 100; 
        if (chance < 20) { 
            std::cout << "With a flourish of arcane power, you weave a spell over the ancient relic, drawing forth its hidden energy." << std::endl;
            std::cout << "A surge of vitality flows through you, granting 1 additional Life-Point!\n" << std::endl;
            player.lifePoints++;
        }
    }
    enterToContinue();
}

void Game::well() {
    clearScreen();
    std::cout << "     _      " << std::endl;
    std::cout << "    / \\     " << std::endl;
    std::cout << "   / '.\\    " << std::endl;
    std::cout << "  /   '.\\   " << std::endl;
    std::cout << " /     '.\\  " << std::endl;
    std::cout << " ~|~~~~~|~  " << std::endl;
    std::cout << " +|-===-|;-. " << std::endl;
    std::cout << "  |  |  |  `- " << std::endl;
    std::cout << " _|--|--|_    " << std::endl;
    std::cout << "|--.....--|   " << std::endl;
    std::cout << "|--.....--|   .''." << std::endl;
    std::cout << "|--.....--|  |~~|" << std::endl;
    std::cout << " ~~-----~~    ~~\n" << std::endl;

    // Mit steigendem Schwierigkeitsgrad verringert sich die Wahrscheinlichkeit einen Lebenspunkt zu erhalten
    int difficultyrandomizer = 10 + world.difficulty;
    int random = rand() % difficultyrandomizer;
    if (random <= 10) {
        player.lifePoints++; // Erhöhre die LP um 1

        std::cout << "Discovering a waterwell, you take a refreshing sip." << std::endl;
        std::cout << "Vitality surges within you, increasing your Life-Points by 1.\n" << std::endl;
    }
    else {
        std::cout << "Approaching the waterwell, you find it sadly dry." << std::endl;
        std::cout << "No vitality found here, your Life-Points remain unchanged." << std::endl;
        std::cout << "The quest for sustenance continues.\n" << std::endl;
    }

    enterToContinue();
}

void Game::danger() {
    clearScreen();
    std::cout << "                           __.--|~|--.__                               ,,;/;" << std::endl;
    std::cout << "                         /~     | |    ;~\\                          ,;;;/;;'" << std::endl;
    std::cout << "                        /|      | |    ;~\\\\                      ,;;;;/;;;'" << std::endl;
    std::cout << "                       |/|      \\_/   ;;;|\\                    ,;;;;/;;;;'" << std::endl;
    std::cout << "                       |/ \\          ;;;/  )                 ,;;;;/;;;;;'" << std::endl;
    std::cout << "                   ___ | ______     ;_____ |___....__      ,;;;;/;;;;;'" << std::endl;
    std::cout << "             ___.-~ \\\\(| \\  \\.\ \__/ /./ /:|)~   ~   \\   ,;;;;/;;;;;'" << std::endl;
    std::cout << "         /~~~    ~\\    |  ~-.     |   .-~: |//  _.-~~--,;;;;/;;;;;'" << std::endl;
    std::cout << "        (.-~___     \\.'|    | /-.__.-\\|::::| //~     ,;;;;/;;;;;'" << std::endl;
    std::cout << "        /      ~~--._ \\|   /          `\\:: |/      ,;;;;/;;;;;'" << std::endl;
    std::cout << "     .-|             ~~|   |  /V\"\"\"\"V\\ |:  |     ,;;;;/;;;;;' \\" << std::endl;
    std::cout << "    /                   \\  |  ~`^~~^'~ |  /    ,;;;;/;;;;;'    ;" << std::endl;
    std::cout << "   (        \\             \\|`\\._____./'|/    ,;;;;/;;;;;'      '\\" << std::endl;
    std::cout << "  / \\        \\                             ,;;;;/;;;;;'     /    |" << std::endl;
    std::cout << " |            |                          ,;;;;/;;;;;'      |     |" << std::endl;
    std::cout << "|`-._          |                       ,;;;;/;;;;;'              \\" << std::endl;
    std::cout << " /     `~--._   \\                      ;;;;;;;;'                 |" << std::endl;
    std::cout << " |         _-~- |                     ;;;;;;;;'                 _/\n" << std::endl;

    // Mit steigendem Level erhöht sich die Wahrscheinlichkeit einen Lebenspunkt zu verlieren
    int difficultyRandomizer = 7;

    // Falls der Spieler den Warrior ausgewählt hat erhöht sich der Randomizer und somit die Chance einen LP zu verlieren
    if (player.warrior) {
        difficultyRandomizer += 2;
    }

    if ((difficultyRandomizer - world.difficulty) > 1) {
        difficultyRandomizer = difficultyRandomizer - world.difficulty;
    }
    else {
        difficultyRandomizer = 1;
    }
    int random = rand() % difficultyRandomizer; 
    if (random == 0) {
        player.lifePoints--; // Verringer die LP um 1
        std::cout << "A fearsome Orc looms, roaring and swinging its massive broadsword." << std::endl;
        std::cout << "You're struck with brutal force, losing 1 Life-Point from the jarring impact.\n" << std::endl;
    }
    else { // Nichts passiert
        std::cout << "Confronted by a massive Orc, you wield your Dagger with deadly intent." << std::endl;
        std::cout << "Evading its attacks, you strike true, felling the beast. Courage and swiftness bring victory!\n" << std::endl;
    }
    enterToContinue();
}

void Game::enemyEncounter(){
    // Der Schaden des Enemys startet bei 1 und steigert sich alle 2 Level um 1
    int enemyDamage = 1 + ((world.difficulty - 1) / 2);
    player.lifePoints = player.lifePoints - enemyDamage; 
    // Der Enemy wird wieder neu auf der Spielkarte platziert
    world.setEnemyOnFieldFalse(world.enemy.enemyX, world.enemy.enemyY);
    world.placeEnemy();

    clearScreen();
    // Enemy Display
    std::cout << "                               .-.._    ___" << std::endl;
    std::cout << "                            ,-'   |:\\ /'--.`." << std::endl;
    std::cout << "                           /'    ,|:|/::::| '\\ " << std::endl;
    std::cout << "                         ,'  ,.-:::::::::::.  \\" << std::endl;
    std::cout << "                       _/' /::::::::::::::::`  \\" << std::endl;
    std::cout << "                      /'  ':::::::_,--.::::::`.'\\" << std::endl;
    std::cout << "                     /  ,'::::.,-'     `\\::::::||" << std::endl;
    std::cout << "                    |  /:::_/'           `\\::::||" << std::endl;
    std::cout << "                    |  \\::-                \\:::||" << std::endl;
    std::cout << "                    /_                      \\_/ |" << std::endl;
    std::cout << "                   |  '-._                      /" << std::endl;
    std::cout << "                   |'.    '`-..._              |" << std::endl;
    std::cout << "                   ..  '--_             ''----.|" << std::endl;
    std::cout << "                   | `._   '-----  '''----__,..\\" << std::endl;
    std::cout << "                   |.._ '-.._________..--'   ,'|_" << std::endl;
    std::cout << "                   |   `--..__            _,' /| ''--." << std::endl;
    std::cout << " ''''''---..__     |          '`-------'''   /-\\ .-.._\\_" << std::endl;
    std::cout << "              '-\\__ \\-----....__        _..'   ,.-. `. .`\\" << std::endl;
    std::cout << "                   '`.          \"\"\"--\"\"\"    _/' _. \\ \\  | \\" << std::endl;
    std::cout << "                      \\--..___       ___..--   / | ' |  |  \\   ___...---" << std::endl;
    std::cout << "             _,........\\      \"\"\"--\"\"        ./  |/-..__=..|,-'\n" << std::endl;

    std::cout << "As the ground trembles, the colossal sandworm emerges, a leviathan of the dunes." << std::endl;
    std::cout << "Its roar shatters the desert silence, its jaws gaping wide in hunger.In a flash, it strikes, sealing your fate." << std::endl;

    // Falls Rogue als Charakter ausgewählt wurde, hat der Spieler eine 15%ige Chance den Gegner auszuweichen
    int chance = rand() % 100;
    if (player.rogue && chance < 15) {
        std::cout << "But with a swift jump to the side, you evade the leviathan's strike and manage to flee.\n" << std::endl;
    }
    else
    {
        std::cout << "The desert claims its due. You have been bested by the desert titan!" << std::endl;
        std::cout << "You lose " << enemyDamage << " Life - Point(s)!\n" << std::endl;
    }

    //Enemy logic
    enterToContinue();
}

void Game::dead() {
    clearScreen();
    //Dead Display
    std::cout <<
        "                      /`._      ,\n"
        "                     /     \\   / \\\n"
        "                     ) ,-==-> /\\/ \\\n"
        "                      )__\\\\/ // \\  |\n"
        "                     /  /' \\//   | |\n"
        "                    /  (  /|/    | /\n"
        "                   /     //|    /,'\n"
        "                  // /  (( )    '\n"
        "                 //     // \\    |\n"
        "                //     (#) |\n"
        "               /        )\\/ \\   '\n"
        "              /        /#/   )\n"
        "             /         \\#\\  /)\n"
        "            ///________/#/_/'\n\n";
    // Dead Message
    std::cout << "You got " << player.relicPoints << " Relic-Points in total and reached Level " << world.difficulty << "\n" << std::endl;
    std::cout << "Your journey has come to a harrowing end as your Life-Points have been extinguished." << std::endl;
    std::cout << "In the annals of time, your story will be remembered—a testament to the trials you faced." << std::endl;
    std::cout << "Rest now, for your struggle is over.\n" << std::endl;
    // Setzt die Spielerstats und den Schwierigkeitsgrad wieder zurück
    player.lifePoints = 10;
    player.relicPoints = 0;
    world.difficulty = 0;
}

void Game::allRelics() {
    clearScreen();
    // Alle Relikte Display 
    std::cout << " _________|________________.=\"\"_;=.______________|_____________________|_______\n";
    std::cout << "|                   |  ,-\"_,=\"\"     `\"=.|                  |\n";
    std::cout << "|___________________|__\"=._o`\"-._        `\"=.______________|___________________\n";
    std::cout << "          |                `\"=._o`\"=._      _`\"=._                     |\n";
    std::cout << " _________|_____________________:=._o \"=._.\"_.-=\"'\"=.__________________|_______\n";
    std::cout << "|                   |    __.--\" , ; `\"=._o.\" ,-\"\"\"-._ \".   |\n";
    std::cout << "|___________________|_._\"  ,. .` ` `` ,  `\"-._\"-._   \". '__|___________________\n";
    std::cout << "          |           |o`\"=._` , \"` `; .\". ,  \"-._\"-._; ;              |\n";
    std::cout << " _________|___________| ;`-.o`\"=._; .\" ` '`.\"\\` . \"-._ /_______________|_______\n";
    std::cout << "|                   | |o;    `\"-.o`\"=._``  '` \" ,__.--o;   |\n";
    std::cout << "|___________________|_| ;     (#) `-.o `\"=.`_.--\"_o.-; ;___|___________________\n";
    std::cout << "____/______/______/___|o;._    \"      `\".o|o_.--\"    ;o;____/______/______/____\n";
    std::cout << "/______/______/______/\"=._o--._        ; | ;        ; ;/______/______/______/_\n";
    std::cout << "____/______/______/______/__\"=._o--._   ;o|o;     _._;o;____/______/______/____\n";
    std::cout << "/______/______/______/______/____\"=._o._; | ;_.--\"o.--\"_/______/______/______/_\n";
    std::cout << "____/______/______/______/______/____\"=.o|o_.--\"\"___/______/______/______/____\n";
    std::cout << "/______/______/______/______/______/______/______/______/______/______/______/\n\n";
    std::cout << "Bravo, brave Adventurer! You've unearthed all ancient relics," << std::endl;
    std::cout << "mastering the desert's secrets through untold dangers. Your name" << std::endl;
    std::cout << "will echo in history, a testament to your bravery. The impossible is achieved!\n" << std::endl;
    std::cout << "You got " << player.relicPoints << " Relic-Points in total and finished Level " << world.difficulty << "\n" << std::endl;
}

void Game::theEnd() {
    std::cout << "Goodbye and thanks for playing!" << std::endl;
    std::cout << "_________          _______    _______  _        ______  \n";
    std::cout << "\\__   __/|\\     /|(  ____ \\  (  ____ \\( (    /|(  __  \\ \n";
    std::cout << "   ) (   | )   ( || (    \\/  | (    \\/|  \\  ( || (  \\  )\n";
    std::cout << "   | |   | (___) || (__      | (__    |   \\ | || |   ) |\n";
    std::cout << "   | |   |  ___  ||  __)     |  __)   | (\\ \\) || |   | |\n";
    std::cout << "   | |   | (   ) || (        | (      | | \\   || |   ) |\n";
    std::cout << "   | |   | )   ( || (____/\\  | (____/\\| )  \\  || (__/  )\n";
    std::cout << "   )_(   |/     \\|(_______/  (_______/|/    )_)(______/ \n";
    std::cout << "                                                        \n";
}