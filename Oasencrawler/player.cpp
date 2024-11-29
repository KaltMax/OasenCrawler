#include "player.hpp"
#include <iostream>

// Constructor für das Erstellen des Spielers
Player::Player(int hp, int rp){
    lifePoints = hp;
    relicPoints = rp;
    playerX = 0;
    playerY = 0;
    warrior = false;
    rogue = false;
    sorcerer = false;
}

Player::~Player() {
}

// Stats und Avatar des Spielers anzeigen
void Player::showStats() {
    std::cout << "Character:" << std::endl;
    if (warrior) {
        printWarrior();
    }
    else if (rogue) {
        printRogue();
    }
    else {
        printSorcerer();
    }
    std::cout << "Life-Points: " << lifePoints << std::endl;
    std::cout << "Relic-Points: " << relicPoints << "\n" << std::endl;
}

// Display-Funktionen für den jeweiligen Avatar
void Player::printWarrior() {
    std::cout << "      _,." << std::endl;
    std::cout << "    ,` -.)" << std::endl;
    std::cout << "   ( _/-\\-._" << std::endl;
    std::cout << "  /,|`--._,-^|" << std::endl;
    std::cout << "  \\_| |`-._/||" << std::endl;
    std::cout << "    |  `-, / |" << std::endl;
    std::cout << "    |     || |" << std::endl;
    std::cout << "     `r-._||/   __" << std::endl;
    std::cout << " __,-<_     )`-/  `." << std::endl;
}

void Player::printRogue() {
    std::cout << "        .;;,." << std::endl;
    std::cout << "       ; '\"' ;\\ \\//" << std::endl;
    std::cout << "      \\|o  o|7 \\//" << std::endl;
    std::cout << "      j| ..  | ||/" << std::endl;
    std::cout << "     //'.--.')\\-,/" << std::endl;
    std::cout << "   .-||- '' ||/  `-." << std::endl;
    std::cout << "  ;  | \\ |/ |/ L.  ,|" << std::endl;
    std::cout << "  f\\ |\\| Y  || \\ '._\\" << std::endl;
    std::cout << " j | \\|     (| |   | |" << std::endl;
}

void Player::printSorcerer() {
    std::cout << "         ____ " << std::endl;
    std::cout << "       .'* *.'" << std::endl;
    std::cout << "    __/_*_*(_" << std::endl;
    std::cout << "   / _______ \\" << std::endl;
    std::cout << " _\\_)\\___\\(_/_ " << std::endl;
    std::cout << "/ _((\\- -/))_ \\" << std::endl;
    std::cout << "\\ \\())(-)(()/ /" << std::endl;
    std::cout << " ' \\(((()))/ ' " << std::endl;
    std::cout << "/ ' \\)).))/ ' \\" << std::endl;
}
