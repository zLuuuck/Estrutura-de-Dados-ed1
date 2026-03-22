#include <stdio.h>
#include <string.h>
#include "ingresso.h"

Ingresso criarIngresso(char nome[], int sala, char horario[], float preco) {
    Ingresso i;

    strcpy(i.nomeFilme, nome);
    i.sala = sala;
    strcpy(i.horario, horario);
    i.preco = preco;

    return i;
}

void imprimirIngresso(Ingresso i) {
    printf("\nFilme: %s", i.nomeFilme);
    printf("\nSala: %d", i.sala);
    printf("\nHorario: %s", i.horario);
    printf("\nPreco: R$ %.2f\n", i.preco);
}