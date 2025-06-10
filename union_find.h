// union_find.h
#pragma once
#include <vector>

/**
 * @brief Estructura Union-Find / Disjoint Set Union.
 */
class UnionFind {
public:
    /**
     * @param n Número de elementos [0..n-1]
     * @param use_pc Si true, activa path‐compression y unión por rango.
     */
    UnionFind(int n, bool use_pc);

    /** @brief Encuentra la raíz de x. */
    int find(int x);

    /** @brief Une los conjuntos que contienen x y y. */
    void unite(int x, int y);

private:
    std::vector<int> parent;
    std::vector<int> rank_;
    bool path_compression;
};
