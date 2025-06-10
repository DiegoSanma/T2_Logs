/**
 * @file crear_puntos.cpp
 * @brief Implementación de la clase CrearPuntos para generación de puntos
 *        y cálculo de distancias al cuadrado en dos estructuras: arreglo ordenado
 *        y heap de prioridades.
 * @author Ateuluz
 */

#include "crear_puntos.h"

#include <cstdint>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include <queue>
#include <algorithm>

#ifndef _WIN32
#  include <sys/mman.h>
#  include <sys/stat.h>
#  include <fcntl.h>
#  include <unistd.h>
#  include <thread>
#endif

/**
 * @brief Calcula la distancia euclidiana al cuadrado entre dos puntos.
 * @param a Primer punto.
 * @param b Segundo punto.
 * @return (x1-x2)^2 + (y1-y2)^2.
 */
inline double distancia2(const Punto& a, const Punto& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return dx*dx + dy*dy;
}

/**
 * @brief Genera N puntos aleatorios en el rango [0,1]×[0,1].
 * @param count Cantidad de puntos a generar.
 * @return Vector de puntos generados.
 */
static std::vector<Punto> generarPuntos(size_t count) {
    std::mt19937_64 rng{ std::random_device{}() };
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    std::vector<Punto> v;
    v.reserve(count);
    for (size_t i = 0; i < count; ++i) {
        v.push_back({ dist(rng), dist(rng) });
    }
    return v;
}

/*---------------------------------------------------*/

/**
 * @brief Constructor de CrearPuntos.
 * @param N Cantidad de puntos a generar.
 * @param X Parámetro auxiliar.
 */
CrearPuntos::CrearPuntos(int N, int X)
    : N(N)
    , X(X)
{}

/**
 * @brief Obtiene el número de puntos a generar.
 * @return Valor de N.
 */
int CrearPuntos::getN() const { return N; }

/**
 * @brief Obtiene el parámetro X.
 * @return Valor de X.
 */
int CrearPuntos::getX() const { return X; }

/**
 * @brief Establece un nuevo valor para X.
 * @param x Nuevo valor de X.
 */
void CrearPuntos::setX(int x) { X = x; }

/**
 * @brief Genera un arreglo ordenado de distancias al cuadrado entre todos los puntos.
 * @return 0 si éxito, !=0 si error.
 */
int CrearPuntos::CrearPuntosNArreglo() {
    if (N <= 0) {
        std::cerr << "Error: N debe ser > 0.\n";
        return 1;
    }

    // Generar puntos y almacenar
    puntos = generarPuntos(static_cast<size_t>(N));

    // Reservar espacio para todas las parejas
    size_t total = static_cast<size_t>(N) * (N - 1) / 2;
    arreglo_distancias.clear();
    arreglo_distancias.reserve(total);

    // Calcular distancias^2
    for (size_t i = 0; i < puntos.size(); ++i) {
        for (size_t j = i + 1; j < puntos.size(); ++j) {
            double d2 = distancia2(puntos[i], puntos[j]);
            arreglo_distancias.push_back({ puntos[i], puntos[j], d2 });
        }
    }

    // Ordenar por distancia creciente
    std::sort(arreglo_distancias.begin(),
              arreglo_distancias.end(),
              [](auto const& a, auto const& b) {
                  return a.distancia < b.distancia;
              });

    return 0;
}

/**
 * @brief Genera un heap de prioridades con las distancias al cuadrado entre puntos.
 * @return 0 si éxito, !=0 si error.
 */
int CrearPuntos::CrearPuntosNHeap() {
    if (N <= 0) {
        std::cerr << "Error: N debe ser > 0.\n";
        return 1;
    }

    // Generar y almacenar puntos
    puntos = generarPuntos(static_cast<size_t>(N));

    // Construir heap de distancias^2
    for (size_t i = 0; i < puntos.size(); ++i) {
        for (size_t j = i + 1; j < puntos.size(); ++j) {
            double d2 = distancia2(puntos[i], puntos[j]);
            heap_distancias.push({ puntos[i], puntos[j], d2 });
        }
    }

    return 0;
}


/* Cambios realizados:
 * - Se reemplazaron índices de bucle de tipo double por size_t para mayor
 *   seguridad y claridad.
 * - Se calcula la distancia al cuadrado (distancia2) evitando llamadas a sqrt.
 * - Se unificó la generación de puntos en la función auxiliar generarPuntos().
 * - Se reforzó el chequeo de errores (N <= 0, apertura de archivos).
 * - Se añadieron comentarios Doxygen en todas las funciones y estructuras.
 * - Firma de autor: Ateuluz
 */