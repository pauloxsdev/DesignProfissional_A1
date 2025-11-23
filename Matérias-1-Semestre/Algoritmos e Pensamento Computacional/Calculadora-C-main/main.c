// --- SEÇÃO 1: BIBLIOTECAS ---
// Importa as bibliotecas padrão do C necessárias para o programa.
// stdio.h: Funções de entrada/saída (printf, scanf, FILE, fopen, etc.)
// stdlib.h: Funções gerais (malloc, free, qsort, exit, abs)
// math.h: Funções matemáticas (sqrt, pow, sin, log, etc.)
// string.h: Funções de manipulação de strings (strcpy, strcmp)
// stdbool.h: Permite usar o tipo 'bool' (true/false)
// ctype.h: Funções de checagem de caracteres (isspace)

// Inclui a biblioteca de entrada e saída
#include <stdio.h>
#include <stdlib.h> // Para malloc, free, qsort, exit
// Inclui a biblioteca matemática
#include <math.h>   
#include <string.h> // Para strcpy, strcmp
// Inclui a biblioteca booleana
#include <stdbool.h> 
#include <ctype.h>  // Para isspace

// --- SEÇÃO 2: CONSTANTES GLOBAIS E STRUCTS ---
// Define valores fixos que serão usados em todo o programa.
// #define cria "apelidos" para valores, facilitando a manutenção.

// Define a constante PI 
#define PI 3.14159265358979323846
#define HISTORICO_TAMANHO 20 // Define o limite de operações no histórico
#define TAM_MATRIZ 2         // Define o tamanho das matrizes (2x2). Mude para 3 para 3x3.
#define NOME_ARQUIVO "historico_calculadora.csv" // Nome do arquivo de save

// typedef struct: Cria um novo tipo de dado personalizado.
// 'Operacao' vai armazenar todas as informações de um cálculo no histórico.
typedef struct {
    char tipo[30];  // Nome da operação (ex: "Soma")
    double a, b;    // Operandos (b pode ser 0 em ops. de 1 número)
    double resultado; // O resultado do cálculo
    int id;         // ID único da operação
} Operacao;


// --- SEÇÃO 3: FUNÇÕES DE INTERFACE E UTILIDADE (I/O) ---
// Este bloco contém todas as funções que lidam diretamente com o usuário.

// --- FUNÇÃO VOID PARA EXIBIR O MENU ---
// Apenas imprime o menu de opções formatado.
void exibirMenu() {
    printf("\n---------- CALCULADORA MODULAR C ----------\n");
    printf("--- Basicas ---\n");
    printf("| 1. Soma             | 2. Subtracao\n");
    printf("| 3. Multiplicacao    | 4. Divisao\n");
    printf("| 5. Potencia (x^y)   | 6. Raiz Quadrada\n");
    printf("| 7. Raiz Cubica      | 8. Fatorial (n!)\n");
    printf("--- Trigonometria (rad) ---\n");
    printf("| 9. Seno             | 10. Cosseno\n");
    printf("| 11. Tangente        | 12. Arco-Seno\n");
    printf("| 13. Arco-Cosseno    | 14. Arco-Tangente\n");
    printf("| 15. Hipotenusa      | 16. Seno Hiperbolico\n");
    printf("| 17. Cosseno Hiper.  | 18. Tangente Hiper.\n");
    printf("--- Logaritmos ---\n");
    printf("| 19. Log Base 10     | 20. Log Natural (ln)\n");
    printf("| 21. Euler (e^x)\n");
    printf("--- Aritmetica (Inteiros) ---\n");
    printf("| 22. MDC             | 23. MMC\n");
    printf("--- Estatistica (Arrays) ---\n");
    printf("| 24. Media           | 25. Mediana\n");
    printf("| 26. Desvio Padrao   | 27. Maximo\n");
    printf("| 28. Minimo\n");
    printf("--- Matrizes %dx%d ---\n", TAM_MATRIZ, TAM_MATRIZ);
    printf("| 29. Soma Matrizes   | 30. Mult. Matrizes\n");
    printf("--- Sistema ---\n");
    printf("| 99. Exibir Historico\n");
    printf("| 0. Sair (e Salvar Historico)\n");
    printf("--------------------------------------------\n");
}

