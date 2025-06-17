// kruskal.cpp
#include "kruskal.h"
#include "union_find.h"
#include "geometry.h"
#include <vector>

#include <algorithm>
#include <queue>

/** Comparador para priorizar aristas de menor peso */
struct EdgeCmp {
    bool operator()(InfoEntrePuntos const& a,
                    InfoEntrePuntos const& b) const {
        return a.distancia2 > b.distancia2;
    }
};

ArbolCoberturaMinimo run_kruskal_array(int N,
                         const std::vector<InfoEntrePuntos>& edges,
                         bool use_pc) {
    UnionFind uf(N, use_pc);
    std::vector<std::size_t> aristas(N - 1); // Reservar espacio para N-1 aristas

    // 1) Copia y ordena la lista de aristas
    auto sorted = edges;
    std::sort(sorted.begin(), sorted.end(),
              [](auto const& a, auto const& b){
                  return a.distancia2 < b.distancia2;
              });

    // 2) Toma aristas hasta armar un spanning tree de N-1 aristas
    int taken = 0;
    double total_weight = 0.0;
    for (auto const& e : sorted) {
        int runion_u = uf.find(e.u);
        int runion_v = uf.find(e.v);
        if (runion_u != runion_v) {
            uf.unite(runion_u, runion_v);
            // Guarda la arista en el árbol de cobertura mínimo
            aristas[taken] = &e - &edges[0]; // índice de la arista
            total_weight += e.distancia2;
            if (++taken == N - 1) break;
        }
    }
    // 3) Devuelve el árbol de cobertura mínimo
    //    y su peso total
    ArbolCoberturaMinimo acm(std::move(aristas), total_weight);
    acm.sumfind = uf.sumfind; // Suma de búsquedas realizadas
    return acm;
}

ArbolCoberturaMinimo run_kruskal_heap(int N,
                        const std::vector<InfoEntrePuntos>& edges,
                        bool use_pc) {
    UnionFind uf(N, use_pc);
    std::vector<std::size_t> aristas(N - 1); // Reservar espacio para N-1 aristas

    // 1) Construye un min-heap copiando el vector de aristas
    std::priority_queue<
        InfoEntrePuntos,
        std::vector<InfoEntrePuntos>,
        EdgeCmp
    > pq(
        EdgeCmp{}, 
        std::vector<InfoEntrePuntos>(edges.begin(), edges.end())
    );

    // 2) Extrae la arista mínima y la une si no cierra ciclo
    int taken = 0;
    double total_weight = 0.0;
    while (taken < N - 1 && !pq.empty()) {
        auto e = pq.top(); 
        pq.pop();
        int runion_u = uf.find(e.u);
        int runion_v = uf.find(e.v);
        if (runion_u != runion_v) {
            // Une los conjuntos que contienen u y v
            uf.unite(runion_u, runion_v);
            // Guarda la arista en el árbol de cobertura mínimo
            aristas[taken] = &e - &edges[0]; // índice de la arista
            total_weight += e.distancia2;
            ++taken;
        }
    }
    // 3) Devuelve el árbol de cobertura mínimo
    //    y su peso total
    ArbolCoberturaMinimo acm(std::move(aristas), total_weight);
    acm.sumfind = uf.sumfind; // Suma de búsquedas realizadas
    return acm;
}
