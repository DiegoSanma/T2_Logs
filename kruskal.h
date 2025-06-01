#ifndef Kruskal_H
#define Kruskal_H

#include "crear_puntos.h"
#include "puntos.h"
#include <vector>

class Kruskal {
private:
    std::vector<Punto> grupos;
    std::vector<InfoEntrePuntos> arbol_minimo;
    int n;


public:
    Kruskal(const std::vector<Punto>& puntos);

    int findArbolMinimo(InfoEntrePuntos* arista);

    std::vector<InfoEntrePuntos> getArbolMinimo();
    
    void Union(Punto* i, Punto* j);

    void setRaiz(Punto* i, Punto* raiz);

    virtual Punto* find(Punto* i);
    
};


#endif