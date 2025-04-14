#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_PROCESSES 10   // Limite máximo de processos
#define MAX_RESOURCES 10   // Limite máximo de tipos de recursos

// Função: lerInteiro
// Exibe um prompt, lê um número inteiro e, caso a entrada seja inválida,
// exibe "Caractere invalido" e solicita a entrada novamente.
int lerInteiro(const char *prompt) {
    int num;
    while(1) {
        printf("%s", prompt);
        if (scanf("%d", &num) == 1) {
            // Consome qualquer caractere extra na linha
            while(getchar() != '\n');
            return num;
        } else {
            printf("Caractere invalido\n");
            // Limpa o buffer de entrada
            while(getchar() != '\n');
        }
    }
}

// Função: calcular_need
// Calcula a matriz "need" como (max - allocation)
void calcular_need(int n, int m, int max[][MAX_RESOURCES],
                   int alloc[][MAX_RESOURCES], int need[][MAX_RESOURCES]) {
    int i, j;
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

// Função: estadoSeguro
// Verifica se o sistema está em um estado seguro utilizando o Algoritmo do Banqueiro.
// Parâmetros:
//   n       : número de processos
//   m       : número de tipos de recursos
//   avail   : vetor de recursos disponíveis (cópia para simulação)
//   alloc   : matriz de alocações atual
//   need    : matriz de necessidades (calculada previamente)
//   safeSeq : vetor que armazenará a sequência segura, se existir
// Retorna: true se o sistema estiver em estado seguro; false caso contrário.
bool estadoSeguro(int n, int m, int avail[],
                  int alloc[][MAX_RESOURCES], int need[][MAX_RESOURCES],
                  int safeSeq[]) {
    bool finish[MAX_PROCESSES] = { false };
    int work[MAX_RESOURCES];
    int i, j, count = 0;

    // Inicializa work com os recursos disponíveis
    for (j = 0; j < m; j++) {
        work[j] = avail[j];
    }

    while (count < n) {
        bool found = false;
        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                bool podeConcluir = true;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        podeConcluir = false;
                        break;
                    }
                }
                if (podeConcluir) {
                    // Processo pode finalizar; simula a liberação de seus recursos
                    for (j = 0; j < m; j++) {
                        work[j] += alloc[i][j];
                    }
                    safeSeq[count] = i;
                    finish[i] = true;
                    found = true;
                    count++;
                }
            }
        }
        if (!found)
            break;
    }
    return (count == n);
}

// Função para exibir uma matriz com um título (cada linha representa um processo)
void exibirMatriz(int n, int m, int matrix[][MAX_RESOURCES], const char *titulo) {
    int i, j;
    printf("\n%s:\n", titulo);
    for (i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (j = 0; j < m; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Função para exibir um vetor com um título
void exibirVetor(int m, int vetor[], const char *titulo) {
    int j;
    printf("\n%s:\n", titulo);
    for (j = 0; j < m; j++) {
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
        printf("\n===== MENU DO ALGORITMO DO BANQUEIRO =====\n");
        printf("1. Inserir dados\n");
        printf("2. Exibir dados inseridos\n");
        printf("3. Executar algoritmo do banqueiro\n");
        printf("4. Sair\n");
        opcao = lerInteiro("Escolha uma opcao: ");
        
        switch(opcao) {
            case 1:
                n = lerInteiro("\nDigite o numero de processos (max 10): ");
                m = lerInteiro("Digite o numero de tipos de recursos (max 10): ");
                
                // Leitura da matriz de alocações
                printf("\nDigite a matriz de alocacoes (cada linha para um processo):\n");
                for (int i = 0; i < n; i++) {
                    printf("Processo P%d:\n", i);
                    for (int j = 0; j < m; j++) {
                        char prompt[50];
                        sprintf(prompt, "Digite alocacao para recurso R%d: ", j);
                        alloc[i][j] = lerInteiro(prompt);
                    }
                }
                
                // Leitura da matriz de demandas máximas
                printf("\nDigite a matriz de demandas maximas (cada linha para um processo):\n");
                for (int i = 0; i < n; i++) {
                    printf("Processo P%d:\n", i);
                    for (int j = 0; j < m; j++) {
                        char prompt[50];
                        sprintf(prompt, "Digite demanda maxima para recurso R%d: ", j);
                        max[i][j] = lerInteiro(prompt);
                    }
                }
                
                // Leitura do vetor de recursos disponíveis
                printf("\nDigite o vetor de recursos disponiveis:\n");
                for (int j = 0; j < m; j++) {
                    char prompt[50];
                    sprintf(prompt, "Digite recurso disponivel para R%d: ", j);
                    avail[j] = lerInteiro(prompt);
                }
                
                // Calcula a matriz de necessidades
                calcular_need(n, m, max, alloc, need);
                printf("\nDados inseridos com sucesso!\n");
                break;
                
            case 2:
                if (n == 0 || m == 0) {
                    printf("\nNenhum dado inserido. Utilize a opcao 1 primeiro.\n");
                } else {
                    exibirMatriz(n, m, alloc, "Matriz de Alocacoes");
                    exibirMatriz(n, m, max, "Matriz de Demandas Maximas");
                    exibirVetor(m, avail, "Vetor de Recursos Disponiveis");
                    exibirMatriz(n, m, need, "Matriz de Necessidades (Need = Max - Alocacao)");
                }
                break;
                
            case 3:
                if (n == 0 || m == 0) {
                    printf("\nNenhum dado inserido. Utilize a opcao 1 primeiro.\n");
                } else {
                    if (estadoSeguro(n, m, avail, alloc, need, safeSeq)) {
                        printf("\nO sistema esta em um estado seguro.\n");
                        printf("Sequencia segura: ");
                        for (int i = 0; i < n; i++) {
                            printf("P%d ", safeSeq[i]);
                        }
                        printf("\n");
                    } else {
                        printf("\nO sistema NAO esta em um estado seguro.\n");
                    }
                }
                break;
                
            case 4:
                printf("\nEncerrando o programa...\n");
                break;
                
            default:
                printf("\nOpcao invalida. Tente novamente.\n");
        }
        
    } while(opcao != 4);
    
    return 0;
}
