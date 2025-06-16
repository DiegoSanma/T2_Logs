#pragma once
#include <vector>
#include "geometry.h"

/**
 * @brief Ejecuta Kruskal usando un arreglo de aristas ordenado.
 *
 * Ordena la lista completa de aristas por peso y extrae
 * las N−1 de menor peso, uniendo sus vértices si no
 * forman ciclo (mediante UnionFind).
 *
 * @param N               Número de vértices (puntos).
 * @param edges           Vector con todas las aristas (u,v,distancia²).
 * @param use_path_compression
 *                        true para habilitar path-compression + union-by-rank.
 * @return Un objeto ArbolCoberturaMinimo que contiene los índices
 *         de las aristas elegidas y el peso total.
 */
ArbolCoberturaMinimo run_kruskal_array(int N,
                                       const std::vector<InfoEntrePuntos>& edges,
                                       bool use_path_compression);

/**
 * @brief Ejecuta Kruskal usando un montículo (min-heap) de aristas.
 *
 * Inserta todas las aristas en un priority_queue y extrae la mínima
 * iterativamente, uniendo sus vértices si no forman ciclo.
 *
 * @param N               Número de vértices (puntos).
 * @param edges           Vector con todas las aristas (u,v,distancia²).
 * @param use_path_compression
 *                        true para habilitar path-compression + union-by-rank.
 * @return Un objeto ArbolCoberturaMinimo que contiene los índices
 *         de las aristas elegidas y el peso total.
 */
ArbolCoberturaMinimo run_kruskal_heap(int N,
                                      const std::vector<InfoEntrePuntos>& edges,
                                      bool use_path_compression);