// Função vital para limpar o buffer de entrada (stdin).
// Evita que um 'Enter' (\n) ou lixo (ex: "abc") de um scanf anterior
// quebre o próximo scanf ou getchar.
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Funções "robustas" para ler números.
// Elas garantem que o usuário SÓ possa digitar um número válido.
// Se o usuário digitar "abc", a função pede novamente em loop (while).
int lerInt(const char* prompt) {
    int valor;
    printf("%s", prompt);
    while (scanf("%d", &valor) != 1) { // '!= 1' significa que a leitura falhou
        printf("Entrada invalida. Digite um numero inteiro: ");
        limparBuffer(); // Limpa o "abc" do buffer
    }
    limparBuffer(); // Limpa o "\n" (Enter) do buffer
    return valor;
}

double lerDouble(const char* prompt) {
    double valor;
    printf("%s", prompt);
    while (scanf("%lf", &valor) != 1) {
        printf("Entrada invalida. Digite um numero (ex: 5 ou 2.5): ");
        limparBuffer();
    }
    limparBuffer(); 
    return valor;
}

// Pausa o programa e espera o usuário pressionar Enter.
void pausar() {
    printf("\nPressione Enter para continuar...\n");
    getchar(); 
}

// Função para ler um conjunto de números (array) do usuário.
// 1. Pergunta o tamanho (n).
// 2. Aloca memória dinamicamente (malloc) para esse tamanho.
// 3. Lê os números um por um usando 'lerDouble'.
// 4. Retorna o ponteiro para o array criado.
double* lerArray(int* n) {
    *n = lerInt("Quantos numeros no conjunto? ");
    if (*n <= 0) {
        printf("ERRO: O conjunto deve ter pelo menos 1 numero.\n");
        *n = 0;
        return NULL;
    }
    
    // Aloca memória do tamanho exato necessário
    double* arr = (double*)malloc(*n * sizeof(double));
    if (arr == NULL) {
        printf("ERRO: Falha ao alocar memoria.\n");
        *n = 0;
        return NULL;
    }

    printf("Digite os %d numeros (separados por Enter):\n", *n);
    for (int i = 0; i < *n; i++) {
        char prompt[30];
        sprintf(prompt, "Numero %d: ", i + 1); // Cria o prompt "Numero 1: ", "Numero 2: "
        arr[i] = lerDouble(prompt);
    }
    return arr; // Retorna o ponteiro para o array na memória
}

// --- SEÇÃO 4: FUNÇÕES DE GERENCIAMENTO DO HISTÓRICO ---
// Este bloco gerencia o array 'historico' e os arquivos.

// Adiciona uma nova operação ao array 'historico'.
// Usa a lógica de "buffer circular":
// O 'indice' é o resto da divisão (modulo, %) do total pelo tamanho.
// Ex: Se o tamanho é 20, a operação 21 (indice 20 % 20 = 0) sobrescreve a 1 (indice 0).
void adicionarAoHistorico(Operacao historico[], int* totalOperacoes, const char* tipo, double a, double b, double resultado) {
    int indice = (*totalOperacoes) % HISTORICO_TAMANHO;

    historico[indice].id = *totalOperacoes + 1;
    strcpy(historico[indice].tipo, tipo); // Copia a string "Soma", "Divisao", etc.
    historico[indice].a = a;
    historico[indice].b = b;
    historico[indice].resultado = resultado;

    (*totalOperacoes)++; // Incrementa o contador total
}

// Imprime o histórico formatado na tela.
// Mostra apenas os últimos 'HISTORICO_TAMANHO' itens.
void exibirHistorico(Operacao historico[], int totalOperacoes) {
    printf("\n--- HISTORICO (Ultimas %d operacoes) ---\n", HISTORICO_TAMANHO);
    
    if (totalOperacoes == 0) {
        printf("Historico vazio.\n");
        return;
    }

    // Calcula por onde começar a imprimir (para mostrar só os últimos 20)
    int inicio = (totalOperacoes > HISTORICO_TAMANHO) ? (totalOperacoes - HISTORICO_TAMANHO) : 0;
    
    for (int i = inicio; i < totalOperacoes; i++) {
        int indice = i % HISTORICO_TAMANHO; // Mapeia o ID para o índice do array
        
        printf("ID: %d | Tipo: %-15s | ", historico[indice].id, historico[indice].tipo);
        
        // Formatação especial para diferentes tipos de operação
        if (strcmp(historico[indice].tipo, "Soma Matriz") == 0 || strcmp(historico[indice].tipo, "Mult. Matriz") == 0) {
            printf("Operacao matricial concluida.");
        } else if (strcmp(historico[indice].tipo, "Media") == 0 || strcmp(historico[indice].tipo, "Mediana") == 0 || strcmp(historico[indice].tipo, "Desvio Padrao") == 0 || strcmp(historico[indice].tipo, "Maximo") == 0 || strcmp(historico[indice].tipo, "Minimo") == 0) {
            printf("N=%.0f, Resultado=%.4f", historico[indice].a, historico[indice].resultado);
        } else if (historico[indice].b == 0 && (strcmp(historico[indice].tipo, "Fatorial") == 0 || strcmp(historico[indice].tipo, "Raiz Quadrada") == 0)) {
            printf("Num: %.2f, Resultado=%.4f", historico[indice].a, historico[indice].resultado);
        } else {
            printf("%.2f, %.2f, Resultado=%.4f", historico[indice].a, historico[indice].b, historico[indice].resultado);
        }
        printf("\n");
    }
    printf("----------------------------------------\n");
}

