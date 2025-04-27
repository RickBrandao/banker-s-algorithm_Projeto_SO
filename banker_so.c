#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

// Definindo códigos de cor
#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define PURPLE  "\033[1;35m"

// Função: lerInteiroSeguro
int lerInteiroSeguro(const char *prompt, int min, int max) {
    int num;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &num) == 1) {
            if (num >= min && num <= max) {
                while (getchar() != '\n'); // Limpa o buffer de entrada
                return num;
            } else {
                printf(RED "Valor fora do intervalo permitido (%d a %d). Tente novamente.\n" RESET, min, max);
                while(getchar() != '\n'); // Limpa o buffer de entrada
            }
        } else {
            printf(RED "Entrada invalida! Por favor, digite um numero inteiro.\n" RESET);
            while(getchar() != '\n'); // Limpa o buffer de entrada
        }
    }
}

// Função: calcular_need
void calcular_need(int n, int m, int max[][MAX_RESOURCES],
                   int alloc[][MAX_RESOURCES], int need[][MAX_RESOURCES]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

// Função: estadoSeguro
bool estadoSeguro(int n, int m, int avail[] ,
                  int alloc[][MAX_RESOURCES], int need[][MAX_RESOURCES],
                  int safeSeq[]) {
    bool finish[MAX_PROCESSES] = { false };
    int work[MAX_RESOURCES];
    int count = 0;

    for (int j = 0; j < m; j++) {
        work[j] = avail[j];
    }

    while (count < n) {
        bool found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool podeConcluir = true;
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        podeConcluir = false;
                        break;
                    }
                }
                if (podeConcluir) {
                    for (int j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }
                    safeSeq[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) break;
    }
    return (count == n);
}

// Função: exibirMatriz
void exibirMatriz(int n, int m, int matrix[][MAX_RESOURCES], const char *titulo) {
    printf(PURPLE "\n%s:\n" RESET, titulo);
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Função: exibirVetor
void exibirVetor(int m, int vetor[], const char *titulo) {
    printf(PURPLE "\n%s:\n" RESET, titulo);
    for (int j = 0; j < m; j++) {
        printf("%d ", vetor[j]);
    }
    printf("\n");
}

int main() {
    int n = 0, m = 0;
    int alloc[MAX_PROCESSES][MAX_RESOURCES];
    int max[MAX_PROCESSES][MAX_RESOURCES];
    int need[MAX_PROCESSES][MAX_RESOURCES];
    int avail[MAX_RESOURCES];
    int safeSeq[MAX_PROCESSES];
    int opcao;

    do {
        printf(CYAN "\n====================================\n" RESET);
        printf(CYAN "|       ALGORITMO DO BANQUEIRO      |\n" RESET);
        printf(CYAN "|----------------------------------|\n" RESET);
        printf(CYAN "| 1. Inserir dados                 |\n" RESET);
        printf(CYAN "| 2. Exibir dados inseridos        |\n" RESET);
        printf(CYAN "| 3. Executar algoritmo do banqueiro|\n" RESET);
        printf(CYAN "| 4. Sair                          |\n" RESET);
        printf(CYAN "====================================\n" RESET);

        opcao = lerInteiroSeguro(GREEN "Escolha uma opcao: " RESET, 1, 4);

        switch (opcao) {
            case 1:
                // Inserir número de processos
                n = lerInteiroSeguro(YELLOW "\nDigite o numero de processos (max 10): " RESET, 1, MAX_PROCESSES);

                // Inserir número de tipos de recursos
                m = lerInteiroSeguro(YELLOW "Digite o numero de tipos de recursos (max 10): " RESET, 1, MAX_RESOURCES);

                printf(YELLOW "\nDigite a matriz de alocacoes:\n" RESET);
                for (int i = 0; i < n; i++) {
                    printf(GREEN "Processo P%d:\n" RESET, i);
                    for (int j = 0; j < m; j++) {
                        char prompt[50];
                        sprintf(prompt, "  Alocacao para recurso R%d: ", j);
                        alloc[i][j] = lerInteiroSeguro(prompt, 0, 1000);
                    }
                }

                printf(YELLOW "\nDigite a matriz de demandas maximas:\n" RESET);
                for (int i = 0; i < n; i++) {
                    printf(GREEN "Processo P%d:\n" RESET, i);
                    for (int j = 0; j < m; j++) {
                        char prompt[50];
                        sprintf(prompt, "  Demanda maxima para recurso R%d: ", j);
                        max[i][j] = lerInteiroSeguro(prompt, 0, 1000);
                    }
                }

                printf(YELLOW "\nDigite o vetor de recursos disponiveis:\n" RESET);
                for (int j = 0; j < m; j++) {
                    char prompt[50];
                    sprintf(prompt, "  Recursos disponiveis para R%d: ", j);
                    avail[j] = lerInteiroSeguro(prompt, 0, 1000);
                }

                calcular_need(n, m, max, alloc, need);
                printf(GREEN "\n>> Dados inseridos com sucesso!\n" RESET);
                break;

            case 2:
                if (n == 0 || m == 0) {
                    printf(RED "\nNenhum dado inserido. Utilize a opcao 1 primeiro.\n" RESET);
                } else {
                    exibirMatriz(n, m, alloc, "Matriz de Alocacoes");
                    exibirMatriz(n, m, max, "Matriz de Demandas Maximas");
                    exibirVetor(m, avail, "Vetor de Recursos Disponiveis");
                    exibirMatriz(n, m, need, "Matriz de Necessidades (Need = Max - Alocacao)");
                }
                break;

            case 3:
                if (n == 0 || m == 0) {
                    printf(RED "\nNenhum dado inserido. Utilize a opcao 1 primeiro.\n" RESET);
                } else {
                    if (estadoSeguro(n, m, avail, alloc, need, safeSeq)) {
                        printf(GREEN "\nO sistema esta em um estado SEGURO.\n" RESET);
                        printf(GREEN "Sequencia segura encontrada: " RESET);
                        for (int i = 0; i < n; i++) {
                            printf("P%d ", safeSeq[i]);
                        }
                        printf("\n");
                    } else {
                        printf(RED "\nO sistema NAO esta em um estado seguro.\n" RESET);
                    }
                }
                break;

            case 4:
                printf(PURPLE "\nEncerrando o programa...\n" RESET);
                break;
        }
    } while (opcao != 4);

    return 0;
}

