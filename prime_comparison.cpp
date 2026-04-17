// ========================================================================
// BASIC INCLUDES AND PARALLELISM LIBRARIES
// ========================================================================
#include <iostream>   // Standard input/output (cout, cin, etc.)
#include <vector>     // Dynamic array (std::vector)
#include <thread>     // C++ standard threads
#include <mutex>      // Mutex for thread synchronization
#include <chrono>     // Time measurement
#include <omp.h>      // OpenMP (directive-based parallelism)
#include <tbb/parallel_for.h>        // Intel TBB: parallel loops
#include <tbb/concurrent_vector.h>   // Intel TBB: thread-safe vector
#include <locale>     // Localization (language, formatting)
#include <iomanip>    // Output formatting (setw, setprecision)
#include <algorithm>  // Generic algorithms (sort, etc.)

// ========================================================================
// HELPER FUNCTIONS FOR CONSOLE COLOR (optional, just for highlight)
// ========================================================================
#ifdef _WIN32
#include <windows.h>
void setConsoleColorGreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}
void resetConsoleColor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
#else
void setConsoleColorGreen() {
    std::cout << "\033[1;32m"; // ANSI bright green
}
void resetConsoleColor() {
    std::cout << "\033[0m"; // Reset color
}
#endif

// ========================================================================
// FUNCTION TO CHECK IF A NUMBER IS PRIME
// (Used by all versions)
// ========================================================================
bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
            return false;
    return true;
}

