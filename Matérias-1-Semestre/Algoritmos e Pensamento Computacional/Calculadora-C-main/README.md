# Calculadora Científica em C

Este projeto implementa uma calculadora científica modular e robusta em C. Ela oferece não apenas funções aritméticas e trigonométricas, mas também operações de estatística (com arrays), manipulação de matrizes (2x2), e um histórico de operações com persistência em arquivo.

-----

## O que o programa faz

O usuário interage através de um menu interativo em loop, podendo realizar várias operações até escolher a opção de sair. O programa é robusto contra entradas inválidas (como letras em vez de números), armazena as últimas 20 operações em um histórico (usando struct) e salva esse histórico em um arquivo historico_calculadora.csv ao sair (e o carrega ao iniciar).

-----

## Operações Disponíveis

O programa oferece as seguintes funcionalidades:

**Básicas e Aritmética:**

  * 1 – Soma 
  * 2 – Subtração 
  * 3 – Multiplicação 
  * 4 – Divisão 
  * 5 – Exponenciação (Potência)
  * 6 – Raiz Quadrada
  * 7 – Raiz Cúbica
  * 8 – Fatorial (n!)
  * 22 – MDC (Máximo Divisor Comum)
  * 23 – MMC (Mínimo Múltiplo Comum)

**Trigonometria**

  * 9 – Seno
  * 10 – Cosseno
  * 11 – Tangente
  * 12 – Arco-Seno
  * 13 – Arco-Cosseno
  * 14 – Arco-Tangente
  * 15 – Hipotenusa
  * 16 – Seno Hiperbólico
  * 17 – Cosseno Hiperbólico
  * 18 – Tangente Hiperbólica

**Logaritmos e Exponencial**

  * 19 – Logaritmo na Base 10
  * 20 – Logaritmo Natural (ln)
  * 21 – Euler (e^x)

**Estatística**

  * 24 – Média
  * 25 – Mediana
  * 26 – Desvio Padrão
  * 27 – Valor Máximo
  * 28 – Valor Mínimo

**Matrizes**

  * 29 – Soma de Matrizes
  * 30 – Multiplicação de Matrizes
  * *****
  * 99 – Exibir Hístorico
  * 0 – Sair
  
-----

## Tecnologias e Recursos Utilizados

  * **Linguagem C**: linguagem de programação utilizada.
  * **Structs:** Uso da struct Operacao para gerenciar o histórico de forma organizada.
  * **Arrays e Alocação Dinâmica:** Uso de arrays (double *) com malloc e free para as funções de estatística, permitindo ao usuário definir o tamanho do conjunto de dados.
  * **Persistência (File I/O):** Leitura e escrita de arquivos (fopen, fprintf, fgets, sscanf) para salvar e carregar o histórico em formato .csv.
  * **Bibliotecas padrão**:
      * `stdio.h` para entrada e saída de dados.
      * `math.h` para funções matemáticas avançadas (pow, sqrt, sin, cos, etc.).
      * `stdbool.h` para uso do tipo booleano (true/false).
      * `stdlib.h:` para alocação de memória (malloc, free) e ordenação (qsort para a mediana).
      * `string.h:` para manipulação de strings (strcpy) no histórico.
      * `ctype.h:` para validação de entrada.
  * **Estruturas de controle**: `switch`, `if/else`, `do-while`.

-----

## Como Compilar e Executar

### 1\. Pré-requisitos

  * Ter um compilador C instalado (ex: GCC, MinGW no Windows, ou gec no Linux).
  * Um editor de texto/IDE (VS Code, Code::Blocks, Dev-C++, etc.).

### 2\. Compilação

```bash
gcc calculadora.c -o calculadora -lm
```

  * O parâmetro `-lm` é necessário para linkar a biblioteca matemática (`math.h`).

### 3\. Execução
```
./main.exe
```
-----

## Informações Adicionais

  * Tratamento de Erros: O programa trata entradas inválidas (não quebra se o usuário digitar letras), Divisão por zero, Raiz quadrada de número negativo, Logaritmo de números não positivos, Domínio inválido em asin/acos e limites de Fatorial (calcula apenas até 20!).
  * Unidade de Medida: Todos os cálculos trigonométricos (Seno, Cosseno, etc.) esperam que a entrada esteja em radianos, não em graus.
  * Histórico: O histórico é "circular", ou seja, armazena apenas as últimas 20 operações. Ele é salvo automaticamente no arquivo historico_calculadora.csv ao sair e carregado ao iniciar.
