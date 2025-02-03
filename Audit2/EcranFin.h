#ifndef ECRANFIN_H
#define ECRANFIN_H

#include <iostream>

class EcranFin {
public:
    virtual void afficher(bool victoire);
    virtual ~EcranFin() {}
};

#endif // ECRANFIN_H
