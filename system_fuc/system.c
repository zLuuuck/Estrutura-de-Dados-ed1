#include <stdio.h>
#include <string.h>
#include "system.h"
#include "../ticket_func/ticket.h"

/* ------------------------------------------------------------------ */
/*  Utilitário interno                                                 */
/* ------------------------------------------------------------------ */

static void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/* ------------------------------------------------------------------ */
/*  Preenchimento automático                                           */
/* ------------------------------------------------------------------ */

void fillUserQueue(Queue *buyQueue)
{
    const char *names[] = {
        "Alice Souza", "Bruno Lima", "Carla Matos",
        "Diego Rocha", "Elena Ferreira", "Fabio Nunes",
        "Gabriela Costa", "Henrique Dias", "Isabela Reis",
        "Joao Pedro"};
    int ages[] = {28, 35, 22, 40, 19, 31, 26, 45, 23, 17};
    int n = 10, added = 0;

    for (int i = 0; i < n; i++)
    {
        User u;
        createUser(&u, names[i], ages[i]);
        if (enqueue(buyQueue, u))
            added++;
        else
            printf("  [AVISO] Fila cheia, nao foi possivel adicionar: %s\n", names[i]);
    }
    printf("  %d clientes adicionados a fila de compra.\n", added);
}

void fillTicketStacks(Stack stacks[])
{
    for (int m = 0; m < NUM_MOVIES; m++)
    {
        int added = 0;
        for (int i = 0; i < 10; i++)
        {
            Ticket t;
            createTicket(&t, MOVIES[m], ROOMS[m], TIMES[m], PRICES[m]);
            if (push(&stacks[m], t))
                added++;
        }
        printf("  %d ingressos empilhados para \"%s\".\n", added, MOVIES[m]);
    }
}

/* ------------------------------------------------------------------ */
/*  Operações de venda                                                 */
/* ------------------------------------------------------------------ */

int sellTicket(Queue *buyQueue,
               Stack stacks[],
               Queue roomQueues[],
               int movieIdx)
{
    if (movieIdx < 0 || movieIdx >= NUM_MOVIES)
    {
        printf("  [ERRO] Indice de filme invalido.\n");
        return 0;
    }
    if (isQueueEmpty(buyQueue))
    {
        printf("  [AVISO] Nao ha clientes na fila de compra.\n");
        return 0;
    }
    if (isStackEmpty(&stacks[movieIdx]))
    {
        printf("  [AVISO] Sem ingressos disponiveis para \"%s\".\n", MOVIES[movieIdx]);
        return 0;
    }

    User u;
    Ticket t;

    /* Retira ingresso do topo da pilha do filme escolhido */
    pop(&stacks[movieIdx], &t);

    /* Retira o primeiro cliente da fila de compra */
    dequeue(buyQueue, &u);

    /* Associa o ingresso ao cliente */
    u.ticket = t;
    u.hasTicket = 1;

    /* Exibe o par cliente -> ingresso */
    printf("\n  >> Ingresso vendido:\n");
    printUserTicketPair(&u);

    /* Enfileira o cliente na fila de exibição da sala correspondente */
    if (!enqueue(&roomQueues[movieIdx], u))
    {
        printf("  [AVISO] Fila de exibicao da sala %d esta cheia!\n", ROOMS[movieIdx]);
        return 0;
    }

    return 1;
}

void sellAllTickets(Queue *buyQueue,
                    Stack stacks[],
                    Queue roomQueues[])
{
    if (isQueueEmpty(buyQueue))
    {
        printf("  A fila de compra ja esta vazia.\n");
        return;
    }

    int sold = 0, movieIdx = 0;

    while (!isQueueEmpty(buyQueue))
    {
        /* Encontra o próximo filme com ingresso disponível */
        int tries = 0;
        while (isStackEmpty(&stacks[movieIdx]) && tries < NUM_MOVIES)
        {
            movieIdx = (movieIdx + 1) % NUM_MOVIES;
            tries++;
        }
        if (tries == NUM_MOVIES)
        {
            printf("\n  [AVISO] Todos os ingressos foram esgotados.\n");
            break;
        }

        sellTicket(buyQueue, stacks, roomQueues, movieIdx);
        sold++;
        movieIdx = (movieIdx + 1) % NUM_MOVIES;
    }

    printf("\n  Total de ingressos vendidos nesta rodada: %d\n", sold);
}

/* ------------------------------------------------------------------ */
/*  Visualização                                                       */
/* ------------------------------------------------------------------ */

void showPendingUsers(const Queue *buyQueue)
{
    printf("\n=== CLIENTES AGUARDANDO NA FILA DE COMPRA ===\n");
    printQueue(buyQueue);
}

void showAttendedUsers(const Queue roomQueues[])
{
    printf("\n=== CLIENTES JA ATENDIDOS (por sala) ===\n");
    for (int i = 0; i < NUM_MOVIES; i++)
    {
        printf("\n  Sala %d - \"%s\":\n", ROOMS[i], MOVIES[i]);
        printRoomQueue(&roomQueues[i]);
    }
}

