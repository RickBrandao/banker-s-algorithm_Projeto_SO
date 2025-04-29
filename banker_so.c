#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_PROCESSOS 10
#define MAX_RECURSOS 10

// Definições de cores para impressão no terminal
#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define PURPLE  "\033[1;35m"

// Função para ler um inteiro de forma segura dentro de um intervalo específico
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
            printf(RED "Entrada inválida! Por favor, digite um número inteiro.\n" RESET);
            while(getchar() != '\n'); // Limpa o buffer de entrada
        }
    }
}

// Função para calcular a matriz de necessidades de cada processo
void calcular_necessidade(int n, int m, int max[][MAX_RECURSOS],
                   int aloc[][MAX_RECURSOS], int necessidade[][MAX_RECURSOS]) {
    for (int i = 0; i < n; i++) { // Para cada processo
        for (int j = 0; j < m; j++) { // Para cada recurso
            necessidade[i][j] = max[i][j] - aloc[i][j]; // Necessidade = Demanda máxima - Alocação atual
        }
    }
}

// Função que verifica se o sistema está em um estado seguro
bool estadoSeguro(int n, int m, int disponivel[] ,
                  int aloc[][MAX_RECURSOS], int necessidade[][MAX_RECURSOS],
                  int sequenciaSegura[], bool terminado[]) {
    int trabalho[MAX_RECURSOS]; // Vetor auxiliar para recursos disponíveis temporariamente
    int contagem = 0; // Contador de processos terminados

    // Inicializa o vetor trabalho com os recursos disponíveis
    for (int j = 0; j < m; j++) {
        trabalho[j] = disponivel[j];
    }

    // Marca todos os processos como não terminados
    for (int i = 0; i < n; i++) {
        terminado[i] = false;
    }
    
    // Enquanto nem todos os processos tiverem terminado
    while (contagem < n) {
        bool encontrado = false; // Indica se um processo foi encontrado na iteração
        for (int i = 0; i < n; i++) {
            if (!terminado[i]) { // Se o processo ainda não terminou
                bool podeConcluir = true;
                for (int j = 0; j < m; j++) {
                    if (necessidade[i][j] > trabalho[j]) { // Se algum recurso necessário for maior do que disponível
                        podeConcluir = false;
                        break;
                    }
                }
                if (podeConcluir) {
                    // Se pode concluir, libera seus recursos para outros processos
                    for (int j = 0; j < m; j++) {
                        trabalho[j] += aloc[i][j]; // Libera os recursos alocados
                    }
                    sequenciaSegura[contagem++] = i; // Adiciona o processo na sequência segura
                    terminado[i] = true; // Marca o processo como terminado
                    encontrado = true;
                }
            }
        }
        if (!encontrado) break; // Se nenhum processo pôde ser concluído, sai do loop
    }
    // Retorna verdadeiro se todos os processos puderem terminar
    return (contagem == n);
}

// Função para exibir uma matriz no console com um título
void exibirMatriz(int n, int m, int matriz[][MAX_RECURSOS], const char *titulo) {
    printf(PURPLE "\n%s:\n" RESET, titulo);
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);
        for (int j = 0; j < m; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }
}

// Função para exibir um vetor no console com um título
void exibirVetor(int m, int vetor[], const char *titulo) {
    printf(PURPLE "\n%s:\n" RESET, titulo);
    for (int j = 0; j < m; j++) {
        printf("%d ", vetor[j]);
    }
    printf("\n");
}

