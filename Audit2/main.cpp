#include "Jeu.h"
#include "Menu.h"
#include "EcranFin.h"
#include <chrono>
#include <thread>
#include <conio.h>
#include <thread>
#include <windows.h>

int main() {
    Jeu jeu;
    Menu menu;
    EcranFin ecranFin;

    while (true) {
        menu.afficher();
        int choix = menu.choixUtilisateur();

        if (choix == 1) {
            jeu = Jeu();

            while (jeu.estEnCours()) {
                if (_kbhit()) {
                    char touche = _getch();

                    switch (touche) {
                        case 'w': jeu.changerDirection(0, -1); break;
                        case 's': jeu.changerDirection(0, 1); break;
                        case 'a': jeu.changerDirection(-1, 0); break;
                        case 'd': jeu.changerDirection(1, 0); break;
                        case 27: return 0;
                    }
                }
                jeu.deplacerJoueur();
                jeu.afficherLabyrinthe();
            }

            ecranFin.afficher(jeu.aGagne());
        } else if (choix == 2) {
            break;
        }
    }

    return 0;
}
