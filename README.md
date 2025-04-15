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

Menu interativo:

===== MENU DO ALGORITMO DO BANQUEIRO =====
1. Inserir dados
2. Exibir dados inseridos
3. Executar algoritmo do banqueiro
4. Sair
   
---
## 👨‍💻 Integrantes:

1-Nome: Luis Henrique Lima Brandão/20180116645 - Função no Projeto: Implementação, testes, documentação.
2-Nome: Lucas da Silva Barros/20190180372  - Função no Projeto: Implementação, Análise de possíveis melhorias 
no código, testes, documentação.
----

## 🧪 Como compilar e executar

No terminal Linux:

```bash
gcc banker_so.c -o banker
./banker

---
