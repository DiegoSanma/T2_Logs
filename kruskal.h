#pragma once
#include <vector>
#include "geometry.h"

/**
 * @brief Kruskal usando lista ordenada de aristas.
 * @param N               Número de vértices (puntos).
 * @param edges           Lista de aristas (u,v,distancia²).
 * @param use_path_compression
 *                       True para path-compression + union-by-rank.
 */
double run_kruskal_array(int N,
                       const std::vector<InfoEntrePuntos>& edges,
                       bool use_path_compression);

/**
 * @brief Kruskal usando un min-heap de aristas.
 * @param N               Número de vértices (puntos).
 * @param edges           Lista de aristas (u,v,distancia²).
 * @param use_path_compression
 *                       True para path-compression + union-by-rank.
 */
double run_kruskal_heap(int N,
                      const std::vector<InfoEntrePuntos>& edges,
                      bool use_path_compression);
