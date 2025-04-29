# 💻 Projeto SO – Algoritmo do Banqueiro

Este projeto é uma implementação do **Algoritmo do Banqueiro** em linguagem C, desenvolvido como parte da disciplina de **Sistemas Operacionais**.

O objetivo é simular um sistema de alocação de recursos que verifica se o estado atual é seguro, prevenindo deadlocks.

---

## 📚 Sobre o Algoritmo

O Algoritmo do Banqueiro é um método de alocação segura de recursos que impede **deadlocks** verificando se a solicitação de um processo mantém o sistema em estado seguro.

O sistema:
- Solicita os dados de alocação atual.
- Define a necessidade máxima de cada processo.
- Informa os recursos disponíveis.
- Calcula se existe uma **sequência segura** de execução.

---

## 📷 Interface de linha de comando

![image](https://github.com/user-attachments/assets/2318c45d-a4fb-4515-af53-0b3a045bdad8)


---

📈 Fluxo do Programa (Passo a Passo)

1 - Início da execução:

- O programa inicializa variáveis de controle.

- Exibe o menu interativo para o usuário.

2 - Inserção de dados (Opção 1):

- O usuário informa:

- Número de processos e número de tipos de recursos.

- Matriz de recursos atualmente alocados para cada processo.

- Matriz de recursos máximos que cada processo poderá solicitar.

- Vetor de recursos disponíveis no sistema.

- Esses dados são armazenados nas matrizes e vetores correspondentes.

3 - Exibição de dados (Opção 2):

- O programa exibe na tela:

- A matriz de alocação atual.

- A matriz de necessidade máxima.

- O vetor de recursos disponíveis.

4 - Execução do Algoritmo do Banqueiro (Opção 3):

- O programa calcula a necessidade de recursos (Need) para cada processo:

Need[i][j] = Max[i][j] - Allocation[i][j]

- Em seguida, simula a execução dos processos:

 Procura processos cuja necessidade possa ser satisfeita pelos recursos disponíveis.

 Se encontrar, libera os recursos do processo finalizado para o sistema.

 Repete o processo até todos os processos serem finalizados ou até não ser possível prosseguir.

 Se todos os processos forem executados com sucesso:

 O sistema é considerado em estado seguro.

 Exibe a sequência segura encontrada.

 Caso contrário:

 Informa que o sistema não está em estado seguro (risco de deadlock).

5 - Encerramento (Opção 4):

  O programa finaliza a execução com uma mensagem de saída.


## 🧪 Como compilar e executar

No terminal Linux:

bash
gcc banker_so.c -o banker

Rodar:
./banker


## 👨‍💻 Integrantes:

## Nome: Luis Henrique Lima Brandão/20180116645 - Função no Projeto: Implementação, testes, documentação.
---------------------------------------------------------------------------------------------------------------------
## Nome: Lucas da Silva Barros/20190180372  - Função no Projeto: Implementação, Análise de possíveis melhorias no código, testes, documentação.
----

🚀 Características do Projeto
✅ Implementação modularizada de funções.

✅ Validação segura de entradas do usuário.

✅ Análise automática de estados seguros ou inseguros.

✅ Interface simples e amigável via terminal.

✅ Testado em múltiplos cenários de alocação de recursos.

✅ Documentação e comentários explicativos no código.

📋 Observações Finais
O projeto foi desenvolvido com foco na compreensão do funcionamento interno do algoritmo e na simulação realista de um sistema de gerenciamento de recursos, reforçando a importância da prevenção de deadlocks em ambientes computacionais.


