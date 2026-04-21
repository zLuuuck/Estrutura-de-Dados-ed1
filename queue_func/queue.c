#include <stdio.h>
#include <string.h>
#include "queue.h"

void initQueue(Queue *q)
{
    q->front = 0;
    q->rear = 0;
    q->size = 0;
}

int isQueueEmpty(const Queue *q)
{
    return q->size == 0;
}

int isQueueFull(const Queue *q)
{
    return q->size == MAX_QUEUE;
}

int enqueue(Queue *q, User u)
{
    if (isQueueFull(q))
        return 0;
    q->data[q->rear] = u;
    q->rear = (q->rear + 1) % MAX_QUEUE; /* wrap-around circular */
    q->size++;
    return 1;
}

int dequeue(Queue *q, User *u)
{
    if (isQueueEmpty(q))
        return 0;
    *u = q->data[q->front];
    q->front = (q->front + 1) % MAX_QUEUE; /* wrap-around circular */
    q->size--;
    return 1;
}

int peekFront(const Queue *q, User *u)
{
    if (isQueueEmpty(q))
        return 0;
    *u = q->data[q->front];
    return 1;
}

int peekLast(const Queue *q, User *u)
{
    if (isQueueEmpty(q))
        return 0;
    // O último elemento está na posição anterior ao rear (com wrap-around)
    int idx = (q->rear - 1 + MAX_QUEUE) % MAX_QUEUE;
    *u = q->data[idx];
    return 1;
}

int queueSize(const Queue *q)
{
    return q->size;
}

int searchUserByName(const Queue *q, const char *name)
{
    for (int i = 0; i < q->size; i++)
    {
        int idx = (q->front + i) % MAX_QUEUE;
        if (strncmp(q->data[idx].name, name, MAX_USER_NAME) == 0)
            return i;
    }
    return -1;
}

void printQueue(const Queue *q)
{
    if (isQueueEmpty(q))
    {
        printf("  [Fila vazia]\n");
        return;
    }
    printf("  Total na fila: %d\n", q->size);
    printf("  --- Inicio ---\n");
    for (int i = 0; i < q->size; i++)
    {
        int idx = (q->front + i) % MAX_QUEUE;
        printf("  [%d] ", i + 1);
        printUser(&q->data[idx]);
    }
    printf("  --- Fim ---\n");
}

void printRoomQueue(const Queue *q)
{
    if (isQueueEmpty(q))
    {
        printf("  [Sala vazia]\n");
        return;
    }
    printf("  Total de clientes na sala: %d\n", q->size);
    printf("  ==========================\n");
    for (int i = 0; i < q->size; i++)
    {
        int idx = (q->front + i) % MAX_QUEUE;
        printf("  Assento %d:\n", i + 1);
        printUserTicketPair(&q->data[idx]);
        printf("  --------------------------\n");
    }
}
