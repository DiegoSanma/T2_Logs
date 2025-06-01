#include "puntos.h"
#include <cmath>


Punto::Punto(double x_, double y_,Punto* raiz_,int id_) : x(x_), y(y_), raiz(raiz_),id(id_), tamaño(1)  {}

double Punto::distancia(const Punto& otro) const {
    return std::sqrt((x - otro.x) * (x - otro.x) + (y - otro.y) * (y - otro.y));
}

bool Punto::iguales(const Punto& otro) const {
    return id == otro.id; // Compara por identificador único
}

bool Comparador::operator()(const InfoEntrePuntos& a, const InfoEntrePuntos& b) const {
        return a.distancia > b.distancia; // menor distancia → más prioritario
}