int main() {
    int n = 0, m = 0; // Número de processos e recursos
    int aloc[MAX_PROCESSOS][MAX_RECURSOS]; // Matriz de alocação
    int max[MAX_PROCESSOS][MAX_RECURSOS]; // Matriz de demanda máxima
    int necessidade[MAX_PROCESSOS][MAX_RECURSOS]; // Matriz de necessidade
    int disponivel[MAX_RECURSOS]; // Vetor de recursos disponíveis
    int sequenciaSegura[MAX_PROCESSOS]; // Vetor de sequência segura
    bool terminado[MAX_PROCESSOS]; // Vetor que indica processos terminados
    int opcao; // Menu de opções

    // Loop principal do menu
    do {
        // Exibição do menu principal
        printf(CYAN "\n======================================\n" RESET);
        printf(CYAN "|       ALGORITMO DO BANQUEIRO        |\n" RESET);
        printf(CYAN "|-------------------------------------|\n" RESET);
        printf(CYAN "| 1. Inserir dados                    |\n" RESET);
        printf(CYAN "| 2. Exibir dados inseridos           |\n" RESET);
        printf(CYAN "| 3. Executar algoritmo do banqueiro  |\n" RESET);
        printf(CYAN "| 4. Sair                             |\n" RESET);
        printf(CYAN "======================================\n" RESET);

        // Leitura da opção do usuário
        opcao = lerInteiroSeguro(GREEN "Escolha uma opcao: " RESET, 1, 4);

        switch (opcao) {
            case 1:
                // Inserir dados
                n = lerInteiroSeguro(YELLOW "\nDigite o numero de processos (max 10): " RESET, 1, MAX_PROCESSOS);
                m = lerInteiroSeguro(YELLOW "Digite o numero de tipos de recursos (max 10): " RESET, 1, MAX_RECURSOS);

                // Inserir matriz de alocação
                printf(YELLOW "\nDigite a matriz de alocacoes:\n" RESET);
                for (int i = 0; i < n; i++) {
                    printf(GREEN "Processo P%d:\n" RESET, i);
                    for (int j = 0; j < m; j++) {
                        char prompt[50];
                        sprintf(prompt, "  Alocacao para recurso R%d: ", j);
                        aloc[i][j] = lerInteiroSeguro(prompt, 0, 1000);
                    }
                }

                // Inserir matriz de demanda máxima
                printf(YELLOW "\nDigite a matriz de demandas maximas:\n" RESET);
                for (int i = 0; i < n; i++) {
                    printf(GREEN "Processo P%d:\n" RESET, i);
                    for (int j = 0; j < m; j++) {
                        char prompt[50];
                        sprintf(prompt, "  Demanda maxima para recurso R%d: ", j);
                        max[i][j] = lerInteiroSeguro(prompt, 0, 1000);
                    }
                }

                // Inserir vetor de recursos disponíveis
                printf(YELLOW "\nDigite o vetor de recursos disponiveis:\n" RESET);
                for (int j = 0; j < m; j++) {
                    char prompt[50];
                    sprintf(prompt, "  Recursos disponiveis para R%d: ", j);
                    disponivel[j] = lerInteiroSeguro(prompt, 0, 1000);
                }

                // Calcula a matriz de necessidade (Need = Max - Allocation)
                calcular_necessidade(n, m, max, aloc, necessidade);

                printf(GREEN "\n>> Dados inseridos com sucesso!\n" RESET);
                break;

            case 2:
                // Exibe dados inseridos
                if (n == 0 || m == 0) {
                    printf(RED "\nNenhum dado inserido. Utilize a opcao 1 primeiro.\n" RESET);
                } else {
                    exibirMatriz(n, m, aloc, "Matriz de Alocacoes");
                    exibirMatriz(n, m, max, "Matriz de Demandas Maximas");
                    exibirVetor(m, disponivel, "Vetor de Recursos Disponiveis");
                    exibirMatriz(n, m, necessidade, "Matriz de Necessidades (Need = Max - Alocacao)");
                }
                break;

            case 3:
                // Executa o Algoritmo do Banqueiro
                if (n == 0 || m == 0) {
                    printf(RED "\nNenhum dado inserido. Utilize a opcao 1 primeiro.\n" RESET);
                } else {
                    if (estadoSeguro(n, m, disponivel, aloc, necessidade, sequenciaSegura, terminado)) {
                        printf(GREEN "\nO sistema esta em um estado SEGURO.\n" RESET);
                        printf(GREEN "Sequencia segura encontrada: " RESET);
                        for (int i = 0; i < n; i++) {
                            printf("P%d ", sequenciaSegura[i]);
                        }
                        printf("\n");
                    } else {
                        printf(RED "\nO sistema NAO esta em um estado seguro.\n" RESET);
                        printf(YELLOW "Processos que nao puderam ser completados: " RESET);
                        for (int i = 0; i < n; i++) {
                            if (!terminado[i]) {
                                printf("P%d ", i);
                            }
                        }
                        printf("\n");
                    }
                }
                break;

            case 4:
                // Sai do programa
                printf(PURPLE "\nEncerrando o programa...\n" RESET);
                break;
        }
    } while (opcao != 4);

    return 0;
}
