#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Número máximo de processos e recursos
#define MAX_PROCESSOS 10
#define MAX_RECURSOS 10

// Códigos de cor para formatação do terminal
#define RESET   "\033[0m"
#define CYAN    "\033[1;36m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RED     "\033[1;31m"
#define PURPLE  "\033[1;35m"

// Função para ler um inteiro com segurança, dentro de um intervalo específico
int lerInteiroSeguro(const char *prompt, int min, int max) {
    int num;
    while (1) {
        printf("%s", prompt); // Exibe o prompt para o usuário
        if (scanf("%d", &num) == 1) {  // Verifica se a entrada é um número inteiro
            if (num >= min && num <= max) {   // Verifica se o número está dentro do intervalo
                while (getchar() != '\n'); // Limpa o buffer de entrada
                return num;  // Retorna o número se válido
            } else {
                 // Se o número estiver fora do intervalo
                printf(RED "Valor fora do intervalo permitido (%d a %d). Tente novamente.\n" RESET, min, max);
                while(getchar() != '\n'); // Limpa o buffer de entrada
            }
        } else {
            // Se a entrada não for um número válido
            printf(RED "Entrada inválida! Por favor, digite um número inteiro.\n" RESET);
            while(getchar() != '\n'); // Limpa o buffer de entrada
        }
    }
}

// Função para calcular a matriz de necessidades (Necessidade = Máximo - Alocação)
void calcular_necessidade(int n, int m, int max[][MAX_RECURSOS],
                   int aloc[][MAX_RECURSOS], int necessidade[][MAX_RECURSOS]) {
    // Calcula a diferença entre os recursos máximos e os recursos alocados                    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            // Calcula a necessidade de recursos (Necessidade) para o processo i e o recurso j,
            // Subtraindo os recursos já alocados (aloc) da quantidade máxima necessária (max).
            necessidade[i][j] = max[i][j] - aloc[i][j];
        }
    }
}

// Função para verificar se o sistema está em um estado seguro
bool estadoSeguro(int n, int m, int disponivel[] ,
                  int aloc[][MAX_RECURSOS], int necessidade[][MAX_RECURSOS],
                  int sequenciaSegura[]) {
    bool terminado[MAX_PROCESSOS] = { false }; // Vetor que indica se o processo já terminou
    int trabalho[MAX_RECURSOS];                // Vetor de trabalho que armazena os recursos disponíveis
    int contagem = 0;                          // Contador de processos que foram completados

    for (int j = 0; j < m; j++) {
        trabalho[j] = disponivel[j];
    }
    
    // Enquanto houver processos não terminados, tenta encontrar uma sequência segura
    while (contagem < n) {
        bool encontrado = false;
        for (int i = 0; i < n; i++) {
            if (!terminado[i]) {              // Se o processo não foi finalizado
                bool podeConcluir = true;
                // Verifica se o processo pode terminar
                for (int j = 0; j < m; j++) {
                    if (necessidade[i][j] > trabalho[j]) { // Se o processo precisa de mais recursos do que os disponíveis
                        podeConcluir = false;
                        break;
                    }
                }
                if (podeConcluir) {   // Se o processo pode ser concluído
                     // Libera os recursos alocados para este processo
                    for (int j = 0; j < m; j++) {
                        trabalho[j] += aloc[i][j]; // Libera os recursos do processo
                    }
                    sequenciaSegura[contagem++] = i; // Adiciona o processo à sequência segura
                    terminado[i] = true;     // Marca o processo como terminado
                    encontrado = true;         // Indica que foi encontrado um processo que pode terminar
                }
            }
        }
        if (!encontrado) break;        // Se não encontrar nenhum processo que possa terminar, interrompe
    }
    return (contagem == n);          // Se todos os processos foram completados, retorna true (estado seguro)
}

// Função para exibir uma matriz (usada para mostrar as matrizes de alocação
void exibirMatriz(int n, int m, int matriz[][MAX_RECURSOS], const char *titulo) {
    printf(PURPLE "\n%s:\n" RESET, titulo);  // Exibe o título
    for (int i = 0; i < n; i++) {
        printf("P%d: ", i);                  // Exibe o número do processo 
        for (int j = 0; j < m; j++) {
            printf("%d ", matriz[i][j]);     // Exibe o valor da matriz para cada recurso
        }
        printf("\n");
    }
}

// Função para exibir um vetor (usado para mostrar o vetor de recursos disponíveis)
void exibirVetor(int m, int vetor[], const char *titulo) {
    printf(PURPLE "\n%s:\n" RESET, titulo);   // Exibe o título
    for (int j = 0; j < m; j++) {
        printf("%d ", vetor[j]);              // Exibe o valor de cada recurso no vetor
    }
    printf("\n");
}