// (BÔNUS) Salva o conteúdo atual do array 'historico' em um arquivo CSV.
// 'fopen(NOME_ARQUIVO, "w")' abre o arquivo em modo "write" (escrita),
// apagando o que estava lá antes.
void salvarHistorico(Operacao historico[], int totalOperacoes) {
    FILE* f = fopen(NOME_ARQUIVO, "w"); // "w" = write
    if (f == NULL) { // Se falhar ao abrir o arquivo
        printf("AVISO: Nao foi possivel salvar o historico em %s\n", NOME_ARQUIVO);
        return;
    }

    fprintf(f, "ID,Tipo,A,B,Resultado\n"); // Imprime o cabeçalho do CSV
    
    int inicio = (totalOperacoes > HISTORICO_TAMANHO) ? (totalOperacoes - HISTORICO_TAMANHO) : 0;
    for (int i = inicio; i < totalOperacoes; i++) {
        int indice = i % HISTORICO_TAMANHO;
        // Imprime a linha do CSV
        fprintf(f, "%d,%s,%.4f,%.4f,%.4f\n",
                historico[indice].id,
                historico[indice].tipo,
                historico[indice].a,
                historico[indice].b,
                historico[indice].resultado);
    }

    fclose(f); // Fecha o arquivo
    printf("Historico salvo em %s\n", NOME_ARQUIVO);
}

// (BÔNUS) Carrega o histórico do arquivo CSV ao iniciar o programa.
int carregarHistorico(Operacao historico[]) {
    FILE* f = fopen(NOME_ARQUIVO, "r"); // "r" = read
    if (f == NULL) { // Se o arquivo não existir
        printf("AVISO: Arquivo de historico nao encontrado. Comecando do zero.\n");
        return 0; // Retorna 0 operações
    }

    int totalOperacoes = 0;
    char linha[200]; // Buffer para ler cada linha
    
    fgets(linha, sizeof(linha), f); // Lê e descarta a primeira linha (cabeçalho)

    // Lê linha por linha até o fim do arquivo
    while (fgets(linha, sizeof(linha), f)) {
        if (totalOperacoes >= HISTORICO_TAMANHO) {
            break; // Limita ao tamanho do histórico
        }

        // 'sscanf' "lê" os dados da string 'linha' e os coloca nas variáveis
        sscanf(linha, "%d,%29[^,],%lf,%lf,%lf",
               &historico[totalOperacoes].id,
               historico[totalOperacoes].tipo,   // %29[^,] lê uma string até a vírgula
               &historico[totalOperacoes].a,
               &historico[totalOperacoes].b,
               &historico[totalOperacoes].resultado);
        
        totalOperacoes++; // Incrementa o contador local
    }

    fclose(f);
    printf("Historico carregado. Total de %d operacoes recuperadas.\n", totalOperacoes);
    
    // Retorna o ID da última operação, para que o contador principal continue de onde parou
    if (totalOperacoes > 0) {
        return historico[totalOperacoes - 1].id; 
    }
    return 0; // Retorna 0 se o arquivo estava vazio
}

// --- SEÇÃO 5: FUNÇÕES DE CÁLCULO (MATEMÁTICA, ESTATÍSTICA, ARITMÉTICA) ---
// Funções "puras": recebem valores, retornam um resultado.
// Elas não interagem com o usuário (não usam printf/scanf).
// A flag 'int* erro' (um ponteiro) é usada para comunicar falhas ao 'main'.

