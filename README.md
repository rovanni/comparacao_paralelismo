# Prime Number Search Performance Comparison in C++ / Comparativo de Desempenho: Busca de Números Primos em C++

---

## 🇺🇸 English Version

This project demonstrates, in a didactic way, how different parallelism techniques in C++ affect the performance of searching for prime numbers up to a limit N. The following approaches are compared:
- **Sequential**
- **std::thread** (manual parallelism)
- **OpenMP** (directive-based parallelism)
- **Intel TBB** (task-based parallelism)

### 🚀 Features
- All versions implemented in the same code
- Automatic measurement of execution time for each approach
- Calculation and display of speedup for each version
- Clear comparison table at the end of execution
- Correctness check (all versions must find the same number of primes)

### 🖥️ How to Run (Windows + Visual Studio)

1. **Install vcpkg (if not already installed):**
```sh
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat
```
2. **Install the TBB library:**
```sh
./vcpkg install tbb:x64-windows
```
3. **Integrate vcpkg with Visual Studio:**
```sh
./vcpkg integrate install
```
4. **Open the `.sln` project in Visual Studio**
   - Make sure the Platform Toolset matches your installation (e.g., v143, v145, v142).
   - Build (Ctrl+Shift+B) and run.

### 🐧 How to Run on Linux (g++/make)

1. **Install dependencies:**
```sh
sudo apt-get update
sudo apt-get install build-essential libtbb-dev libomp-dev
```
2. **Compile:**
```sh
g++ -std=c++17 -O3 prime_comparison.cpp -o prime_benchmark -fopenmp -ltbb -pthread
```
3. **Run:**
```sh
./prime_benchmark
```

### 📊 Example Output
```
=== Performance Comparison: Prime Number Search up to 10000000 ===
System: 16 logical cores available.

[1] Sequential: 4.5123 seconds
[2] std::thread (16 threads): 0.5891 seconds
[3] OpenMP: 0.5723 seconds
[4] TBB: 0.5518 seconds

--- [OK] Correctness Check (all should be equal) ---
Total primes (sequential): 664579
Total primes (std::thread): 664579
Total primes (OpenMP): 664579
Total primes (TBB): 664579

================================================================================
TIME AND SPEEDUP COMPARISON TABLE
================================================================================
Version             Time (s)       Speedup        
--------------------------------------------------------------------------------
Sequential          4.5123         1.00x          
std::thread (16)    0.5891         7.66x          
OpenMP              0.5723         7.89x          
TBB                 0.5518         8.18x          
--------------------------------------------------------------------------------

[WINNER] FASTEST VERSION: TBB (0.5518 seconds)
FASTEST: Speedup of 8.18x compared to sequential version!
================================================================================

--- [SEARCH] First 20 primes found (example) ---
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 

[OK] Comparison completed successfully!
```

### ℹ️ Tips
- If you get a toolset error in Visual Studio, adjust to the installed toolset (right-click project > Properties > General > Platform Toolset).
- If you get a TBB include error, check if vcpkg is integrated and tbb:x64-windows is installed.
- To test with other N values, change the `N` constant at the beginning of `main`.

---

## 🇧🇷 Versão em Português

Este projeto demonstra, de forma didática, como diferentes técnicas de paralelismo em C++ afetam o desempenho na busca de números primos até um limite N. São comparadas as abordagens:
- **Sequencial**
- **std::thread** (paralelismo manual)
- **OpenMP** (paralelismo por diretivas)
- **Intel TBB** (paralelismo por tarefas)

### 🚀 Funcionalidades
- Implementação de todas as versões no mesmo código
- Medição automática do tempo de execução de cada abordagem
- Cálculo e exibição do speedup (aceleração) de cada versão
- Tabela comparativa clara ao final da execução
- Verificação de corretude (todas as versões devem encontrar a mesma quantidade de primos)

### 🖥️ Como Executar (Windows + Visual Studio)

1. **Instale o vcpkg (se ainda não tiver):**
```sh
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat
```
2. **Instale a biblioteca TBB:**
```sh
./vcpkg install tbb:x64-windows
```
3. **Integre o vcpkg ao Visual Studio:**
```sh
./vcpkg integrate install
```
4. **Abra o projeto `.sln` no Visual Studio**
   - Certifique-se de que o Platform Toolset do projeto está compatível (ex: v143, v145, v142).
   - Compile (Ctrl+Shift+B) e execute.

### 🐧 Como Executar no Linux (g++/make)

1. **Instale as dependências:**
```sh
sudo apt-get update
sudo apt-get install build-essential libtbb-dev libomp-dev
```
2. **Compile:**
```sh
g++ -std=c++17 -O3 comparacao_paralelismo.cpp -o prime_benchmark -fopenmp -ltbb -pthread
```
3. **Execute:**
```sh
./prime_benchmark
```

### 📊 Exemplo de Saída
```
=== Comparacao de Desempenho: Busca de Numeros Primos ate 10000000 ===
Sistema: 16 nucleos logicos disponiveis.

[1] Sequencial: 4.5123 segundos
[2] std::thread (16 threads): 0.5891 segundos
[3] OpenMP: 0.5723 segundos
[4] TBB: 0.5518 segundos

--- [OK] Verificacao de Corretude (todos devem ser iguais) ---
Total de primos (sequencial): 664579
Total de primos (std::thread): 664579
Total de primos (OpenMP): 664579
Total de primos (TBB): 664579

================================================================================
TABELA DE COMPARACAO DE TEMPO E SPEEDUP
================================================================================
Versao              Tempo (s)      Speedup        
--------------------------------------------------------------------------------
Sequencial          4.5123         1.00x          
std::thread (16)    0.5891         7.66x          
OpenMP              0.5723         7.89x          
TBB                 0.5518         8.18x          
--------------------------------------------------------------------------------

[VENCEDOR] VERSAO MAIS RAPIDA: TBB (0.5518 segundos)
MAIS [RAPIDO!]: Speedup de 8.18x em relacao a versao sequencial!
================================================================================

--- [BUSCA] Primeiros 20 primos encontrados (exemplo) ---
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 

[OK] Comparacao concluida com sucesso!
```

### ℹ️ Dicas
- Se der erro de toolset no Visual Studio, ajuste para o toolset instalado (clique com o direito no projeto > Propriedades > General > Platform Toolset).
- Se der erro de include do TBB, confira se o vcpkg está integrado e o pacote tbb:x64-windows está instalado.
- Para testar com outros valores de N, altere a constante `N` no início do `main`.

---

## 👨‍🏫 Educational Purpose / Objetivo Didático
This project was developed to facilitate the teaching of parallelism in C++ and to demonstrate, in practice, the impact of different techniques on computational performance.

---

[⬆️ Back to top / Voltar ao topo](#prime-number-search-performance-comparison-in-c-comparativo-de-desempenho-busca-de-números-primos-em-c)
