#pragma once
#include <vector>
#include "geometry.h"

/**
 * @brief Genera N puntos aleatorios uniformes en el cuadrado [0,1]².
 *
 * Utiliza un generador mt19937_64 y distribución uniforme en doble.
 *
 * @param N Número de puntos a generar.
 * @return Vector de objetos Punto con coordenadas (x,y).
 */
std::vector<Punto> generate_points(std::size_t N);

/**
 * @brief Construye la lista de todas las aristas con peso = distancia².
 *
 * Para cada par i<j en el vector @p points, calcula (x_i−x_j)²+(y_i−y_j)²
 * y crea un InfoEntrePuntos(i,j,distancia2).
 *
 * @param points Vector de puntos en el plano.
 * @return Vector de todas las aristas posibles (N·(N−1)/2 elementos).
 */
std::vector<InfoEntrePuntos>
build_edge_list(const std::vector<Punto>& points);
