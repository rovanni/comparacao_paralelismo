#include <iostream>   // Entrada e saída padrão (cout, cin, etc.)
#include <vector>     // Vetor dinâmico (std::vector)
#include <thread>     // Threads padrão C++
#include <mutex>      // Mutex para sincronização entre threads
#include <chrono>     // Medição de tempo
#include <omp.h>      // OpenMP (paralelismo por diretivas)
#include <tbb/parallel_for.h>        // Intel TBB: laços paralelos
#include <tbb/concurrent_vector.h>   // Intel TBB: vetor thread-safe
#include <locale>     // Localização (idioma, formatação)
#include <iomanip>    // Formatação de saída (setw, setprecision)
#include <algorithm>  // Algoritmos genéricos (sort, etc.)

// Funções auxiliares para colorir o console (opcional, só para destaque)
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
    std::cout << "\033[1;32m"; // ANSI verde brilhante
}
void resetConsoleColor() {
    std::cout << "\033[0m"; // Reseta cor
}
#endif

// Função que verifica se um número 'n' é primo — REUTILIZADA POR TODAS AS VERSÕES
bool is_prime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
            return false;
    return true;
}

// ========================================================================
// VERSÃO 1: SEQUENCIAL (sem paralelismo)
// ========================================================================
double versao_sequencial(int N, std::vector<int>& resultado) {
    auto start = std::chrono::high_resolution_clock::now();
    // Percorre todos os números de 1 até N
    for (int i = 1; i <= N; ++i) {
        if (is_prime(i)) {
            resultado.push_back(i); // Se for primo, adiciona ao vetor
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count(); // Retorna tempo em segundos
}

// ========================================================================
// VERSÃO 2: COM STD::THREAD (múltiplas threads manuais + mutex)
// ========================================================================
double versao_std_thread(int N, int num_threads, std::vector<int>& resultado) {
    std::mutex mtx; // Mutex para proteger o vetor resultado
    std::vector<std::thread> threads; // Vetor de threads
    auto start = std::chrono::high_resolution_clock::now();
    int block = N / num_threads; // Divide o trabalho em blocos
    for (int i = 0; i < num_threads; ++i) {
        int start_idx = i * block + 1;
        int end_idx = (i == num_threads - 1) ? N + 1 : start_idx + block;
        // Cada thread processa um bloco
        threads.emplace_back([start_idx, end_idx, &resultado, &mtx]() {
            for (int j = start_idx; j < end_idx; ++j) {
                if (is_prime(j)) {
                    std::lock_guard<std::mutex> lock(mtx); // Protege acesso ao vetor
                    resultado.push_back(j);
                }
            }
        });
    }
    for (auto& t : threads) t.join(); // Espera todas as threads terminarem
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

// ========================================================================
// VERSÃO 3: COM OpenMP
// ========================================================================
double versao_openmp(int N, std::vector<int>& resultado) {
    double start_time = omp_get_wtime();
    // Cria várias threads automaticamente
#pragma omp parallel
    {
        std::vector<int> local_primes; // Cada thread tem seu vetor local
#pragma omp for
        for (int i = 1; i <= N; ++i) {
            if (is_prime(i)) {
                local_primes.push_back(i);
            }
        }
#pragma omp critical
        {
            resultado.insert(resultado.end(), local_primes.begin(), local_primes.end());
        }
    }
    double end_time = omp_get_wtime();
    return end_time - start_time;
}

// ========================================================================
// VERSÃO 4: COM Intel TBB
// ========================================================================
double versao_tbb(int N, tbb::concurrent_vector<int>& resultado) {
    auto start = std::chrono::high_resolution_clock::now();
    // Executa o laço em paralelo, cada iteração pode rodar em uma thread
    tbb::parallel_for(1, N + 1, [&resultado](int i) {
        if (is_prime(i)) {
            resultado.push_back(i); // concurrent_vector é thread-safe
        }
    });
    auto end = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(end - start).count();
}

// ========================================================================
// FUNÇÃO PRINCIPAL — EXECUTA E COMPARA TODAS AS VERSÕES
// ========================================================================
int main() {
    // Configurações de localidade e console (para acentuação e cor)
    std::setlocale(LC_ALL, "pt_BR.UTF-8");
#ifdef _WIN32
    system("chcp 65001 > nul"); // Força UTF-8 no Windows
#endif

    // Parâmetros do teste
    const int N = 100000000; // Limite superior para busca de primos
    const int NUM_THREADS = std::thread::hardware_concurrency(); // Usa todos os núcleos disponíveis
    //const int NUM_THREADS = 4; // (opcional) Defina manualmente o número de threads

    std::cout << "=== Comparacao de Desempenho: Busca de Numeros Primos ate " << N << " ===\n";
    std::cout << "Sistema: " << std::thread::hardware_concurrency() << " nucleos logicos disponiveis.\n\n";

    // --------------------------------------------------------------------
    // Executa todas as versoes
    // --------------------------------------------------------------------
    std::vector<int> primos_seq;
    double tempo_seq = versao_sequencial(N, primos_seq);
    setConsoleColorGreen();
    std::cout << "[1] Sequencial: " << std::fixed << std::setprecision(4) << tempo_seq << " segundos\n";
    resetConsoleColor();

    std::vector<int> primos_thread;
    double tempo_thread = versao_std_thread(N, NUM_THREADS, primos_thread);
    std::cout << "[2] std::thread (" << NUM_THREADS << " threads): " << std::fixed << std::setprecision(4) << tempo_thread << " segundos\n";

    std::vector<int> primos_omp;
    double tempo_omp = versao_openmp(N, primos_omp);
    std::cout << "[3] OpenMP: " << std::fixed << std::setprecision(4) << tempo_omp << " segundos\n";

    tbb::concurrent_vector<int> primos_tbb;
    double tempo_tbb = versao_tbb(N, primos_tbb);
    std::cout << "[4] TBB: " << std::fixed << std::setprecision(4) << tempo_tbb << " segundos\n";

    // --------------------------------------------------------------------
    // Verificacao de corretude
    // --------------------------------------------------------------------
    std::cout << "\n--- [OK] Verificacao de Corretude (todos devem ser iguais) ---\n";
    std::cout << "Total de primos (sequencial): " << primos_seq.size() << "\n";
    std::cout << "Total de primos (std::thread): " << primos_thread.size() << "\n";
    std::cout << "Total de primos (OpenMP): " << primos_omp.size() << "\n";
    std::cout << "Total de primos (TBB): " << primos_tbb.size() << "\n";

    // --------------------------------------------------------------------
    // Comparacao de desempenho — Speedup + Destaque do VENCEDOR
    // --------------------------------------------------------------------
    double speedup_thread = tempo_seq / tempo_thread;
    double speedup_omp = tempo_seq / tempo_omp;
    double speedup_tbb = tempo_seq / tempo_tbb;

    struct Resultado {
        std::string nome;
        double tempo;
        double speedup;
    };

    std::vector<Resultado> resultados = {
        {"std::thread (" + std::to_string(NUM_THREADS) + " threads)", tempo_thread, speedup_thread},
        {"OpenMP",      tempo_omp,    speedup_omp},
        {"TBB",         tempo_tbb,    speedup_tbb}
    };

    std::sort(resultados.begin(), resultados.end(),
        [](const Resultado& a, const Resultado& b) {
        return a.tempo < b.tempo;
    });

    // Tabela comparativa de tempos e speedups
    std::cout << "\n" << std::string(80, '=') << "\n";
    std::cout << "TABELA DE COMPARACAO DE TEMPO E SPEEDUP\n";
    std::cout << std::string(80, '=') << "\n";
    std::cout << std::left
        << std::setw(20) << "Versao"
        << std::setw(15) << "Tempo (s)"
        << std::setw(15) << "Speedup"
        << "\n" << std::string(80, '-') << "\n";
    std::cout << std::left
        << std::setw(20) << "Sequencial"
        << std::setw(15) << std::fixed << std::setprecision(4) << tempo_seq
        << std::setw(15) << "1.00x" << "\n";
    std::cout << std::left
        << std::setw(20) << ("std::thread (" + std::to_string(NUM_THREADS) + ")")
        << std::setw(15) << std::fixed << std::setprecision(4) << tempo_thread
        << std::setw(15) << std::fixed << std::setprecision(2) << speedup_thread << "x\n";
    std::cout << std::left
        << std::setw(20) << "OpenMP"
        << std::setw(15) << std::fixed << std::setprecision(4) << tempo_omp
        << std::setw(15) << std::fixed << std::setprecision(2) << speedup_omp << "x\n";
    std::cout << std::left
        << std::setw(20) << "TBB"
        << std::setw(15) << std::fixed << std::setprecision(4) << tempo_tbb
        << std::setw(15) << std::fixed << std::setprecision(2) << speedup_tbb << "x\n";
    std::cout << std::string(80, '-') << "\n\n";

    // Destaque para o vencedor
    std::cout << "\n"
        << std::string(80, '-') << "\n";
    std::cout << "[VENCEDOR] VERSAO MAIS RAPIDA: ";
    setConsoleColorGreen();
    std::cout << resultados[0].nome << " (" << std::fixed << std::setprecision(4) << resultados[0].tempo << " segundos)\n";
    resetConsoleColor();
    std::cout << "MAIS [RAPIDO!]: Speedup de " << std::fixed << std::setprecision(2) << resultados[0].speedup << "x em relacao a versao sequencial!\n";
    std::cout << std::string(80, '=') << "\n";

    // --------------------------------------------------------------------
    // Mostrar amostra dos primos
    // --------------------------------------------------------------------
    std::cout << "\n--- [BUSCA] Primeiros 20 primos encontrados (exemplo) ---\n";
    for (int i = 0; i < 20 && i < primos_seq.size(); ++i) {
        std::cout << primos_seq[i] << " ";
    }
    std::cout << "\n\n[OK] Comparacao concluida com sucesso!\n";

    return 0;
}