// 5.1 - Funções Básicas
double soma(double a, double b) { return a + b; }
double subtracao(double a, double b) { return a - b; }
double multiplicacao(double a, double b) { return a * b; }
double divisao(double a, double b, int* erro) {
    if (b == 0) { // Tratamento de erro
        *erro = 1; // Altera o valor da variável 'erro' lá na 'main'
        return 0;
    }
    *erro = 0;
    return a / b;
}

// 5.2 - Funções Avançadas (Trigonometria, Log, etc.)
double exponenciacao(double a, double b) { return pow(a, b); }
double raizQuadrada(double a, int* erro) {
    if (a < 0) { // Tratamento de erro de domínio
        *erro = 1;
        return 0;
    }
    *erro = 0;
    return sqrt(a);
}
double raizCubica(double a) { return cbrt(a); }
double seno(double a_rad) { return sin(a_rad); }
double cosseno(double a_rad) { return cos(a_rad); }
double tangente(double a_rad) { return tan(a_rad); }
double logBase10(double a, int* erro) {
    if (a <= 0) { // Tratamento de erro de domínio
        *erro = 1;
        return 0;
    }
    *erro = 0;
    return log10(a);
}
double logNatural(double a, int* erro) {
    if (a <= 0) { // Tratamento de erro de domínio
        *erro = 1;
        return 0;
    }
    *erro = 0;
    return log(a);
}
double eulerEx(double a) { return exp(a); }
double arcoCosseno(double a, int* erro) {
    if (a < -1 || a > 1) { // Tratamento de erro de domínio
        *erro = 1;
        return 0;
    }
    *erro = 0;
    return acos(a);
}
double arcoSeno(double a, int* erro) {
    if (a < -1 || a > 1) { // Tratamento de erro de domínio
        *erro = 1;
        return 0;
    }
    *erro = 0;
    return asin(a);
}
double arcoTangente(double a) { return atan(a); }
double hipotenusa(double a, double b) { return hypot(a, b); }
double senoHiperbolico(double a) { return sinh(a); }
double cossenoHiperbolico(double a) { return cosh(a); }
double tangenteHiperbolica(double a) { return tanh(a); }

long long fatorial(int n, int* erro) {
    if (n < 0 || n > 20) { // Tratamento de erro (limite do 'long long')
        *erro = 1;
        return 0;
    }
    *erro = 0;
    long long res = 1;
    for (int i = 2; i <= n; i++) {
        res *= i;
    }
    return res;
}

// 5.3 - Funções de Estatística (Arrays)

// Função 'helper' (ajudante) necessária para o qsort (ordenação) da mediana.
// Compara dois números 'a' e 'b' para a ordenação.
int compararDoubles(const void* a, const void* b) {
    double da = *(const double*)a;
    double db = *(const double*)b;
    if (da < db) return -1;
    if (da > db) return 1;
    return 0;
}

double media(double arr[], int n, int* erro) {
    if (n <= 0) { *erro = 1; return 0; }
    *erro = 0;
    double soma = 0;
    for (int i = 0; i < n; i++) {
        soma += arr[i];
    }
    return soma / n;
}

double mediana(double arr[], int n, int* erro) {
    if (n <= 0) { *erro = 1; return 0; }
    *erro = 0;

    // Cria uma CÓPIA do array para não bagunçar o original
    double* temp = (double*)malloc(n * sizeof(double));
    if (temp == NULL) { *erro = 1; return 0; }
    memcpy(temp, arr, n * sizeof(double));

    // Ordena a CÓPIA
    qsort(temp, n, sizeof(double), compararDoubles);

    double mediana;
    if (n % 2 == 0) { // Se for par, pega a média dos dois do meio
        mediana = (temp[n / 2 - 1] + temp[n / 2]) / 2.0;
    } else { // Se for ímpar, pega exatamente o do meio
        mediana = temp[n / 2];
    }

    free(temp); // Libera a memória da cópia
    return mediana;
}

double desvioPadrao(double arr[], int n, int* erro) {
    if (n <= 1) { // Desvio padrão não existe para 1 ou 0 elementos
        *erro = 1; 
        return 0;
    }
    
    int errMedia = 0;
    double m = media(arr, n, &errMedia); // Reutiliza a função de média
    
    double somaQuadrados = 0;
    for (int i = 0; i < n; i++) {
        somaQuadrados += pow(arr[i] - m, 2); // (valor - media)^2
    }
    
    *erro = 0;
    return sqrt(somaQuadrados / (n - 1)); // Raiz da variância (amostral, n-1)
}

double maximo(double arr[], int n, int* erro) {
    if (n <= 0) { *erro = 1; return 0; }
    *erro = 0;
    double max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}

