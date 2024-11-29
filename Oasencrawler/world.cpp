#include "world.hpp"
#include <iostream>

// Constructor zur Erstellung der Spielwelt
GameWorld::GameWorld(int w, int h){
    width = w;
    height = h;
    relicCount = 0;
    difficulty = 0;
    enemy.enemyX = width - 1;
    enemy.enemyY = height - 1;
    fields = new Field* [height];
    for (int i = 0; i < height; ++i) {
        fields[i] = new Field[width];
    }
    initializeWorld();
}

// Destructor
GameWorld::~GameWorld() {
    for (int i = 0; i < height; ++i) {
        delete[] fields[i]; // Zeilen freigeben
    }
    delete[] fields; // Pointer freigeben
}
// Initialisiert die Felder der Spielwelt
void GameWorld::initializeWorld() {
    difficulty++; // Erhöht nach jeder Generierung den Schwierigkeitsgrad
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            fields[i][j].enemyOnField = false; // Setzte den bool für den Gegner auf jedem Feld auf false
            int random = rand() % 10;
            if (random < 4) {
                fields[i][j].type = EMPTY;
            }
            else if (random < 8) {
                fields[i][j].type = DANGER;
            }
            else if (random == 8) {
                fields[i][j].type = WELL;
            }
            else {
                fields[i][j].type = RELIC;
                relicCount++;
            }
        }
    }
    // Verringert den relicCount, falls es auf [0][0] gesetzt wurde
    if (fields[0][0].type == RELIC) {
        relicCount--;
    }
    // Falls es kein Relikt auf der Spielkarte gibt, wird eins platziert
    if (relicCount == 0) {
        ensureAtLeastOneRelic();
    }
    // Platziert den Spieler auf [0][0]
    fields[0][0].type = PLAYER;

    // Platziert den Gegner auf das letzte Feld
    fields[height - 1][width - 1].enemyOnField = true;
}

// Sicherstellen, dass mindestens ein Relikt auf der Map ist,
// aber nicht bei [0][0], falls dort das einzige Relikt platziert wurde
void GameWorld::ensureAtLeastOneRelic() {
        int x, y;
        do {
            x = rand() % width;
            y = rand() % height;
        } while (x == 0 && y == 0); // Verhindert, dass das Relikt wieder auf [0][0] platziert wird

        fields[y][x].type = RELIC; // Platziert das Relikt an den neuen Koordinaten
        relicCount++;
}

// Platziert den ENEMY auf der Spielwelt
void GameWorld::placeEnemy() {
    int randomHeight = 0;
    int randomWidth = 0;
    // Sichergehen, dass der Gegner nicht auf dem Feld spawnt, auf dem sich er Spieler gerade befindet
    do {
        randomHeight = rand() % height;
        randomWidth = rand() % width;
        enemy.enemyX = randomWidth;
        enemy.enemyY = randomHeight;
    } while (fields[randomHeight][randomWidth].type == PLAYER);

    fields[randomHeight][randomWidth].enemyOnField = true;
}

// Ausgabe der Spielwelt
void GameWorld::showWorld() {
    std::cout << "Level: " << difficulty << std::endl;
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (fields[i][j].enemyOnField) { // Wenn ein Gegner auf dem Feld ist soll das Symbol *E* ausgegeben werden
                std::cout << "*E*  ";
            }
            else {
                switch (fields[i][j].type) {
                case EMPTY:
                    std::cout << "-    ";
                    break;
                case DANGER:
                    std::cout << "D    ";
                    break;
                case WELL:
                    std::cout << "W    ";
                    break;
                case RELIC:
                    std::cout << "R    ";
                    break;
                case PLAYER:
                    std::cout << "*P*  ";
                    break;
                }
            }
        }
        std::cout << "\n\n";
    }
    showLegend();
    std::cout << "Relics left: " << relicCount << "\n"  << std::endl;
}

// Azeige der Spielkarten Legende
void GameWorld::showLegend() {
    std::cout << "Legend: " << std::endl;
    std::cout << "- ..... EMPTY    " << "D ..... DANGER    " << "*P* ... PLAYER" << std::endl;
    std::cout << "W ..... WELL     " << "R ..... RELIC     " << "*E* ... ENEMY" <<  std::endl;
    std::cout << "\n";
}

// Setter
void GameWorld::setFieldTypeToPlayer(int x, int y) {
    if (fields[y][x].type == RELIC) {
        relicCount--;
    }
    fields[y][x].type = PLAYER;
}

void GameWorld::setFieldTypeToEmpty(int x, int y) {
    fields[y][x].type = EMPTY;
}

void GameWorld::setEnemyOnFieldTrue(int x, int y) {
    fields[y][x].enemyOnField = true;
}

void GameWorld::setEnemyOnFieldFalse(int x, int y) {
    fields[y][x].enemyOnField = false;
}

// Getter
enum FieldType GameWorld::getFieldType(int x, int y) const {
    return fields[y][x].type;
}

int GameWorld::getRelicCount() const {
    return relicCount; 
}

int GameWorld::getWidth() const {
     return width; 
}

int GameWorld::getHeight() const { 
    return height; 
}
