#ifndef INGRESSO_H
#define INGRESSO_H

#include "constantes.h"

typedef struct {
    char nomeFilme[MAX_NOME];
    int sala;
    char horario[MAX_HORARIO];
    float preco;
} Ingresso;

Ingresso criarIngresso(char nome[], int sala, char horario[], float preco);
void imprimirIngresso(Ingresso i);

#endif