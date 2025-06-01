#include "kruskal_opti.h"
#include <iostream>

KruskalOpti::KruskalOpti(const std::vector<Punto>& puntos) : Kruskal(puntos) {}

Punto* KruskalOpti::find(Punto* i) {
    std::vector<Punto> vuelta;
    if(!i) {
        std::cerr << "Error: El puntero es nulo." << std::endl;
        return nullptr; // Verifica si el puntero es nulo
    }
    while(!(i->iguales(*i->raiz))) { // Mientras no sea su propia raíz
        vuelta.push_back(*i); // Guarda el camino recorrido
        i = i->raiz; // Avanza al padre
    }
    // Actualiza todos los puntos en el camino para que apunten directamente a la raíz
    for (auto& p : vuelta) {
        p.raiz = i; 
    }
    return i->raiz;
}