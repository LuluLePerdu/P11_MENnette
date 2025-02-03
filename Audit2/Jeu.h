#ifndef JEU_H
#define JEU_H

#include <chrono>
#include <stack>
#include <vector>
#include <ctime>
#include <cstdlib>

const int LARGEUR = 41;
const int HAUTEUR = 21;
const char MUR = '#';
const char JOUEUR = 'O';
const char VIDE = ' ';
const char OBJECTIF = 'X';

class Jeu {
protected:
    char labyrinthe[HAUTEUR][LARGEUR];
    int joueurX = 1;
    int joueurY = 1;
    bool jeuEnCours = true;
    bool victoire = false;
    int score = 0;
    int directionX = 0;
    int directionY = 0;

    void initialiserLabyrinthe();
    void genererLabyrinthe(int startX, int startY);

public:
    Jeu();
    virtual ~Jeu() = default;

    void afficherLabyrinthe();
    void deplacerJoueur();
    void changerDirection(int dx, int dy);
    void placerObjectif();
    bool estEnCours() const;
    bool aGagne() const;
};

#endif
