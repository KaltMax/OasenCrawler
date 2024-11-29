class Player {
public:
    int lifePoints;
    int relicPoints;
    int playerX;
    int playerY;
    bool warrior;
    bool rogue;
    bool sorcerer;

    Player(int hp, int rp);
    ~Player();
    void showStats();
    void printWarrior();
    void printRogue();
    void printSorcerer();
};