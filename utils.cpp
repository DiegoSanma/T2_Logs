// utils.cpp
#include "utils.h"
#include "geometry.h"

#include <random>

std::vector<Punto> generate_points(std::size_t N) {
    std::mt19937_64 rng{std::random_device{}()};
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    std::vector<Punto> pts;
    pts.reserve(N);
    for (std::size_t i = 0; i < N; ++i)
        pts.emplace_back(dist(rng), dist(rng));
    return pts;
}

std::vector<InfoEntrePuntos> build_edge_list(const std::vector<Punto>& pts) {
    std::size_t N = pts.size();
    std::vector<InfoEntrePuntos> edges;
    edges.reserve(N * (N - 1) / 2);

    for (std::size_t i = 0; i < N; ++i) {
        for (std::size_t j = i + 1; j < N; ++j) {
            double dx = pts[i].x - pts[j].x;
            double dy = pts[i].y - pts[j].y;
            edges.emplace_back( i, j, dx*dx + dy*dy );
        }
    }
    return edges;
}
