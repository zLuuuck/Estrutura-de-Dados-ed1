#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constantes.h"
#include "ingresso.h"
#include "cliente.h"
#include "fila.h"
#include "pilha.h"
#include "main.h"

// Definição das variáveis globais
FilaClientes filaInicial;
PilhaIngressos pilhas[NUM_FILMES];
FilaClientes filasExibicao[NUM_FILMES];

const char *nomesFilmes[NUM_FILMES] = {
    "Avatar 3",
    "Vingadores: Guerra Infinita",
    "Interestelar"
};

const Ingresso ingressosExemplo[NUM_FILMES] = {
    {"Avatar 3", 1, "19:00", 32.50},
    {"Vingadores: Guerra Infinita", 2, "20:30", 35.00},
    {"Interestelar", 3, "21:00", 30.00}
};

// Implementações das funções auxiliares
void preencherFilaClientes() {
    Cliente clientesExemplo[] = {
        {"João Silva", 25, {"", 0, "", 0}},
        {"Maria Oliveira", 32, {"", 0, "", 0}},
        {"Pedro Santos", 19, {"", 0, "", 0}},
        {"Ana Costa", 28, {"", 0, "", 0}},
        {"Lucas Lima", 41, {"", 0, "", 0}},
        {"Fernanda Souza", 22, {"", 0, "", 0}}
    };
    int num = sizeof(clientesExemplo) / sizeof(Cliente);
    
    inicializarFila(&filaInicial);
    for (int i = 0; i < num; i++) {
        if (!enfileirar(&filaInicial, clientesExemplo[i])) {
            printf("Erro ao enfileirar cliente %s\n", clientesExemplo[i].nome);
            break;
        }
    }
    printf("Fila inicial preenchida com %d clientes.\n", num);
}

void preencherPilhasIngressos() {
    int qtdPorPilha = 5;
    for (int i = 0; i < NUM_FILMES; i++) {
        inicializarPilha(&pilhas[i]);
        for (int j = 0; j < qtdPorPilha; j++) {
            Ingresso ing = ingressosExemplo[i];
            if (!push(&pilhas[i], ing)) {
                printf("Erro ao empilhar ingresso do filme %s\n", nomesFilmes[i]);
                break;
            }
        }
        printf("Pilha do filme %s preenchida com %d ingressos.\n", nomesFilmes[i], qtdPorPilha);
    }
}

