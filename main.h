#ifndef MAIN_H
#define MAIN_H

#include "fila.h"
#include "pilha.h"

// Declaração das variáveis globais (definidas em main.c)
extern FilaClientes filaInicial;
extern PilhaIngressos pilhas[NUM_FILMES];
extern FilaClientes filasExibicao[NUM_FILMES];
extern const char *nomesFilmes[NUM_FILMES];
extern const Ingresso ingressosExemplo[NUM_FILMES];

// Protótipos das funções auxiliares que serão usadas em main
void preencherFilaClientes();
void preencherPilhasIngressos();
void venderIngressos(int indiceFilme);
void limparBuffer();

#endif