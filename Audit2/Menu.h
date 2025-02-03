#ifndef MENU_H
#define MENU_H

#include <iostream>

class Menu {
public:
    virtual void afficher();
    virtual int choixUtilisateur();
    virtual ~Menu() {}
};

#endif
