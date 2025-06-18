#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <chrono>
#include <numeric>              // for std::accumulate

#include "utils.h"    // generate_points, build_edge_list
#include "kruskal.h"  // run_kruskal_array, run_kruskal_heap

// ─────── Global switches ───────
constexpr bool RUN_OPT_ARR  = true;   // array + path-compression
constexpr bool RUN_ARR      = true;   // array only
constexpr bool RUN_OPT_HEAP = true;   // heap + path-compression
constexpr bool RUN_HEAP     = true;   // heap only
constexpr bool LOGS         = false;  // print experiment logs
// ────────────────────────────────

// Experiment parameters:
constexpr int REPS = 5;
const std::vector<int> NS = {
    1<<5,  1<<6,  1<<7,  1<<8,
    1<<9, 1<<10, 1<<11, 1<<12
};

/**
 * @brief Punto de entrada: ejecuta los experimentos de Kruskal.
 *
 * Crea cuatro variantes del algoritmo (array/heap con/sin optimización),
 * para distintos tamaños N y repeticiones REPS. Mide y
 * reporta tiempos promedio por N y totales.
 *
 * Variables globales (flags RUN_* y LOGS) controlan
 * qué variantes se ejecutan y si se imprimen logs intermedios.
 *
 * @return Código de salida (0 si todo OK).
 */
int main() {
    using Clock = std::chrono::high_resolution_clock;
    using ms    = std::chrono::milliseconds;

    struct Experiment {
        std::string name;
        ArbolCoberturaMinimo (*fn)(int,
                                   const std::vector<InfoEntrePuntos>&,
                                   bool);
        bool use_path;
    };

    std::vector<Experiment> experiments;
    if (RUN_ARR)      experiments.push_back({ "ARR",      run_kruskal_array, false });
    if (RUN_HEAP)     experiments.push_back({ "HEAP",     run_kruskal_heap,  false });
    if (RUN_OPT_ARR)  experiments.push_back({ "ARR_OPT",  run_kruskal_array, true  });
    if (RUN_OPT_HEAP) experiments.push_back({ "HEAP_OPT", run_kruskal_heap,  true  });

    // Storage for per-N and overall timings
    std::map<int, std::map<std::string, std::vector<long long>>> times_by_N;
    std::map<int, std::map<std::string, std::vector<long long>>> finds_by_N;
    std::map<std::string, std::vector<long long>> overall_times;

    // Start total timer
    auto t_start = Clock::now();

    for (int N : NS) {
        for (int rep = 0; rep < REPS; ++rep) {
            auto points = generate_points(N);
            auto edges  = build_edge_list(points);
            
            for (auto& exp : experiments) {
                auto v0 = Clock::now();
                ArbolCoberturaMinimo acm = exp.fn(N, edges, exp.use_path);
                if (LOGS) {
                    std::cout << "Experiment: " << exp.name 
                              << ", N = " << N 
                              << ", rep = " << rep 
                              << ", weight = " << acm.peso
                              << ", edges = " << acm.aristas.size() 
                              << ", sumfind = " << acm.sumfind
                              << "\n";
                }
                auto v1 = Clock::now();

                long long dur = std::chrono::duration_cast<ms>(v1 - v0).count();
                times_by_N[N][exp.name].push_back(dur);
                finds_by_N[N][exp.name].push_back(acm.sumfind);
                overall_times[exp.name].push_back(dur);
            }
        }
    }

    // Stop total timer
    auto t_end = Clock::now();
    auto total_elapsed = std::chrono::duration_cast<ms>(t_end - t_start).count();

    // 1) Print overall elapsed time
    std::cout << "Total elapsed time: "
              << total_elapsed << " ms\n\n";

    // 2) Print per-N breakdown
    for (int N : NS) {
        std::cout << "=== Results for N = " << N << " ===\n";
        for (auto& exp : experiments) {
            auto& times = times_by_N[N][exp.name];
            long long sum = std::accumulate(times.begin(), times.end(), 0LL);
            double avg = double(sum) / times.size();
            std::cout << exp.name
                      << ": ran " << times.size()
                      << " times, avg = " << avg << " ms\n";
        }
        std::cout << '\n';
    }
    
    // 4) Print per-N breakdown
    for (int N : NS) {
        std::cout << "=== Finds for N = " << N << " ===\n";
        for (auto& exp : experiments) {
            auto& finds = finds_by_N[N][exp.name][0];
            std::cout << exp.name
            << ": find calls: " << finds << " \n";
        }
        std::cout << '\n';
    }

    // 3) Print overall averages
    std::cout << "=== Overall Averages ===\n";
    for (auto& [label, times] : overall_times) {
        long long sum = std::accumulate(times.begin(), times.end(), 0LL);
        double avg = double(sum) / times.size();
        std::cout << label
                    << ": ran " << times.size()
                    << " times, avg = " << avg << " ms\n";
    }
    std::cout << '\n';
    
    return 0;
}