void venderIngressos(int indiceFilme) {
    if (filaVazia(&filaInicial)) {
        printf("Não há clientes na fila inicial para vender ingressos.\n");
        return;
    }
    
    if (pilhaVazia(&pilhas[indiceFilme])) {
        printf("Não há ingressos disponíveis para o filme %s.\n", nomesFilmes[indiceFilme]);
        return;
    }
    
    printf("\n=== VENDENDO INGRESSOS PARA %s ===\n", nomesFilmes[indiceFilme]);
    int vendidos = 0;
    
    while (!filaVazia(&filaInicial) && !pilhaVazia(&pilhas[indiceFilme])) {
        Ingresso ing = pop(&pilhas[indiceFilme]);
        Cliente cliente = desenfileirar(&filaInicial);
        cliente.ingresso = ing;
        
        printf("Cliente: %s -> Ingresso: %s - Sala %d - %s - R$ %.2f\n",
               cliente.nome, ing.nomeFilme, ing.sala, ing.horario, ing.preco);
        
        enfileirar(&filasExibicao[indiceFilme], cliente);
        vendidos++;
    }
    
    printf("\nVenda concluída. Foram vendidos %d ingressos.\n", vendidos);
    if (filaVazia(&filaInicial)) {
        printf("Todos os clientes foram atendidos.\n");
    } else if (pilhaVazia(&pilhas[indiceFilme])) {
        printf("Os ingressos para este filme acabaram. Ainda há clientes na fila inicial.\n");
    }
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int main() {
    int opcao, indiceFilme;
    
    inicializarFila(&filaInicial);
    for (int i = 0; i < NUM_FILMES; i++) {
        inicializarPilha(&pilhas[i]);
        inicializarFila(&filasExibicao[i]);
    }
    
    do {
        printf("\n=== SISTEMA DE VENDA DE INGRESSOS - CINECAPI ===\n");
        printf("1. Preencher automaticamente a fila de clientes\n");
        printf("2. Preencher automaticamente as pilhas de ingressos\n");
        printf("3. Vender ingressos (escolher um filme)\n");
        printf("4. Imprimir fila inicial de clientes\n");
        printf("5. Imprimir uma fila de exibição\n");
        printf("6. Imprimir uma pilha de ingressos\n");
        printf("7. Buscar cliente na fila inicial\n");
        printf("8. Buscar ingresso em uma pilha\n");
        printf("9. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limparBuffer();
        
        switch(opcao) {
            case 1:
                preencherFilaClientes();
                break;
            case 2:
                preencherPilhasIngressos();
                break;
            case 3:
                printf("Escolha o filme:\n");
                for (int i = 0; i < NUM_FILMES; i++) {
                    printf("%d - %s\n", i+1, nomesFilmes[i]);
                }
                printf("Opção: ");
                scanf("%d", &indiceFilme);
                limparBuffer();
                if (indiceFilme >= 1 && indiceFilme <= NUM_FILMES) {
                    venderIngressos(indiceFilme - 1);
                } else {
                    printf("Opção inválida!\n");
                }
                break;
            case 4:
                imprimirFila(&filaInicial, "Fila Inicial de Clientes");
                break;
            case 5:
                printf("Escolha o filme para ver a fila de exibição:\n");
                for (int i = 0; i < NUM_FILMES; i++) {
                    printf("%d - %s\n", i+1, nomesFilmes[i]);
                }
                printf("Opção: ");
                scanf("%d", &indiceFilme);
                limparBuffer();
                if (indiceFilme >= 1 && indiceFilme <= NUM_FILMES) {
                    char nomeFila[100];
                    sprintf(nomeFila, "Fila de Exibição - %s", nomesFilmes[indiceFilme-1]);
                    imprimirFila(&filasExibicao[indiceFilme-1], nomeFila);
                } else {
                    printf("Opção inválida!\n");
                }
                break;
            case 6:
                printf("Escolha o filme para ver a pilha de ingressos:\n");
                for (int i = 0; i < NUM_FILMES; i++) {
                    printf("%d - %s\n", i+1, nomesFilmes[i]);
                }
                printf("Opção: ");
                scanf("%d", &indiceFilme);
                limparBuffer();
                if (indiceFilme >= 1 && indiceFilme <= NUM_FILMES) {
                    char nomePilha[100];
                    sprintf(nomePilha, "Pilha de Ingressos - %s", nomesFilmes[indiceFilme-1]);
                    imprimirPilha(&pilhas[indiceFilme-1], nomePilha);
                } else {
                    printf("Opção inválida!\n");
                }
                break;
            case 7:
                {
                    char nomeBusca[MAX_NOME];
                    printf("Digite o nome do cliente a buscar: ");
                    fgets(nomeBusca, MAX_NOME, stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                    int pos = buscarNaFila(&filaInicial, nomeBusca);
                    if (pos != -1) {
                        printf("Cliente encontrado na posição %d da fila inicial.\n", pos+1);
                    } else {
                        printf("Cliente não encontrado.\n");
                    }
                }
                break;
            case 8:
                {
                    char nomeFilmeBusca[MAX_NOME];
                    printf("Digite o nome do filme para buscar ingresso: ");
                    fgets(nomeFilmeBusca, MAX_NOME, stdin);
                    nomeFilmeBusca[strcspn(nomeFilmeBusca, "\n")] = '\0';
                    int encontrado = 0;
                    for (int i = 0; i < NUM_FILMES; i++) {
                        int pos = buscarNaPilha(&pilhas[i], nomeFilmeBusca);
                        if (pos != -1) {
                            printf("Ingresso do filme '%s' encontrado na pilha do filme %s (posição %d).\n",
                                   nomeFilmeBusca, nomesFilmes[i], pos+1);
                            encontrado = 1;
                        }
                    }
                    if (!encontrado) {
                        printf("Ingresso não encontrado em nenhuma pilha.\n");
                    }
                }
                break;
            case 9:
                printf("Encerrando sistema...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 9);
    
    return 0;
}