int main() {
    int n = 0, m = 0;                           // Número de processos e recursos 
    int aloc[MAX_PROCESSOS][MAX_RECURSOS];    // Matriz de alocação
    int max[MAX_PROCESSOS][MAX_RECURSOS];      // Matriz de demandas máximas
    int necessidade[MAX_PROCESSOS][MAX_RECURSOS];     // Matriz de necessidades
    int disponivel[MAX_RECURSOS];                   // Vetor de recursos disponíveis
    int sequenciaSegura[MAX_PROCESSOS];                 // Sequência segura
    int opcao;                                  // Variável para armazenar a opção escolhida no menu
 
    do {
        // Menu do programa
        printf(CYAN "\n====================================\n" RESET);
        printf(CYAN "|       ALGORITMO DO BANQUEIRO      |\n" RESET);
        printf(CYAN "|----------------------------------|\n" RESET);
        printf(CYAN "| 1. Inserir dados                 |\n" RESET);
        printf(CYAN "| 2. Exibir dados inseridos        |\n" RESET);
        printf(CYAN "| 3. Executar algoritmo do banqueiro|\n" RESET);
        printf(CYAN "| 4. Sair                          |\n" RESET);
        printf(CYAN "====================================\n" RESET);

        // Lê a opção escolhida pelo usuário
        opcao = lerInteiroSeguro(GREEN "Escolha uma opcao: " RESET, 1, 4);

        switch (opcao) {
            case 1:
                // Inserir número de processos
                n = lerInteiroSeguro(YELLOW "\nDigite o numero de processos (max 10): " RESET, 1, MAX_PROCESSOS);

                // Inserir número de tipos de recursos
                m = lerInteiroSeguro(YELLOW "Digite o numero de tipos de recursos (max 10): " RESET, 1, MAX_RECURSOS);
               
                // Inserir a matriz de alocações
                printf(YELLOW "\nDigite a matriz de alocacoes:\n" RESET);
                for (int i = 0; i < n; i++) {
                    printf(GREEN "Processo P%d:\n" RESET, i);
                    for (int j = 0; j < m; j++) {
                        char prompt[50];
                        sprintf(prompt, "  Alocacao para recurso R%d: ", j);
                        aloc[i][j] = lerInteiroSeguro(prompt, 0, 1000); // Lê as alocações de cada recurso
                    }
                }
                // Inserir a matriz de demandas máximas
                printf(YELLOW "\nDigite a matriz de demandas maximas:\n" RESET);
                for (int i = 0; i < n; i++) {
                    printf(GREEN "Processo P%d:\n" RESET, i);
                    for (int j = 0; j < m; j++) {
                        char prompt[50];
                        sprintf(prompt, "  Demanda maxima para recurso R%d: ", j); 
                        max[i][j] = lerInteiroSeguro(prompt, 0, 1000);  // Lê as demandas máximas de cada recurso
                    }
                }
                // Inserir o vetor de recursos disponíveis
                printf(YELLOW "\nDigite o vetor de recursos disponiveis:\n" RESET);
                for (int j = 0; j < m; j++) {
                    char prompt[50];
                    sprintf(prompt, "  Recursos disponiveis para R%d: ", j);
                    disponivel[j] = lerInteiroSeguro(prompt, 0, 1000); // Lê os recursos disponíveis
                }
                // Calcula a matriz de necessidades (Necessidade)
                calcular_necessidade(n, m, max, aloc, necessidade);
                printf(GREEN "\n>> Dados inseridos com sucesso!\n" RESET);
                break;

            case 2:
                if (n == 0 || m == 0) {
                    printf(RED "\nNenhum dado inserido. Utilize a opcao 1 primeiro.\n" RESET);
                } else {
                    // Exibe as matrizes e o vetor inseridos
                    exibirMatriz(n, m, aloc, "Matriz de Alocacoes");
                    exibirMatriz(n, m, max, "Matriz de Demandas Maximas");
                    exibirVetor(m, disponivel, "Vetor de Recursos Disponiveis");
                    exibirMatriz(n, m, necessidade, "Matriz de Necessidades (Need = Max - Alocacao)");
                }
                break;

            case 3:
                if (n == 0 || m == 0) {
                    printf(RED "\nNenhum dado inserido. Utilize a opcao 1 primeiro.\n" RESET);
                } else {
                    if (estadoSeguro(n, m, disponivel, aloc, necessidade, sequenciaSegura)) {
                        printf(GREEN "\nO sistema esta em um estado SEGURO.\n" RESET);
                        printf(GREEN "Sequencia segura encontrada: " RESET);
                        for (int i = 0; i < n; i++) {
                            printf("P%d ", sequenciaSegura[i]);
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