void showAvailableTickets(const Stack stacks[])
{
    printf("\n=== INGRESSOS DISPONIVEIS (pilhas) ===\n");
    for (int i = 0; i < NUM_MOVIES; i++)
    {
        printf("\n  Filme : \"%s\" | Sala %d | %s | R$ %.2f\n",
               MOVIES[i], ROOMS[i], TIMES[i], PRICES[i]);
        printf("  Quantidade: %d\n", stackSize(&stacks[i]));
        printStack(&stacks[i]);
    }
}

void showSoldTickets(const Queue roomQueues[])
{
    printf("\n=== INGRESSOS VENDIDOS ===\n");
    int total = 0;
    for (int i = 0; i < NUM_MOVIES; i++)
    {
        int qty = queueSize(&roomQueues[i]);
        total += qty;
        printf("  \"%s\" (Sala %d): %d ingresso(s) vendido(s)\n",
               MOVIES[i], ROOMS[i], qty);
    }
    printf("  Total geral: %d\n", total);
}

void showSystemStatus(const Queue *buyQueue,
                      const Stack stacks[],
                      const Queue roomQueues[])
{
    printf("\n=== STATUS GERAL DO SISTEMA ===\n");
    printf("  Clientes na fila de compra : %d\n", queueSize(buyQueue));
    printf("\n  Ingressos disponiveis por filme:\n");
    for (int i = 0; i < NUM_MOVIES; i++)
    {
        printf("    %-22s (Sala %d): %d ingresso(s)\n",
               MOVIES[i], ROOMS[i], stackSize(&stacks[i]));
    }
    printf("\n  Clientes por sala de exibicao:\n");
    for (int i = 0; i < NUM_MOVIES; i++)
    {
        printf("    %-22s (Sala %d): %d cliente(s)\n",
               MOVIES[i], ROOMS[i], queueSize(&roomQueues[i]));
    }
}

/* ------------------------------------------------------------------ */
/*  Menu principal                                                     */
/* ------------------------------------------------------------------ */

static void printMovieOptions(void)
{
    printf("\n  Escolha o filme:\n");
    for (int i = 0; i < NUM_MOVIES; i++)
    {
        printf("    [%d] %s  (Sala %d | %s | R$ %.2f)\n",
               i + 1, MOVIES[i], ROOMS[i], TIMES[i], PRICES[i]);
    }
    printf("  Opcao: ");
}

void mainMenu(Queue *buyQueue,
              Stack stacks[],
              Queue roomQueues[])
{
    int option;

    do
    {
        printf("\n");
        printf("=========================================\n");
        printf("      CineCapi - Sistema de Ingressos    \n");
        printf("=========================================\n");
        printf("  [1] Preencher fila de clientes (auto)\n");
        printf("  [2] Preencher pilhas de ingressos (auto)\n");
        printf("  [3] Vender ingresso (escolher filme)\n");
        printf("  [4] Vender todos os ingressos (automatico)\n");
        printf("  [5] Ver clientes aguardando na fila\n");
        printf("  [6] Ver clientes atendidos (por sala)\n");
        printf("  [7] Ver ingressos disponiveis\n");
        printf("  [8] Ver ingressos vendidos\n");
        printf("  [9] Ver status geral\n");
        printf("  [0] Sair\n");
        printf("-----------------------------------------\n");
        printf("  Opcao: ");

        if (scanf("%d", &option) != 1)
        {
            clearInputBuffer();
            option = -1;
        }
        else
        {
            clearInputBuffer();
        }

        switch (option)
        {

        case 1:
            printf("\n--- Preenchendo fila de clientes ---\n");
            fillUserQueue(buyQueue);
            break;

        case 2:
            printf("\n--- Preenchendo pilhas de ingressos ---\n");
            fillTicketStacks(stacks);
            break;

        case 3:
        {
            printMovieOptions();
            int choice;
            if (scanf("%d", &choice) != 1)
            {
                clearInputBuffer();
                break;
            }
            clearInputBuffer();
            sellTicket(buyQueue, stacks, roomQueues, choice - 1);
            break;
        }

        case 4:
            printf("\n--- Vendendo todos os ingressos ---\n");
            sellAllTickets(buyQueue, stacks, roomQueues);
            break;

        case 5:
            showPendingUsers(buyQueue);
            break;

        case 6:
            showAttendedUsers(roomQueues);
            break;

        case 7:
            showAvailableTickets(stacks);
            break;

        case 8:
            showSoldTickets(roomQueues);
            break;

        case 9:
            showSystemStatus(buyQueue, stacks, roomQueues);
            break;

        case 0:
            printf("\n  Encerrando o sistema CineCapi. Ate logo!\n\n");
            break;

        default:
            printf("  [ERRO] Opcao invalida. Tente novamente.\n");
        }

    } while (option != 0);
}
