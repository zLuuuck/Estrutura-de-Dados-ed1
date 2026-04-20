#include "main.h"

int main(void)
{
    /* Fila de compra: clientes aguardando para comprar ingresso */
    Queue buyQueue;
    initQueue(&buyQueue);

    /* Uma pilha de ingressos para cada filme */
    Stack stacks[NUM_MOVIES];
    for (int i = 0; i < NUM_MOVIES; i++)
        initStack(&stacks[i]);

    /* Uma fila de exibição para cada sala/filme */
    Queue roomQueues[NUM_MOVIES];
    for (int i = 0; i < NUM_MOVIES; i++)
        initQueue(&roomQueues[i]);

    /* Inicia o menu interativo */
    mainMenu(&buyQueue, stacks, roomQueues);

    return 0;
}
