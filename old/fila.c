#include "fila.h"
#include <stdio.h>
#include <string.h>

void inicializarFila(FilaClientes *f) {
    f->frente = 0;
    f->tras = -1;
    f->tamanho = 0;
}

int enfileirar(FilaClientes *f, Cliente c) {
    if (filaCheia(f)) {
        printf("Erro: fila cheia!\n");
        return 0;
    }
    f->tras = (f->tras + 1) % MAX_CLIENTES;
    f->clientes[f->tras] = c;
    f->tamanho++;
    return 1;
}

Cliente desenfileirar(FilaClientes *f) {
    Cliente vazio = {"", 0, {"", 0, "", 0}};
    if (filaVazia(f)) {
        printf("Erro: fila vazia!\n");
        return vazio;
    }
    Cliente c = f->clientes[f->frente];
    f->frente = (f->frente + 1) % MAX_CLIENTES;
    f->tamanho--;
    return c;
}

int filaVazia(FilaClientes *f) {
    return f->tamanho == 0;
}

int filaCheia(FilaClientes *f) {
    return f->tamanho == MAX_CLIENTES;
}

void imprimirFila(FilaClientes *f, const char *nomeFila) {
    printf("\n=== %s ===\n", nomeFila);
    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return;
    }
    int i = f->frente;
    for (int count = 0; count < f->tamanho; count++) {
        Cliente c = f->clientes[i];
        printf("Cliente: %s, Idade: %d\n", c.nome, c.idade);
        if (strlen(c.ingresso.nomeFilme) > 0) {
            printf("  Ingresso: %s - Sala %d - %s - R$ %.2f\n",
                   c.ingresso.nomeFilme, c.ingresso.sala,
                   c.ingresso.horario, c.ingresso.preco);
        } else {
            printf("  (Aguardando ingresso)\n");
        }
        i = (i + 1) % MAX_CLIENTES;
    }
}

int buscarNaFila(FilaClientes *f, const char *nomeCliente) {
    if (filaVazia(f)) return -1;
    int i = f->frente;
    for (int count = 0; count < f->tamanho; count++) {
        if (strcmp(f->clientes[i].nome, nomeCliente) == 0) {
            return count;  // posição relativa na fila (0 = primeiro)
        }
        i = (i + 1) % MAX_CLIENTES;
    } 
    return -1;
}