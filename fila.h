#ifndef FILA_H
#define FILA_H

#include "constantes.h"
#include "cliente.h"

typedef struct {
    Cliente clientes[MAX_CLIENTES];
    int frente;
    int tras;
    int tamanho;
} FilaClientes;

void inicializarFila(FilaClientes *f);
int enfileirar(FilaClientes *f, Cliente c);
Cliente desenfileirar(FilaClientes *f);
int filaVazia(FilaClientes *f);
int filaCheia(FilaClientes *f);
void imprimirFila(FilaClientes *f, const char *nomeFila);
int buscarNaFila(FilaClientes *f, const char *nomeCliente);

#endif