double minimo(double arr[], int n, int* erro) {
    if (n <= 0) { *erro = 1; return 0; }
    *erro = 0;
    double min = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) min = arr[i];
    }
    return min;
}

// 5.4 - Funções de Aritmética (Inteiros)

// Algoritmo de Euclides para Máximo Divisor Comum
int mdc(int a, int b) {
    a = abs(a);
    b = abs(b);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Mínimo Múltiplo Comum (usa o MDC)
int mmc(int a, int b) {
    if (a == 0 || b == 0) return 0;
    return abs(a * b) / mdc(a, b); // Fórmula: (a*b) / MDC(a,b)
}

// --- SEÇÃO 6: FUNÇÕES DE MATRIZ ---
// Funções dedicadas a operações com matrizes (arrays 2D).

// Lê os elementos da matriz, um por um.
void lerMatriz(double matriz[TAM_MATRIZ][TAM_MATRIZ]) {
    for (int i = 0; i < TAM_MATRIZ; i++) {
        for (int j = 0; j < TAM_MATRIZ; j++) {
            char prompt[30];
            sprintf(prompt, "Elemento [%d][%d]: ", i, j);
            matriz[i][j] = lerDouble(prompt);
        }
    }
}

// Imprime a matriz formatada.
void imprimirMatriz(double matriz[TAM_MATRIZ][TAM_MATRIZ]) {
    for (int i = 0; i < TAM_MATRIZ; i++) {
        printf("| ");
        for (int j = 0; j < TAM_MATRIZ; j++) {
            printf("%8.2f ", matriz[i][j]); // %8.2f = 8 espaços, 2 casas decimais
        }
        printf("|\n");
    }
}

// Soma (A[i][j] + B[i][j])
void somarMatrizes(double A[TAM_MATRIZ][TAM_MATRIZ], double B[TAM_MATRIZ][TAM_MATRIZ], double R[TAM_MATRIZ][TAM_MATRIZ]) {
    for (int i = 0; i < TAM_MATRIZ; i++) {
        for (int j = 0; j < TAM_MATRIZ; j++) {
            R[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Multiplicação (requer 3 loops aninhados: i, j, k)
void multiplicarMatrizes(double A[TAM_MATRIZ][TAM_MATRIZ], double B[TAM_MATRIZ][TAM_MATRIZ], double R[TAM_MATRIZ][TAM_MATRIZ]) {
    for (int i = 0; i < TAM_MATRIZ; i++) { // Linha de A
        for (int j = 0; j < TAM_MATRIZ; j++) { // Coluna de B
            R[i][j] = 0; // Inicia o elemento do resultado
            for (int k = 0; k < TAM_MATRIZ; k++) { // Elemento (Coluna de A, Linha de B)
                R[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}


// --- SEÇÃO 7: FUNÇÃO PRINCIPAL (main) ---
// É o "condutor" do programa. Controla o fluxo, o loop e chama as outras funções.
// Função principal, onde a execução do programa começa.
int main() {
    // 7.1 - Inicialização
    // Declaração das variáveis principais.
    Operacao historico[HISTORICO_TAMANHO]; // O array de structs para o histórico
    int totalOperacoes = 0; // Contador total de operações (para IDs)
    int escolha; // Opção do menu
    double num1, num2, resultado; // Variáveis para cálculos double
    int int1, int2; // Variáveis para cálculos int (MDC/MMC/Fatorial)
    int erro = 0; // Flag de erro (0 = OK, 1 = Falha)

    // Tenta carregar o histórico salvo no arquivo CSV.
    totalOperacoes = carregarHistorico(historico);

    // 7.2 - Loop Principal
    // O 'do-while' garante que o menu rode pelo menos uma vez.
    // O loop continua rodando enquanto 'escolha' for diferente de 0.
    do {
        // --- SEÇÃO DO MENU ---
        // Aqui, chamamos a função 'void' para executar a ação de exibir o menu.
        exibirMenu();
        
        // Pede ao usuário que digite sua escolha.
        // Usa a função robusta 'lerInt' para evitar que o programa quebre.
        escolha = lerInt("Escolha uma operacao: ");
        erro = 0; // Reseta a flag de erro a cada nova operação

        // --- SEÇÃO DE CÁLCULO ---
        // 7.3 - Bloco Switch
        // Direciona o programa para a lógica correta baseado na 'escolha'.
        // (Nota: A estrutura mudou. Os comentários originais de "Entrada" e "Cálculo" 
        // agora estão misturados dentro do switch, pois cada 'case' cuida de sua própria entrada.)
        switch (escolha) {
            // Cada case simples:
            // 1. Lê os números necessários (lerDouble/lerInt)
            // 2. Chama a função de cálculo pura (ex: soma(num1, num2))
            // 3. Verifica se houve erro (se aplicável)
            // 4. Imprime o resultado
            // 5. Adiciona ao histórico
            // 6. 'break' para sair do switch
            case 1: // Soma
                num1 = lerDouble("Num 1: ");
                num2 = lerDouble("Num 2: ");
                resultado = soma(num1, num2);
                printf("\nResultado: %.4f\n", resultado);
                adicionarAoHistorico(historico, &totalOperacoes, "Soma", num1, num2, resultado);
                break;
            case 2: // Subtração
                num1 = lerDouble("Num 1: ");
                num2 = lerDouble("Num 2: ");
                resultado = subtracao(num1, num2);
                printf("\nResultado: %.4f\n", resultado);
                adicionarAoHistorico(historico, &totalOperacoes, "Subtracao", num1, num2, resultado);
                break;
            case 3: // Multiplicação
                num1 = lerDouble("Num 1: ");
                num2 = lerDouble("Num 2: ");
                resultado = multiplicacao(num1, num2);
                printf("\nResultado: %.4f\n", resultado);
                adicionarAoHistorico(historico, &totalOperacoes, "Multiplicacao", num1, num2, resultado);
                break;
            case 4: // Divisão
                num1 = lerDouble("Dividendo: ");
                num2 = lerDouble("Divisor: ");
                resultado = divisao(num1, num2, &erro); // Passa o endereço de 'erro'
                if (erro) { // Verifica se a função de cálculo mudou a flag 'erro'
                    printf("ERRO: Divisao por zero!\n");
                } else {
                    printf("\nResultado: %.4f\n", resultado);
                    adicionarAoHistorico(historico, &totalOperacoes, "Divisao", num1, num2, resultado);
                }
                break;
            case 5: // Potência
                num1 = lerDouble("Base: ");
                num2 = lerDouble("Expoente: ");
                resultado = exponenciacao(num1, num2);
                printf("\nResultado: %.4f\n", resultado);
                adicionarAoHistorico(historico, &totalOperacoes, "Potencia", num1, num2, resultado);
                break;
            case 6: // Raiz Quadrada
                num1 = lerDouble("Numero: ");
                resultado = raizQuadrada(num1, &erro);
                if (erro) {
                    printf("ERRO: Nao existe raiz de numero negativo.\n");
                } else {
                    printf("\nResultado: %.4f\n", resultado);
                    adicionarAoHistorico(historico, &totalOperacoes, "Raiz Quadrada", num1, 0, resultado);
                }
                break;
            case 7: // Raiz Cúbica
                num1 = lerDouble("Numero: ");
                resultado = raizCubica(num1);
                printf("\nResultado: %.4f\n", resultado);
                adicionarAoHistorico(historico, &totalOperacoes, "Raiz Cubica", num1, 0, resultado);
                break;
            case 8: // Fatorial
                int1 = lerInt("Numero (n!): ");
                long long res_fat = fatorial(int1, &erro);
                if (erro) {
                    printf("ERRO: Fatorial indefinido (n < 0 ou n > 20).\n");
                } else {
                    resultado = (double)res_fat; // Converte para double para salvar no histórico
                    printf("\nResultado: %lld\n", res_fat); // Imprime como long long
                    adicionarAoHistorico(historico, &totalOperacoes, "Fatorial", (double)int1, 0, resultado);
                }
                break;
            
            case 9: // Seno
                num1 = lerDouble("Angulo (rad): ");
                resultado = seno(num1);
                printf("\nResultado: %.4f\n", resultado);
                adicionarAoHistorico(historico, &totalOperacoes, "Seno", num1, 0, resultado);
                break;
            case 10: // Cosseno
                num1 = lerDouble("Angulo (rad): ");
                resultado = cosseno(num1);
                printf("\nResultado: %.4f\n", resultado);
                adicionarAoHistorico(historico, &totalOperacoes, "Cosseno", num1, 0, resultado);
                break;
            case 11: // Tangente
                num1 = lerDouble("Angulo (rad): ");
                resultado = tangente(num1);
                printf("\nResultado: %.4f\n", resultado);
                adicionarAoHistorico(historico, &totalOperacoes, "Tangente", num1, 0, resultado);
                break;
            case 12: // Arco-Seno
                num1 = lerDouble("Valor [-1, 1]: ");
                resultado = arcoSeno(num1, &erro);
                 if (erro) {
                    printf("ERRO: Dominio invalido.\n");
                } else {
                    printf("\nResultado (rad): %.4f\n", resultado);
                    adicionarAoHistorico(historico, &totalOperacoes, "Arco-Seno", num1, 0, resultado);
                }
                break;
             case 13: // Arco-Cosseno
                num1 = lerDouble("Valor [-1, 1]: ");
                resultado = arcoCosseno(num1, &erro);
                 if (erro) {
                    printf("ERRO: Dominio invalido.\n");
                } else {
                    printf("\nResultado (rad): %.4f\n", resultado);
                    adicionarAoHistorico(historico, &totalOperacoes, "Arco-Cosseno", num1, 0, resultado);
                }
                break;
             case 14: // Arco-Tangente
                num1 = lerDouble("Valor: ");
                resultado = arcoTangente(num1);
                printf("\nResultado (rad): %.4f\n", resultado);
                adicionarAoHistorico(historico, &totalOperacoes, "Arco-Tangente", num1, 0, resultado);
                break;
             case 15: // Hipotenusa
                num1 = lerDouble("Cateto A: ");
                num2 = lerDouble("Cateto B: ");
                resultado = hipotenusa(num1, num2);
                printf("\nResultado: %.4f\n", resultado);
                adicionarAoHistorico(historico, &totalOperacoes, "Hipotenusa", num1, num2, resultado);
                break;
             case 16: // Seno Hiperbólico
                num1 = lerDouble("Numero: ");
                resultado = senoHiperbolico(num1);
                printf("\nResultado: %.4f\n", resultado);
                adicionarAoHistorico(historico, &totalOperacoes, "Seno Hiper", num1, 0, resultado);
                break;
             case 17: // Cosseno Hiperbólico
                num1 = lerDouble("Numero: ");
                resultado = cossenoHiperbolico(num1);
                printf("\nResultado: %.4f\n", resultado);
                adicionarAoHistorico(historico, &totalOperacoes, "Cosseno Hiper", num1, 0, resultado);
                break;
             case 18: // Tangente Hiperbólica
                num1 = lerDouble("Numero: ");
                resultado = tangenteHiperbolica(num1);
                printf("\nResultado: %.4f\n", resultado);
                adicionarAoHistorico(historico, &totalOperacoes, "Tangente Hiper", num1, 0, resultado);
                break;
            case 19: // Log 10
                num1 = lerDouble("Numero (log10): ");
                resultado = logBase10(num1, &erro);
                if (erro) {
                    printf("ERRO: Dominio invalido (n <= 0).\n");
                } else {
                    printf("\nResultado: %.4f\n", resultado);
                    adicionarAoHistorico(historico, &totalOperacoes, "Log10", num1, 0, resultado);
                }
                break;
            case 20: // Log Natural
                num1 = lerDouble("Numero (ln): ");
                resultado = logNatural(num1, &erro);
                if (erro) {
                    printf("ERRO: Dominio invalido (n <= 0).\n");
                } else {
                    printf("\nResultado: %.4f\n", resultado);
                    adicionarAoHistorico(historico, &totalOperacoes, "Log Natural", num1, 0, resultado);
                }
                break;
            case 21: // Euler
                num1 = lerDouble("Expoente (e^x): ");
                resultado = eulerEx(num1);
                printf("\nResultado: %.4f\n", resultado);
                adicionarAoHistorico(historico, &totalOperacoes, "Euler (e^x)", num1, 0, resultado);
                break;
            case 22: // MDC
                int1 = lerInt("Num 1 (inteiro): ");
                int2 = lerInt("Num 2 (inteiro): ");
                resultado = (double)mdc(int1, int2);
                printf("\nResultado: %.0f\n", resultado);
                adicionarAoHistorico(historico, &totalOperacoes, "MDC", (double)int1, (double)int2, resultado);
                break;
            case 23: // MMC
                int1 = lerInt("Num 1 (inteiro): ");
                int2 = lerInt("Num 2 (inteiro): ");
                resultado = (double)mmc(int1, int2);
                printf("\nResultado: %.0f\n", resultado);
                adicionarAoHistorico(historico, &totalOperacoes, "MMC", (double)int1, (double)int2, resultado);
                break;

            // --- Bloco de "Fall-Through" para Estatística ---
            // Os 'cases' 24 a 27 estão "vazios" de propósito.
            // Isso faz com que o código "caia" (fall-through) até o bloco do 'case 28'.
            // Todas essas 5 opções usam o *mesmo* código de preparação (ler o array).
            case 24: 
            case 25: 
            case 26: 
            case 27: 
            case 28: 
            { // As chaves { } criam um escopo para declarar 'n' e 'arr'
                int n = 0;
                double* arr = lerArray(&n); // Chama a função que lê o array
                if (arr == NULL) { // Se a leitura falhar (ex: n=0 ou malloc falhar)
                    break; // Sai do switch
                }
                
                char nomeOp[20];
                
                // Um 'if' interno decide qual cálculo fazer baseado na 'escolha'
                if (escolha == 24) {
                    resultado = media(arr, n, &erro);
                    strcpy(nomeOp, "Media");
                } else if (escolha == 25) {
                    resultado = mediana(arr, n, &erro);
                     strcpy(nomeOp, "Mediana");
                } else if (escolha == 26) {
                    resultado = desvioPadrao(arr, n, &erro);
                     strcpy(nomeOp, "Desvio Padrao");
                } else if (escolha == 27) {
                    resultado = maximo(arr, n, &erro);
                     strcpy(nomeOp, "Maximo");
                } else if (escolha == 28) {
                    resultado = minimo(arr, n, &erro);
                     strcpy(nomeOp, "Minimo");
                }

                if(erro) {
                    printf("ERRO: Nao foi possivel calcular (conjunto invalido).\n");
                } else {
                    printf("\nResultado (%s): %.4f\n", nomeOp, resultado);
                    // Salva 'n' (o tamanho do array) no campo 'a' do histórico
                    adicionarAoHistorico(historico, &totalOperacoes, nomeOp, (double)n, 0, resultado);
                }
                
                free(arr); // Libera a memória alocada por 'malloc'
                break; // FIM do bloco de estatística
            } 
            
            // --- Bloco de "Fall-Through" para Matrizes ---
            // Mesma lógica de 'fall-through' do 'case 29' para o '30'.
            // Ambos precisam ler a Matriz A e a Matriz B.
            case 29: 
            case 30: 
            { 
                double matA[TAM_MATRIZ][TAM_MATRIZ];
                double matB[TAM_MATRIZ][TAM_MATRIZ];
                double matR[TAM_MATRIZ][TAM_MATRIZ];
                
                // Lógica de preparação (leitura)
                printf("--- Digite a Matriz A (%dx%d) ---\n", TAM_MATRIZ, TAM_MATRIZ);
                lerMatriz(matA);
                printf("--- Digite a Matriz B (%dx%d) ---\n", TAM_MATRIZ, TAM_MATRIZ);
                lerMatriz(matB);

                // 'if' interno para decidir qual cálculo fazer
                if (escolha == 29) { // Soma
                    somarMatrizes(matA, matB, matR);
                    printf("\nResultado (A + B):\n");
                    imprimirMatriz(matR);
                    adicionarAoHistorico(historico, &totalOperacoes, "Soma Matriz", 0, 0, 0);
                } else { // Multiplicação (escolha == 30)
                    multiplicarMatrizes(matA, matB, matR);
                    printf("\nResultado (A * B):\n");
                    imprimirMatriz(matR);
                    adicionarAoHistorico(historico, &totalOperacoes, "Mult. Matriz", 0, 0, 0);
                }
                break; // FIM do bloco de matrizes
            } 
            
            // --- Casos do Sistema ---
            case 99: // Exibir Histórico
                exibirHistorico(historico, totalOperacoes);
                break;
            case 0: // Sair
                salvarHistorico(historico, totalOperacoes); // Salva antes de sair
                // (O 'break' aqui é substituído pela condição do 'do-while')
                break;
            default: // Se o usuário digitou um número inválido
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }

        // 7.4 - Seção de Pausa
        // --- SEÇÃO DE PAUSA ---
        if (escolha != 0) { // Não pausa se o usuário escolheu '0' (Sair)
            // Pede ao usuário para pressionar Enter para prosseguir.
            pausar();
        }

    // Fim do laço 'do-while'. A condição para repetir é a 'escolha' ser diferente de 0.
    } while (escolha != 0);

    // 7.5 - Encerramento
    // Exibe uma mensagem de despedida quando o laço termina.
    printf("\nSaindo da calculadora\n");

    // Retorna 0, indicando que o programa foi executado com sucesso.
    return 0;
// Fecha a função