// ========================================================================
// VERSION 1: SEQUENTIAL (no parallelism)
// ========================================================================
double sequential_version(int N, std::vector<int>& result) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= N; ++i) {
        if (is_prime(i)) {
            result.push_back(i);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

// ========================================================================
// VERSION 2: std::thread (manual parallelism with threads and mutex)
// ========================================================================
double std_thread_version(int N, int num_threads, std::vector<int>& result) {
    std::mutex mtx;
    std::vector<std::thread> threads;
    auto start = std::chrono::high_resolution_clock::now();
    int block = N / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        int start_idx = i * block + 1;
        int end_idx = (i == num_threads - 1) ? N + 1 : start_idx + block;
        threads.emplace_back([start_idx, end_idx, &result, &mtx]() {
            for (int j = start_idx; j < end_idx; ++j) {
                if (is_prime(j)) {
                    std::lock_guard<std::mutex> lock(mtx);
                    result.push_back(j);
                }
            }
        });
    }
    for (auto& t : threads) t.join();
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

// ========================================================================
// VERSION 3: OpenMP (directive-based parallelism)
// ========================================================================
double openmp_version(int N, std::vector<int>& result) {
    double start_time = omp_get_wtime();
#pragma omp parallel
    {
        std::vector<int> local_primes;
#pragma omp for
        for (int i = 1; i <= N; ++i) {
            if (is_prime(i)) {
                local_primes.push_back(i);
            }
        }
#pragma omp critical
        {
            result.insert(result.end(), local_primes.begin(), local_primes.end());
        }
    }
    double end_time = omp_get_wtime();
    return end_time - start_time;
}

// ========================================================================
// VERSION 4: Intel TBB (task-based parallelism)
// ========================================================================
double tbb_version(int N, tbb::concurrent_vector<int>& result) {
    auto start = std::chrono::high_resolution_clock::now();
    tbb::parallel_for(1, N + 1, [&result](int i) {
        if (is_prime(i)) {
            result.push_back(i);
        }
    });
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

// ========================================================================
// MAIN FUNCTION: Runs and compares all versions
// ========================================================================
int main() {
    std::setlocale(LC_ALL, "en_US.UTF-8");
#ifdef _WIN32
    system("chcp 65001 > nul"); // Force UTF-8 on Windows
#endif

    const int N = 10000000;
    const int NUM_THREADS = std::thread::hardware_concurrency();

    std::cout << "=== Performance Comparison: Prime Number Search up to " << N << " ===\n";
    std::cout << "System: " << std::thread::hardware_concurrency() << " logical cores available.\n\n";

    std::vector<int> primes_seq;
    double time_seq = sequential_version(N, primes_seq);
    setConsoleColorGreen();
    std::cout << "[1] Sequential: " << std::fixed << std::setprecision(4) << time_seq << " seconds\n";
    resetConsoleColor();

    std::vector<int> primes_thread;
    double time_thread = std_thread_version(N, NUM_THREADS, primes_thread);
    std::cout << "[2] std::thread (" << NUM_THREADS << " threads): " << std::fixed << std::setprecision(4) << time_thread << " seconds\n";

    std::vector<int> primes_omp;
    double time_omp = openmp_version(N, primes_omp);
    std::cout << "[3] OpenMP: " << std::fixed << std::setprecision(4) << time_omp << " seconds\n";

    tbb::concurrent_vector<int> primes_tbb;
    double time_tbb = tbb_version(N, primes_tbb);
    std::cout << "[4] TBB: " << std::fixed << std::setprecision(4) << time_tbb << " seconds\n";

    // Correctness check
    std::cout << "\n--- [OK] Correctness Check (all should be equal) ---\n";
    std::cout << "Total primes (sequential): " << primes_seq.size() << "\n";
    std::cout << "Total primes (std::thread): " << primes_thread.size() << "\n";
    std::cout << "Total primes (OpenMP): " << primes_omp.size() << "\n";
    std::cout << "Total primes (TBB): " << primes_tbb.size() << "\n";

    // Speedup calculation and comparison table
    double speedup_thread = time_seq / time_thread;
    double speedup_omp = time_seq / time_omp;
    double speedup_tbb = time_seq / time_tbb;

    struct Result {
        std::string name;
        double time;
        double speedup;
    };
    std::vector<Result> results = {
        {"std::thread (" + std::to_string(NUM_THREADS) + " threads)", time_thread, speedup_thread},
        {"OpenMP",      time_omp,    speedup_omp},
        {"TBB",         time_tbb,    speedup_tbb}
    };
    std::sort(results.begin(), results.end(),
        [](const Result& a, const Result& b) {
        return a.time < b.time;
    });

    // Comparison table
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << "TIME AND SPEEDUP COMPARISON TABLE\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << std::left
        << std::setw(20) << "Version"
        << std::setw(15) << "Time (s)"
        << std::setw(15) << "Speedup"
        << "\n" << std::string(80, '-') << "\n";
    std::cout << std::left
        << std::setw(20) << "Sequential"
        << std::setw(15) << std::fixed << std::setprecision(4) << time_seq
        << std::setw(15) << "1.00x" << "\n";
    std::cout << std::left
        << std::setw(20) << ("std::thread (" + std::to_string(NUM_THREADS) + ")")
        << std::setw(15) << std::fixed << std::setprecision(4) << time_thread
        << std::setw(15) << std::fixed << std::setprecision(2) << speedup_thread << "x\n";
    std::cout << std::left
        << std::setw(20) << "OpenMP"
        << std::setw(15) << std::fixed << std::setprecision(4) << time_omp
        << std::setw(15) << std::fixed << std::setprecision(2) << speedup_omp << "x\n";
    std::cout << std::left
        << std::setw(20) << "TBB"
        << std::setw(15) << std::fixed << std::setprecision(4) << time_tbb
        << std::setw(15) << std::fixed << std::setprecision(2) << speedup_tbb << "x\n";
    std::cout << std::string(80, '-') << "\n\n";

    // Highlight the winner
    std::cout << "\n"
        << std::string(80, '-') << "\n";
    std::cout << "[WINNER] FASTEST VERSION: ";
    setConsoleColorGreen();
    std::cout << results[0].name << " (" << std::fixed << std::setprecision(4) << results[0].time << " seconds)\n";
    resetConsoleColor();
    std::cout << "FASTEST: Speedup of " << std::fixed << std::setprecision(2) << results[0].speedup << "x compared to sequential version!\n";
    std::cout << std::string(80, '=') << "\n";

    // Show the first 20 primes found (example)
    std::cout << "\n--- [SEARCH] First 20 primes found (example) ---\n";
    for (int i = 0; i < 20 && i < primes_seq.size(); ++i) {
        std::cout << primes_seq[i] << " ";
    }
    std::cout << "\n\n[OK] Comparison completed successfully!\n";
    return 0;
}
