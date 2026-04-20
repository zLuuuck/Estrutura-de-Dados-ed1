#ifndef STACK_H
#define STACK_H

#include "../ticket_func/ticket.h"

#define MAX_STACK 50

typedef struct
{
    Ticket data[MAX_STACK];
    int top; /* índice do topo; -1 = vazia */
} Stack;

/* Inicializa a pilha (top = -1) */
void initStack(Stack *s);

/* Retorna 1 se a pilha estiver vazia */
int isStackEmpty(const Stack *s);

/* Retorna 1 se a pilha estiver cheia */
int isStackFull(const Stack *s);

/* Empilha um ticket. Retorna 1 em sucesso, 0 se cheia */
int push(Stack *s, Ticket t);

/* Desempilha e copia para *t. Retorna 1 em sucesso, 0 se vazia */
int pop(Stack *s, Ticket *t);

/* Espia o topo sem remover. Retorna 1 em sucesso, 0 se vazia */
int peekTop(const Stack *s, Ticket *t);

/* Retorna quantos elementos há na pilha */
int stackSize(const Stack *s);

/* Busca ticket pelo nome do filme; retorna índice ou -1 */
int searchTicketByMovie(const Stack *s, const char *movieName);

/* Imprime todos os tickets da pilha (topo → base) */
void printStack(const Stack *s);

#endif /* STACK_H */
