#pragma once
#include <vector>
#include "geometry.h"

/** @brief Genera N puntos uniformes en [0,1]². */
std::vector<Punto> generate_points(std::size_t N);

/** @brief Devuelve todas las (N·(N-1)/2) aristas con distancia². */
std::vector<InfoEntrePuntos>
build_edge_list(const std::vector<Punto>& points);
