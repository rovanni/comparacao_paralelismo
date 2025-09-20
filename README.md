<a name="inicio"></a>
<a name="english"></a>
**[English Version](#english)** | **[Versão em Português](#português)**

---

<a name="english"></a>
# 🚀 Performance Comparison: Finding Prime Numbers Using Different Parallelism Paradigms in C++

This project compares the performance of four different approaches to find all prime numbers up to **N = 10,000,000**:

1. **Sequential** (no parallelism)  
2. **std::thread** (manual threads + mutex)  
3. **OpenMP** (parallelism via compiler directives)  
4. **Intel TBB** (Threading Building Blocks — `parallel_for` + `concurrent_vector`)

The goal is to measure execution time, calculate **speedup** relative to the sequential version, and highlight the **fastest implementation** — with a **green highlight** in the console!

---

## 📊 Expected Results

The program:

- Executes all 4 versions.
- Measures execution time with high precision (`std::chrono` or `omp_get_wtime`).
- Verifies **correctness** (all versions must find the same number of primes).
- Calculates **speedup** (sequential_time / parallel_time).
- **Ranks** implementations by performance and highlights the **winner** in **GREEN**.
- Displays the first 20 primes as sample output.

---

## 🧰 Requirements

- C++17 or higher compiler (e.g., `g++`, `clang++`, `MSVC`)
- Libraries:
  - OpenMP (usually bundled with compiler)
  - Intel TBB (install via package manager or from [official site](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onetbb.html))

---

## 🛠️ How to Compile and Run

### Linux / macOS

```bash
# Install TBB (if not installed)
sudo apt install libtbb-dev          # Ubuntu/Debian
brew install tbb                     # macOS

# Compile with OpenMP and TBB
g++ -std=c++17 -O3 -fopenmp -ltbb -o primes main.cpp

# Run
./primes
