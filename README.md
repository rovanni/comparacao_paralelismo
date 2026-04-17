# Comparativo de Desempenho: Busca de Números Primos em C++

Este projeto demonstra, de forma didática, como diferentes técnicas de paralelismo em C++ afetam o desempenho na busca de números primos até um limite N. São comparadas as abordagens:
- **Sequencial**
- **std::thread** (paralelismo manual)
- **OpenMP** (paralelismo por diretivas)
- **Intel TBB** (paralelismo por tarefas)

## 🚀 Funcionalidades
- Implementação de todas as versões no mesmo código
- Medição automática do tempo de execução de cada abordagem
- Cálculo e exibição do speedup (aceleração) de cada versão
- Tabela comparativa clara ao final da execução
- Verificação de corretude (todas as versões devem encontrar a mesma quantidade de primos)

---

## 🖥️ Como Executar (Windows + Visual Studio)

### 1. Instale o vcpkg (se ainda não tiver)
Abra o PowerShell e execute:
```sh
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
./bootstrap-vcpkg.bat
```

### 2. Instale a biblioteca TBB
No diretório do vcpkg:
```sh
./vcpkg install tbb:x64-windows
```

### 3. Integre o vcpkg ao Visual Studio
```sh
./vcpkg integrate install
```

### 4. Abra o projeto `.sln` no Visual Studio
- Certifique-se de que o Platform Toolset do projeto está compatível (ex: v143, v145, v142).
- Compile normalmente (Ctrl+Shift+B).

### 5. Execute o programa
- O console mostrará o tempo de execução de cada versão e uma tabela comparativa.

---

## 🐧 Como Executar no Linux (g++/make)

1. Instale as dependências:
```sh
sudo apt-get update
sudo apt-get install build-essential libtbb-dev libomp-dev
```

2. Compile:
```sh
g++ -std=c++17 -O3 comparacao_paralelismo.cpp -o prime_benchmark -fopenmp -ltbb -pthread
```

3. Execute:
```sh
./prime_benchmark
```

---

## 📊 Exemplo de Saída
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

---

## ℹ️ Dicas e Solução de Problemas
- Se der erro de toolset no Visual Studio, ajuste para o toolset instalado (clique com o direito no projeto > Propriedades > General > Platform Toolset).
- Se der erro de include do TBB, confira se o vcpkg está integrado e o pacote tbb:x64-windows está instalado.
- Para testar com outros valores de N, altere a constante `N` no início do main.

---

## 👨‍🏫 Objetivo Didático
Este projeto foi desenvolvido para facilitar o ensino de paralelismo em C++ e demonstrar, na prática, o impacto das diferentes técnicas no desempenho computacional.

---

[⬆️ Voltar ao topo](#comparativo-de-desempenho-busca-de-números-primos-em-c)
