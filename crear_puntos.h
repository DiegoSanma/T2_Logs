#ifndef CrearPuntos_H
#define CrearPuntos_H

#include "puntos.h"

class CrearPuntos {
private:
    const char* filePuntos;
    const char* fileDistancias;
    std::vector<Punto>puntos;
    std::priority_queue<InfoEntrePuntos, std::vector<InfoEntrePuntos>, Comparador> heap_distancias;
    std::vector<InfoEntrePuntos> arreglo_distancias;
    int N;
    int X;

public:
    CrearPuntos(const char* filePuntos, const char* fileDistancias, int N);

    const char* getFilePuntos() const;

    const char* getFileDistancias() const;

    int getN() const;

    std::vector<Punto> getPuntos();

    std::priority_queue<InfoEntrePuntos, std::vector<InfoEntrePuntos>, Comparador> getHeapDistancias();

    std::vector<InfoEntrePuntos> getArregloDistancias();

    int CrearPuntosNArreglo();

    int CrearPuntosNHeap();
};


#endif