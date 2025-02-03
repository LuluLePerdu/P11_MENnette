#include "Jeu.h"
#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <windows.h> 
#include "Couleur.cpp"

void setCouleur(int texte, int fond) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (fond << 4) | texte);
}

Jeu::Jeu() {
    srand(static_cast<unsigned int>(time(0)));
    initialiserLabyrinthe();
    genererLabyrinthe(1, 1);
    labyrinthe[1][1] = JOUEUR;
    placerObjectif();
}

void Jeu::initialiserLabyrinthe() {
    for (int y = 0; y < HAUTEUR; y++) {
        for (int x = 0; x < LARGEUR; x++) {
            labyrinthe[y][x] = MUR;
        }
    }
}

void Jeu::genererLabyrinthe(int startX, int startY) {
    std::stack<std::pair<int, int>> pile;
    pile.push({startX, startY});
    labyrinthe[startY][startX] = VIDE;

    while (!pile.empty()) {
        auto [x, y] = pile.top();
        std::vector<std::pair<int, int>> voisins;

        if (x > 2 && labyrinthe[y][x - 2] == MUR) voisins.push_back({x - 2, y});
        if (x < LARGEUR - 3 && labyrinthe[y][x + 2] == MUR) voisins.push_back({x + 2, y});
        if (y > 2 && labyrinthe[y - 2][x] == MUR) voisins.push_back({x, y - 2});
        if (y < HAUTEUR - 3 && labyrinthe[y + 2][x] == MUR) voisins.push_back({x, y + 2});

        if (!voisins.empty()) {
            auto [nx, ny] = voisins[rand() % voisins.size()];
            labyrinthe[ny][nx] = VIDE;
            labyrinthe[(ny + y) / 2][(nx + x) / 2] = VIDE;
            pile.push({nx, ny});
        } else {
            pile.pop();
        }
    }

    for (int y = 0; y < HAUTEUR; y++) {
        labyrinthe[y][0] = labyrinthe[y][LARGEUR - 1] = MUR;
    }
    for (int x = 0; x < LARGEUR; x++) {
        labyrinthe[0][x] = labyrinthe[HAUTEUR - 1][x] = MUR;
    }
}

void Jeu::afficherLabyrinthe() {
    std::cout << "\033[?25l";
    std::cout << "\033[H";

    for (int y = 0; y < HAUTEUR; y++) {
        for (int x = 0; x < LARGEUR; x++) {
            std::cout << "\033[" << y + 1 << ";" << x + 1 << "H";

            if (labyrinthe[y][x] == MUR) {
                setCouleur(BLEU_FONCE, GRIS);
            } else if (labyrinthe[y][x] == JOUEUR) {
                setCouleur(JAUNE, NOIR);
            } else if (labyrinthe[y][x] == OBJECTIF) {
                setCouleur(VERT_CLAIR, NOIR);
            } else {
                setCouleur(BLANC, NOIR);
            }

            std::cout << labyrinthe[y][x];
        }
    }

    setCouleur(BLANC, NOIR);
    std::cout << "\033[?25h";
    std::cout.flush();
}

void Jeu::deplacerJoueur() {
    int newX = joueurX + directionX;
    int newY = joueurY + directionY;

    if (labyrinthe[newY][newX] == MUR) {
        jeuEnCours = false;
        return;
    }

    if (labyrinthe[newY][newX] == OBJECTIF) {
        jeuEnCours = false;
        victoire = true;
        return;
    }

    labyrinthe[joueurY][joueurX] = VIDE;
    joueurX = newX;
    joueurY = newY;
    labyrinthe[joueurY][joueurX] = JOUEUR;
}

void Jeu::changerDirection(int dx, int dy) {
    directionX = dx;
    directionY = dy;
}

void Jeu::placerObjectif() {
    int x, y;
    do {
        x = rand() % (LARGEUR - 2) + 1;
        y = rand() % (HAUTEUR - 2) + 1;
    } while (labyrinthe[y][x] != VIDE || (x == 1 && y == 1));
    labyrinthe[y][x] = OBJECTIF;
}

bool Jeu::estEnCours() const {
    return jeuEnCours;
}

bool Jeu::aGagne() const {
    return victoire;
}