#include "game.hpp"
#include <iostream>
#include <cstdlib> // F�r system("clear") und system("cls")
#include <ctime> // f�r srand

int main() {
    srand(static_cast<unsigned int>(time(nullptr))); // Seeden des random number generators
    bool again = true; // F�r die Spielschleife

    // Spielname + Intro
    header();
    intro();
    // Parameter zur Spielerstellung
    int worldWidth = inputWorldSize();
    int worldHeight = worldWidth;
    // Startstats des Spielers
    int playerHP = 10; 
    int playerRP = 0;  
    Game game(playerHP, playerRP, worldWidth, worldHeight); // Erstellung des Spiels

    // Charakter ausw�hlen
    game.chooseCharacter();

    while(again){
        clearScreen();
        game.run(); // Der Game-Loop
        again = game.playAgain();
        if (again) {
            game.regenerateWorld();
        }
    }
    return 0;
}