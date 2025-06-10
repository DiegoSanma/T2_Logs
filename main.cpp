#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <chrono>

#include "utils.h"     // generate_points, build_edge_list
#include "kruskal.h"   // run_kruskal_array, run_kruskal_heap

// ─────── Global switches ───────
constexpr bool RUN_OPT_ARR  = true;   // array + path-compression
constexpr bool RUN_ARR      = true;   // array only
constexpr bool RUN_OPT_HEAP = true;   // heap + path-compression
constexpr bool RUN_HEAP     = true;   // heap only

// Experiment parameters:
constexpr int REPS = 5;
const std::vector<int> NS = {
    // 1<<5,  1<<6,  1<<7,  1<<8,
    // 1<<9, 1<<10, 1<<11, 1<<12
    1<<13
};

int main() {
    using Clock = std::chrono::high_resolution_clock;
    using ms    = std::chrono::milliseconds;

    // Prepare experiments:
    struct Experiment {
        std::string name;
        double (*fn)(int,
                     const std::vector<InfoEntrePuntos>&,
                     bool);
        bool use_path;
    };
    std::vector<Experiment> experiments;
    if (RUN_OPT_ARR)  experiments.push_back({ "ARR_OPT",  run_kruskal_array, true  });
    if (RUN_ARR)      experiments.push_back({ "ARR",      run_kruskal_array, false });
    if (RUN_OPT_HEAP) experiments.push_back({ "HEAP_OPT", run_kruskal_heap,  true  });
    if (RUN_HEAP)     experiments.push_back({ "HEAP",     run_kruskal_heap,  false });

    // Storage for timings:
    std::map<std::string, std::vector<long long>> variant_times;

    auto t_start = Clock::now();

    for (int N : NS) {
        for (int rep = 0; rep < REPS; ++rep) {
            auto points = generate_points(N);
            auto edges  = build_edge_list(points);

            for (auto& exp : experiments) {
                auto v0 = Clock::now();
                double weight = exp.fn(N, edges, exp.use_path);
                (void)weight; // Suppress unused variable warning
                // std::cout << "Experiment: " << exp.name 
                //           << ", N = " << N 
                //           << ", rep = " << rep 
                //           << ", weight = " << weight 
                //           << "\n";
                auto v1 = Clock::now();
                variant_times[exp.name].push_back(
                    std::chrono::duration_cast<ms>(v1 - v0).count()
                );
            }
        }
    }

    auto t_end = Clock::now();
    auto total_elapsed = std::chrono::duration_cast<ms>(t_end - t_start).count();

    std::cout << "Total elapsed time: " << total_elapsed << " ms\n";
    for (auto& [label, times] : variant_times) {
        long long sum = 0;
        for (auto d : times) sum += d;
        double avg = double(sum) / times.size();
        std::cout << label 
                  << ": ran " << times.size() 
                  << " times, avg = " << avg << " ms\n";
    }

    return 0;
}
