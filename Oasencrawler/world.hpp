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

class GameWorld {
private:
    int width;
    int height;
    int relicCount;
    Field** fields;
    void ensureAtLeastOneRelic();
    void showLegend();

public:
    GameWorld(int w, int h);
    ~GameWorld();
    Enemy enemy;
    int difficulty;
    void showWorld();
    void initializeWorld();
    int getRelicCount() const; 
    int getWidth() const; 
    int getHeight() const; 

    // Getter
    enum FieldType getFieldType(int x, int y) const;

    // Setter
    void setFieldTypeToPlayer(int x, int y);
    void setFieldTypeToEmpty(int x, int y);
    void setEnemyOnFieldTrue(int x, int y);
    void setEnemyOnFieldFalse(int x, int y);
    void placeEnemy();
};