#include <iostream>
// Enum für die Feldtypen der Map
enum FieldType { EMPTY, DANGER, WELL, RELIC, PLAYER, ENEMY };

struct Enemy {
    int enemyX;
    int enemyY;
};

struct Field {
    FieldType type;
    bool enemyOnField;
};

// Forward declaration der Klassen
class Player;
class GameWorld;

class Player {
public:
    int lifePoints;
    int relicPoints;
    int playerX;
    int playerY;

    Player(int hp, int rp); 
    void showStats();
};

