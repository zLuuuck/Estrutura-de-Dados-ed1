#ifndef QUEUE_H
#define QUEUE_H

#include "../user_func/user.h"

#define MAX_QUEUE 50

typedef struct
{
    User data[MAX_QUEUE];
    int front; /* índice do primeiro elemento               */
    int rear;  /* índice da próxima posição livre           */
    int size;  /* quantidade de elementos presentes na fila */
} Queue;

/* Inicializa a fila circular */
void initQueue(Queue *q);

/* Retorna 1 se a fila estiver vazia */
int isQueueEmpty(const Queue *q);

/* Retorna 1 se a fila estiver cheia */
int isQueueFull(const Queue *q);

/* Enfileira um usuário. Retorna 1 em sucesso, 0 se cheia */
int enqueue(Queue *q, User u);

/* Desenfileira e copia para *u. Retorna 1 em sucesso, 0 se vazia */
int dequeue(Queue *q, User *u);

/* Espia o início sem remover. Retorna 1 em sucesso, 0 se vazia */
int peekFront(const Queue *q, User *u);

/* Espia o último elemento da fila sem remover. Retorna 1 em sucesso, 0 se vazia */
int peekLast(const Queue *q, User *u);

/* Retorna quantos elementos há na fila */
int queueSize(const Queue *q);

/* Busca usuário por nome; retorna índice lógico (0=início) ou -1 */
int searchUserByName(const Queue *q, const char *name);

/* Imprime todos os usuários da fila (início → fim) */
void printQueue(const Queue *q);

/* Imprime todos os usuários com ingresso de uma fila de exibição */
void printRoomQueue(const Queue *q);

#endif /* QUEUE_H */
