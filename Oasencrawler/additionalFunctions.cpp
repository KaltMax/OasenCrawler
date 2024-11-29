#include "additionalFunctions.hpp"
#include <iostream>
#include <string>

// Header und Intro des Spiels
void header() {
    std::cout << " _______  _______  _______  _______  _        _______  _______  _______           _        _______  _______ \n";
    std::cout << "(  ___  )(  ___  )(  ____ \\(  ____ \\( (    /|(  ____ \\(  ____ )(  ___  )|\\     /|( \\      (  ____ \\(  ____ )\n";
    std::cout << "| (   ) || (   ) || (    \\/| (    \\/|  \\  ( || (    \\/| (    )|| (   ) || )   ( || (      | (    \\/| (    )|\n";
    std::cout << "| |   | || (___) || (_____ | (__    |   \\ | || |      | (____)|| (___) || | _ | || |      | (__    | (____)|\n";
    std::cout << "| |   | ||  ___  |(_____  )|  __)   | (\\ \\) || |      |     __)|  ___  || |( )| || |      |  __)   |     __)\n";
    std::cout << "| |   | || (   ) |      ) || (      | | \\   || |      | (\\ (   | (   ) || || || || |      | (      | (\\ (   \n";
    std::cout << "| (___) || )   ( |/\\____) || (____/\\| )  \\  || (____/\\| ) \\ \\__| )   ( || () () || (____/\\| (____/\\| ) \\ \\__\n";
    std::cout << "(_______)|/     \\|\\_______)(_______/|/    )_)(_______/|/   \\__/|/     \\|(_______)(_______/(_______/|/   \\__/\n";
    enterToStart();
}

void intro() {
    std::cout << "                                             _______________________" << std::endl;
    std::cout << "   _______________________-------------------                       `\\" << std::endl;
    std::cout << " /:--__                                                              |" << std::endl;
    std::cout << "||< > |                                   ___________________________/" << std::endl;
    std::cout << "| \\__/_________________-------------------                         |" << std::endl;
    std::cout << "|                                                                  |" << std::endl;
    std::cout << " |                       OASENCRAWLER                               |" << std::endl;
    std::cout << " |                                                                  |" << std::endl;
    std::cout << " |        A vast and unforgiving dessert filled with ancient        |" << std::endl;
    std::cout << "  |        mysteries and hidden treasures lies ahead of you.         |" << std::endl;
    std::cout << "  |      Your quest is to collect as many ancient relics             |" << std::endl;
    std::cout << "  |        as possible, artifacts of a forgotten era                 |" << std::endl;
    std::cout << "  |      hidden beneath the shifting dunes.                           |" << std::endl;
    std::cout << "   |       But beware, for the dessert holds many secrets,           |" << std::endl;
    std::cout << "   |       and not all who seek its treasure emerge unscathed...      |" << std::endl;
    std::cout << "   |                                                                 |" << std::endl;
    std::cout << "  |                                              ____________________|_" << std::endl;
    std::cout << "  |  ___________________-------------------------                      `\\" << std::endl;
    std::cout << "  |/`--_                                                                 |" << std::endl;
    std::cout << "  ||[ ]||                                            ___________________/" << std::endl;
    std::cout << "   \\===/___________________--------------------------" << std::endl;
    enterToContinue();
}

// Eingabe der Spielwelt-Größe
int inputWorldSize() {
    int worldWidth = 0;
    while (true) {
        std::cout << "Choose a size for the map (5 - 10): \n" << std::endl;
        std::cout << "Width and Length: " << std::endl;
        std::cin >> worldWidth;
        if (worldWidth >= 5 && worldWidth <= 10) {
            return worldWidth;
        }
        else {
            std::cout << "Size not valid! Try again!\n" << std::endl;
        }
    }
}

// Utility Funktionen
void enterToStart() {
    while (true) {
        std::string start = "";
        std::cout << "Press ENTER, if you are ready to start!\n";
        std::getline(std::cin, start);
        if (start.empty()) {
            clearScreen();
            std::cin.clear();
            break;
        }
    }
}

void enterToContinue() {
    while (true) {
        std::string start = "";
        std::cout << "Press ENTER to continue!\n";
        std::getline(std::cin, start);
        if (start.empty()) {
            clearScreen();
            break;
        }
    }
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    // Assume POSIX
    system("clear");
#endif
}