#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <system.h>
#include "../ticket_func/ticket.h"

#ifdef _WIN32
#define CLEAR_CMD "cls"
#else
#define CLEAR_CMD "clear"
#endif

/* ------------------------------------------------------------------ */
/*  Utilitários internos                                               */
/* ------------------------------------------------------------------ */

static void clearScreen(void)
{
    system(CLEAR_CMD);
}

static void clearInputBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

static void pauseScreen(void)
{
    printf("\n  Pressione ENTER para continuar...");
    clearInputBuffer();
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
/*  Funções de busca                                                  */
/* ------------------------------------------------------------------ */

void searchUserInBuyQueue(const Queue *buyQueue)
{
    if (isQueueEmpty(buyQueue))
    {
        printf("  A fila de compra está vazia.\n");
        return;
    }

    char name[MAX_USER_NAME];
    printf("  Digite o nome do cliente: ");
    if (scanf(" %[^\n]", name) != 1)
    {
        clearInputBuffer();
        printf("  Entrada inválida.\n");
        return;
    }
    clearInputBuffer();

    int pos = searchUserByName(buyQueue, name);
    if (pos == -1)
    {
        printf("  Cliente \"%s\" não encontrado na fila de compra.\n", name);
    }
    else
    {
        printf("  Cliente \"%s\" encontrado na posição %d da fila.\n", name, pos + 1);
        // Exibe os dados do cliente encontrado (opcional)
        User u;
        // Para exibir, precisamos pegar o elemento. Podemos iterar até a posição.
        int idx = (buyQueue->front + pos) % MAX_QUEUE;
        u = buyQueue->data[idx];
        printUser(&u);
    }
}

void searchTicketInStack(const Stack *stack, int movieIdx)
{
    if (movieIdx < 0 || movieIdx >= NUM_MOVIES)
    {
        printf("  Índice de filme inválido.\n");
        return;
    }
    if (isStackEmpty(stack))
    {
        printf("  A pilha de ingressos para \"%s\" está vazia.\n", MOVIES[movieIdx]);
        return;
    }

    // Como a pilha já é específica do filme, a busca por nome do filme é redundante,
    // mas podemos buscar se existe um ingresso com aquele nome (todos têm o mesmo).
    // Exibiremos o topo e a quantidade.
    printf("  Filme selecionado: %s\n", MOVIES[movieIdx]);
    printf("  Ingressos disponíveis: %d\n", stackSize(stack));
    if (!isStackEmpty(stack))
    {
        Ticket t;
        peekTop(stack, &t);
        printf("  Próximo ingresso a ser vendido (topo):\n");
        printTicket(&t);
    }
}

/* ------------------------------------------------------------------ */
/*  Espiar elementos da fila                                           */
/* ------------------------------------------------------------------ */

void showNextUser(const Queue *buyQueue)
{
    User u;
    if (!peekFront(buyQueue, &u))
    {
        printf("  A fila de compra está vazia.\n");
        return;
    }
    printf("  Próximo cliente a ser atendido:\n");
    printUser(&u);
}

void showLastUser(const Queue *buyQueue)
{
    User u;
    if (!peekLast(buyQueue, &u))
    {
        printf("  A fila de compra está vazia.\n");
        return;
    }
    printf("  Último cliente da fila (entrou mais recentemente):\n");
    printUser(&u);
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

static void printMenu(const Queue *buyQueue,
                      const Stack stacks[],
                      const Queue roomQueues[])
{
    printf("=========================================\n");
    printf("      CineCapi - Sistema de Ingressos    \n");
    printf("=========================================\n");

    /* Mini status no topo do menu */
    printf("  Fila de compra : %d cliente(s)\n", queueSize(buyQueue));
    for (int i = 0; i < NUM_MOVIES; i++)
    {
        printf("  %-20s: %d ingresso(s) | %d na sala\n",
               MOVIES[i],
               stackSize(&stacks[i]),
               queueSize(&roomQueues[i]));
    }

    printf("-----------------------------------------\n");
    printf("  [1] Preencher fila de clientes (auto)\n");
    printf("  [2] Preencher pilhas de ingressos (auto)\n");
    printf("  [3] Vender ingresso (escolher filme)\n");
    printf("  [4] Vender todos os ingressos (automatico)\n");
    printf("  [5] Ver clientes aguardando na fila\n");
    printf("  [6] Ver clientes atendidos (por sala)\n");
    printf("  [7] Ver ingressos disponiveis\n");
    printf("  [8] Ver ingressos vendidos\n");
    printf("  [9] Ver status geral\n");
    printf("  [10] Buscar cliente na fila de compra\n");
    printf("  [11] Buscar ingresso por filme\n");
    printf("  [12] Ver próximo cliente da fila\n");
    printf("  [13] Ver último cliente da fila\n");
    printf("  [0] Sair\n");
    printf("  [0] Sair\n");
    printf("-----------------------------------------\n");
    printf("  Opcao: ");
}

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
        /* 1. Limpa a tela e exibe o menu */
        clearScreen();
        printMenu(buyQueue, stacks, roomQueues);

        /* 2. Lê a opção do usuário */
        if (scanf("%d", &option) != 1)
        {
            clearInputBuffer();
            option = -1;
        }
        else
        {
            clearInputBuffer();
        }

        /* 3. Limpa a tela e executa a ação */
        clearScreen();

        switch (option)
        {

        case 1:
            printf("=========================================\n");
            printf("      [1] Preencher fila de clientes     \n");
            printf("=========================================\n");
            fillUserQueue(buyQueue);
            pauseScreen();
            break;

        case 2:
            printf("=========================================\n");
            printf("    [2] Preencher pilhas de ingressos    \n");
            printf("=========================================\n");
            fillTicketStacks(stacks);
            pauseScreen();
            break;

        case 3:
        {
            printf("=========================================\n");
            printf("         [3] Vender ingresso             \n");
            printf("=========================================\n");
            printMovieOptions();
            int choice;
            if (scanf("%d", &choice) != 1)
            {
                clearInputBuffer();
                break;
            }
            clearInputBuffer();
            clearScreen();
            printf("=========================================\n");
            printf("         [3] Vender ingresso             \n");
            printf("=========================================\n");
            sellTicket(buyQueue, stacks, roomQueues, choice - 1);
            pauseScreen();
            break;
        }

        case 4:
            printf("=========================================\n");
            printf("   [4] Vender todos os ingressos (auto)  \n");
            printf("=========================================\n");
            sellAllTickets(buyQueue, stacks, roomQueues);
            pauseScreen();
            break;

        case 5:
            printf("=========================================\n");
            printf("      [5] Clientes aguardando na fila    \n");
            printf("=========================================\n");
            showPendingUsers(buyQueue);
            pauseScreen();
            break;

        case 6:
            printf("=========================================\n");
            printf("       [6] Clientes atendidos por sala   \n");
            printf("=========================================\n");
            showAttendedUsers(roomQueues);
            pauseScreen();
            break;

        case 7:
            printf("=========================================\n");
            printf("       [7] Ingressos disponiveis         \n");
            printf("=========================================\n");
            showAvailableTickets(stacks);
            pauseScreen();
            break;

        case 8:
            printf("=========================================\n");
            printf("         [8] Ingressos vendidos          \n");
            printf("=========================================\n");
            showSoldTickets(roomQueues);
            pauseScreen();
            break;

        case 9:
            printf("=========================================\n");
            printf("              [9] Status geral           \n");
            printf("=========================================\n");
            showSystemStatus(buyQueue, stacks, roomQueues);
            pauseScreen();
            break;

        case 10:
            printf("=========================================\n");
            printf("     [10] Buscar cliente na fila        \n");
            printf("=========================================\n");
            searchUserInBuyQueue(buyQueue);
            pauseScreen();
            break;

        case 11:
        {
            printf("=========================================\n");
            printf("     [11] Buscar ingresso por filme     \n");
            printf("=========================================\n");
            printMovieOptions();
            int choice;
            if (scanf("%d", &choice) != 1)
            {
                clearInputBuffer();
                break;
            }
            clearInputBuffer();
            clearScreen();
            printf("=========================================\n");
            printf("     [11] Buscar ingresso por filme     \n");
            printf("=========================================\n");
            if (choice >= 1 && choice <= NUM_MOVIES)
            {
                searchTicketInStack(&stacks[choice - 1], choice - 1);
            }
            else
            {
                printf("  Opção inválida.\n");
            }
            pauseScreen();
            break;
        }

        case 12:
            printf("=========================================\n");
            printf("    [12] Próximo cliente da fila        \n");
            printf("=========================================\n");
            showNextUser(buyQueue);
            pauseScreen();
            break;

        case 13:
            printf("=========================================\n");
            printf("     [13] Último cliente da fila        \n");
            printf("=========================================\n");
            showLastUser(buyQueue);
            pauseScreen();
            break;

        case 0:
            clearScreen();
            printf("=========================================\n");
            printf("      CineCapi - Sistema de Ingressos    \n");
            printf("=========================================\n");
            printf("\n  Encerrando o sistema. Ate logo!\n\n");
            break;

        default:
            printf("  [ERRO] Opcao invalida. Tente novamente.\n");
            pauseScreen();
        }

    } while (option != 0);
}