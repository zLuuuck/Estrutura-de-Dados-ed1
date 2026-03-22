#ifndef CLIENTE_H
#define CLIENTE_H

#include "constantes.h"
#include "ingresso.h"

typedef struct {
    char nome[MAX_NOME];
    int idade;
    Ingresso ingresso;   // ingresso comprado (preenchido após venda)
} Cliente;

#endif