/**
 * @file crear_puntos.h
 * @brief Declaración de la clase CrearPuntos para generación de puntos
 *        y cálculo de distancias al cuadrado en dos estructuras:
 *        arreglo ordenado y heap de prioridades.  
 * @author Ateuluz
 */
#ifndef CREAR_PUNTOS_H
#define CREAR_PUNTOS_H

#include <cstddef>
#include <vector>
#include <queue>

/**
 * @brief Representa un punto en el plano 2D.
 */
struct Punto {
    double x;  /**< Coordenada X */
    double y;  /**< Coordenada Y */

    /**
     * @brief Construye un punto con coordenadas dadas.
     * @param x_ Coordenada X.
     * @param y_ Coordenada Y.
     */
    Punto(double x_ = 0.0, double y_ = 0.0)
        : x(x_), y(y_) {}
};

/**
 * @brief Contiene información de la arista entre dos puntos.
 */
struct InfoEntrePuntos {
    Punto p1;           /**< Primer punto */
    Punto p2;           /**< Segundo punto */
    double distancia;   /**< Distancia euclidiana al cuadrado */
};

/**
 * @brief Comparador para crear un min-heap basado en InfoEntrePuntos.distancia.
 */
struct Comparador {
    /**
     * @brief Compara dos estructuras InfoEntrePuntos.
     * @param a Primera arista.
     * @param b Segunda arista.
     * @return true si a.distancia > b.distancia.
     */
    bool operator()(const InfoEntrePuntos& a,
                    const InfoEntrePuntos& b) const {
        return a.distancia > b.distancia;
    };
};

/**
 * @brief Genera puntos aleatorios y calcula sus distancias.
 *
 * Esta clase ofrece dos métodos de cálculo:
 *  - CrearPuntosNArreglo: almacena distancias en un arreglo ordenado.
 *  - CrearPuntosNHeap: almacena distancias en un min-heap.
 */
class CrearPuntos {
private:
    int N;                    /**< Número de puntos a generar */
    int X;                    /**< Parámetro auxiliar */

    std::vector<Punto> puntos;                    /**< Puntos generados */
    std::vector<InfoEntrePuntos> arreglo_distancias; /**< Arreglo de distancias */
    std::priority_queue<InfoEntrePuntos,
                        std::vector<InfoEntrePuntos>,
                        Comparador> heap_distancias; /**< Heap de distancias */

public:
    /**
     * @brief Constructor.
     * @param N Número de puntos.
     * @param X Parámetro auxiliar.
     */
    CrearPuntos(int N,
                int X);

    /** @brief Número de puntos a generar. */
    int getN() const;

    /** @brief Parámetro auxiliar X. */
    int getX() const;

    /**
     * @brief Establece un nuevo valor para X.
     * @param x Nuevo valor.
     */
    void setX(int x);

    /**
     * @brief Genera puntos y construye un arreglo ordenado de distancias al cuadrado.
     * @return 0 si éxito, !=0 en caso de error.
     */
    int CrearPuntosNArreglo();

    /**
     * @brief Genera puntos y construye un min-heap de distancias al cuadrado.
     * @return 0 si éxito, !=0 en caso de error.
     */
    int CrearPuntosNHeap();
};

#endif // CREAR_PUNTOS_H
