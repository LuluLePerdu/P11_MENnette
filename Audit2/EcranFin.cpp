#include "EcranFin.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Couleur.cpp"
#include "Jeu.h"

void setCouleur(int textColor, int bgColor);

void EcranFin::afficher(bool victoire) {
    system("cls");
    if (victoire) {
        setCouleur(VERT_CLAIR, NOIR);
        std::cout << "=== Vous avez gagne ! ===" << std::endl;
    } else {
        setCouleur(ROUGE_CLAIR, NOIR);
        std::cout << "=== Vous avez perdu ! ===" << std::endl;
    }
        setCouleur(BLANC, NOIR);
        std::cout << "Appuyez sur une touche pour retourner au menu..." << std::endl;
        _getch();
}
