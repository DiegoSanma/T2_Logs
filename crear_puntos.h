#ifndef CrearPuntos_H
#define CrearPuntos_H

class CrearPuntos {
private:
    const char* filePuntos;
    const char* fileDistancias;
    int N;
    int X;

public:
    CrearPuntos(const char* filePuntos, const char* fileDistancias, int N,int X);

    const char* getFilePuntos() const;

    const char* getFileDistancias() const;

    int getN() const;

    int getX() const;

    void setX(int x);

    int CrearPuntosNArreglo() const;

    int CrearPuntosNHeap() const;
};

#endif