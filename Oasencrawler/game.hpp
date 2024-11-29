#include "player.hpp"
#include "world.hpp"
#include "additionalFunctions.hpp"

class Game {
public:
    Game(int playerHP, int playerRP, int worldWidth, int worldHeight);
    void run();
    void chooseCharacter();
    char input();
    void regenerateWorld();

    // Sonstige Funktionen
    bool playAgain();

private:
    Player player;
    GameWorld world;
    void movePlayer(char move);
    void moveEnemy();
    void theEnd();
    bool gameOver();
    // Event Funktionen
    void events(enum FieldType eventType);
    void empty();
    void relic();
    void danger();
    void well();
    void enemyEncounter();
    void dead();
    void allRelics();
};