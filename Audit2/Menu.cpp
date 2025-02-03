#include "Menu.h"
#include <iostream>



void Menu::afficher() {
    system("cls");
    std::cout << "=== Menu Principal ===" << std::endl;
    std::cout << "1. Commencer le jeu" << std::endl;
    std::cout << "2. Quitter" << std::endl;
}

int Menu::choixUtilisateur() {
    char choix;
    std::cin >> choix;
    return choix - '0';
}
