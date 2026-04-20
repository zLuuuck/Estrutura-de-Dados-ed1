#include <stdio.h>
#include <string.h>
#include "stack.h"

void initStack(Stack *s)
{
    s->top = -1;
}

int isStackEmpty(const Stack *s)
{
    return s->top == -1;
}

int isStackFull(const Stack *s)
{
    return s->top == MAX_STACK - 1;
}

int push(Stack *s, Ticket t)
{
    if (isStackFull(s))
        return 0;
    s->top++;
    s->data[s->top] = t;
    return 1;
}

int pop(Stack *s, Ticket *t)
{
    if (isStackEmpty(s))
        return 0;
    *t = s->data[s->top];
    s->top--;
    return 1;
}

int peekTop(const Stack *s, Ticket *t)
{
    if (isStackEmpty(s))
        return 0;
    *t = s->data[s->top];
    return 1;
}

int stackSize(const Stack *s)
{
    return s->top + 1;
}

int searchTicketByMovie(const Stack *s, const char *movieName)
{
    for (int i = s->top; i >= 0; i--)
    {
        if (strncmp(s->data[i].movieName, movieName, MAX_MOVIE_NAME) == 0)
            return i;
    }
    return -1;
}

void printStack(const Stack *s)
{
    if (isStackEmpty(s))
    {
        printf("  [Pilha vazia]\n");
        return;
    }
    printf("  Total de ingressos: %d\n", stackSize(s));
    printf("  --- Topo ---\n");
    for (int i = s->top; i >= 0; i--)
    {
        printf("  [%d]\n", s->top - i + 1);
        printTicket(&s->data[i]);
        printf("  -----------\n");
    }
}
