#pragma once
#include <cstddef>
#include <vector>

/** @brief Punto en el plano 2D. */
struct Punto {
    double x, y;
    Punto(double x_ = 0.0, double y_ = 0.0) : x(x_), y(y_) {}
};

/** @brief Arista entre vértices u,v con peso = distancia². */
struct InfoEntrePuntos {
    std::size_t u, v;   /**< Índices [0..N-1] de los puntos  */
    double    distancia2;
    
    InfoEntrePuntos(std::size_t u_, std::size_t v_, double d2_)
      : u(u_), v(v_), distancia2(d2_) {}
};

/** @brief Arbol covertor minimo y su peso. */
struct ArbolCoberturaMinimo {
    std::vector<std::size_t> aristas; /**< Aristas del árbol (índices de InfoEntrePuntos) */
    double peso;                     /**< Peso total del árbol (suma de distancias²) */
    ArbolCoberturaMinimo(std::vector<std::size_t> aristas_, double peso_)
      : aristas(std::move(aristas_)), peso(peso_) {}
};