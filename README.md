<a name="inicio"></a>
<a name="english"></a>
**[English Version](#english)** | **[Versão em Português](#português)**

Performance Comparison: Finding Prime Numbers in C++
This project provides a practical analysis of different parallel programming approaches in C++ for the task of finding all prime numbers up to a specified limit N. It compares a baseline sequential implementation against three parallelization techniques: std::thread, OpenMP, and Intel Threading Building Blocks (TBB).

The main goal is to measure and contrast the execution time and speedup achieved by each parallel model, identifying the most efficient solution for this specific computational problem.

🚀 Features
Four Implementations:

Sequential: A single-threaded, straightforward approach.

std::thread: Manual thread management using the C++11 standard library, synchronized with std::mutex.

OpenMP: High-level parallelism using compiler directives (#pragma omp).

Intel TBB: Task-based parallelism using the tbb::parallel_for algorithm.

Performance Benchmarking: Measures the execution time of each version.

Speedup Calculation: Compares the performance of parallel versions against the sequential baseline.

Correctness Verification: Ensures all implementations produce the same number of primes.

Formatted Output: Displays a clear, color-coded summary of the results, highlighting the winner.

🛠️ Environment Setup
To compile and run this project, you will need a C++ compiler (C++11 or newer) and the necessary parallelism libraries. Below are the installation instructions for each dependency.

1. OpenMP
OpenMP is usually included with modern compilers like GCC, Clang, and Visual Studio. You just need to enable it during compilation with the -fopenmp flag (for GCC/Clang) or through project settings in Visual Studio. No separate installation is typically required.

2. Intel Threading Building Blocks (TBB)
You need to install the TBB library on your system. Here are the instructions for different operating systems:

Linux (Debian/Ubuntu)
Use the apt package manager:

sudo apt-get update
sudo apt-get install libtbb-dev

macOS
Use the brew package manager:

brew install tbb

Windows (with Visual Studio using vcpkg)
The recommended way to install TBB on Windows is by using the vcpkg package manager.

a. Install vcpkg:
If you don't have it installed, clone the repository and run the bootstrap script.

git clone [https://github.com/microsoft/vcpkg.git](https://github.com/microsoft/vcpkg.git)
cd vcpkg
.\bootstrap-vcpkg.bat

b. Install the TBB library:
Use vcpkg to install the TBB package for your architecture (e.g., x64).

.\vcpkg install tbb:x64-windows

c. Integrate with Visual Studio:
To make the library automatically available to all your Visual Studio projects, run the integration command.

.\vcpkg integrate install

After this step, Visual Studio will be able to find the TBB headers and libraries automatically.

⚙️ Compilation and Execution
Clone the repository or save the source code as main.cpp.

Open a terminal in the file's directory.

Compile the code using the following command, which links all necessary libraries:

g++ -std=c++17 -O3 main.cpp -o prime_benchmark -fopenmp -ltbb -pthread

-std=c++17: Sets the C++ standard.

-O3: Enables high-level compiler optimizations.

-fopenmp: Enables OpenMP support.

-ltbb: Links the Intel TBB library.

-pthread: Links the POSIX threads library.

Run the executable:

./prime_benchmark

📊 Example Output
The program will execute all four versions and print a summary of the performance results.

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
 [DESEMPENHO] COMPARACAO DE DESEMPENHO — QUAL FOI O MAIS RAPIDO?
================================================================================

Implementacao                 Tempo (s)      Speedup (vs Seq)    Classificacao
--------------------------------------------------------------------------------
TBB                           0.5518         8.18x               [VENCEDOR!] [RAPIDO!]
OpenMP                        0.5723         7.89x               [2o Lugar]
std::thread (16 threads)      0.5891         7.66x               [3o Lugar]

--------------------------------------------------------------------------------
[VENCEDOR] VERSAO MAIS RAPIDA: TBB (0.5518 segundos)
MAIS [RAPIDO!]: Speedup de 8.18x em relacao a versao sequencial!
================================================================================

--- [BUSCA] Primeiros 20 primos encontrados (exemplo) ---
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 

[OK] Comparacao concluida com sucesso!

[⬆️ Back to top](#inicio) 

<a name="português"></a>

Comparativo de Desempenho: Busca de Números Primos em C++
Este projeto oferece uma análise prática de diferentes abordagens de programação paralela em C++ para a tarefa de encontrar todos os números primos até um limite N especificado. Ele compara uma implementação sequencial de referência com três técnicas de paralelização: std::thread, OpenMP e Intel Threading Building Blocks (TBB).

O objetivo principal é medir e contrastar o tempo de execução e o speedup (aceleração) alcançado por cada modelo paralelo, identificando a solução mais eficiente para este problema computacional específico.

🚀 Funcionalidades
Quatro Implementações:

Sequencial: Uma abordagem de thread única e direta.

std::thread: Gerenciamento manual de threads usando a biblioteca padrão do C++11, com sincronização via std::mutex.

OpenMP: Paralelismo de alto nível utilizando diretivas de compilador (#pragma omp).

Intel TBB: Paralelismo baseado em tarefas usando o algoritmo tbb::parallel_for.

Benchmark de Desempenho: Mede o tempo de execução de cada versão.

Cálculo de Speedup: Compara o desempenho das versões paralelas com a implementação sequencial.

Verificação de Corretude: Garante que todas as implementações produzam o mesmo número de primos.

Saída Formatada: Exibe um resumo claro e colorido dos resultados, destacando a versão vencedora.

🛠️ Configuração do Ambiente
Para compilar e executar este projeto, você precisará de um compilador C++ (padrão C++11 ou superior) e das bibliotecas de paralelismo necessárias. Abaixo estão as instruções de instalação para cada dependência.

1. OpenMP
O OpenMP geralmente já vem incluído em compiladores modernos como GCC, Clang e Visual Studio. Basta ativá-lo durante a compilação com a flag -fopenmp (para GCC/Clang) ou através das configurações do projeto no Visual Studio. Nenhuma instalação separada é normalmente necessária.

2. Intel Threading Building Blocks (TBB)
É preciso instalar a biblioteca TBB no seu sistema. Aqui estão as instruções para diferentes sistemas operacionais:

Linux (Debian/Ubuntu)
Use o gerenciador de pacotes apt:

sudo apt-get update
sudo apt-get install libtbb-dev

macOS
Use o gerenciador de pacotes brew:

brew install tbb

Windows (com Visual Studio usando vcpkg)
A maneira recomendada de instalar o TBB no Windows é usando o gerenciador de pacotes vcpkg.

a. Instale o vcpkg:
Caso não o tenha instalado, clone o repositório e execute o script de inicialização.

git clone [https://github.com/microsoft/vcpkg.git](https://github.com/microsoft/vcpkg.git)
cd vcpkg
.\bootstrap-vcpkg.bat

b. Instale a biblioteca TBB:
Use o vcpkg para instalar o pacote TBB para a sua arquitetura (ex: x64).

.\vcpkg install tbb:x64-windows

c. Integre com o Visual Studio:
Para que a biblioteca fique disponível automaticamente para todos os seus projetos do Visual Studio, execute o comando de integração.

.\vcpkg integrate install

Após este passo, o Visual Studio será capaz de encontrar os cabeçalhos e as bibliotecas do TBB automaticamente.

⚙️ Compilação e Execução
Clone o repositório ou salve o código-fonte como main.cpp.

Abra um terminal no diretório do arquivo.

Compile o código com o seguinte comando, que vincula todas as bibliotecas necessárias:

g++ -std=c++17 -O3 main.cpp -o prime_benchmark -fopenmp -ltbb -pthread

-std=c++17: Define o padrão do C++.

-O3: Ativa otimizações de alto nível do compilador.

-fopenmp: Habilita o suporte ao OpenMP.

-ltbb: Vincula a biblioteca Intel TBB.

-pthread: Vincula a biblioteca de threads POSIX.

Execute o programa:

./prime_benchmark

📊 Exemplo de Saída
O programa executará as quatro versões e imprimirá um resumo dos resultados de desempenho.

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
 [DESEMPENHO] COMPARACAO DE DESEMPENHO — QUAL FOI O MAIS RAPIDO?
================================================================================

Implementacao                 Tempo (s)      Speedup (vs Seq)    Classificacao
--------------------------------------------------------------------------------
TBB                           0.5518         8.18x               [VENCEDOR!] [RAPIDO!]
OpenMP                        0.5723         7.89x               [2o Lugar]
std::thread (16 threads)      0.5891         7.66x               [3o Lugar]

--------------------------------------------------------------------------------
[VENCEDOR] VERSAO MAIS RAPIDA: TBB (0.5518 segundos)
MAIS [RAPIDO!]: Speedup de 8.18x em relacao a versao sequencial!
================================================================================

--- [BUSCA] Primeiros 20 primos encontrados (exemplo) ---
2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 

[OK] Comparacao concluida com sucesso!

[⬆️ Back to top](#inicio) | [Voltar ao início](#inicio)
