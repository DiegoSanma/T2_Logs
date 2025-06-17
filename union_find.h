// union_find.h
#pragma once
#include <vector>

/**
 * @brief Estructura Union-Find / Disjoint Set Union.
 */
class UnionFind {
public:
    /**
     * @brief Construye una estructura Union-Find (Disjoint Set Union).
     *
     * Inicializa un arreglo de tamaño @p n con cada elemento como su propio
     * padre. Si @p use_pc es true, activa path-compression y unión por rango.
     *
     * @param n Número de elementos (índices de 0 a n−1).
     * @param use_pc true para habilitar optimizaciones de path-compression y union-by-rank.
     */
    UnionFind(int n, bool use_pc);

    /**
     * @brief Encuentra la raíz del conjunto que contiene @p x.
     *
     * Recorre los padres hasta la raíz. Si path-compression está activado,
     * hace que todos los nodos en el camino apunten directamente a la raíz,
     * reduciendo el costo amortizado de futuras búsquedas.
     *
     * @param x Elemento cuya raíz se desea encontrar.
     * @return Índice de la raíz del conjunto que contiene @p x.
     */
    int find(int x);

    /**
     * @brief Une los conjuntos cuyas raíces son @p rx y @p ry.
     *
     * Si @p rx y @p ry son diferentes, conecta la raíz de rango menor
     * como hijo de la de rango mayor. Actualiza el rango si es necesario.
     *
     * @param rx Índice de la raíz del primer conjunto.
     * @param ry Índice de la raíz del segundo conjunto.
     */
    void unite(int x, int y);

    long long sumfind = 0; // Suma de las búsquedas realizadas
private:
    std::vector<int> parent;
    std::vector<int> rank_;
    bool path_compression;
};
