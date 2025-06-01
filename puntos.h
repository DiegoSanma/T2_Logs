#ifndef Puntos_H
#define Puntos_H    

struct Punto {
    double x;
    double y;
    Punto* raiz;
    int tamaño;
    int id; // Identificador único para cada punto
    Punto(double x_, double y_, Punto* raiz_ = nullptr, int id_ = -1);
    bool iguales(const Punto& otro) const;
    double distancia(const Punto& otro) const;
};

struct InfoEntrePuntos {
    Punto* p1;
    Punto* p2;
    double distancia;
};

struct Comparador {
    bool operator()(const InfoEntrePuntos& a, const InfoEntrePuntos& b) const;
};

#endif // Puntos_H