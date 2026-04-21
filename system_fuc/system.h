#ifndef SYSTEM_H
#define SYSTEM_H

#include "../queue_func/queue.h"
#include "../stack_func/stack.h"

/* ------------------------------------------------------------------ */
/*  Menu principal                                                     */
/* ------------------------------------------------------------------ */

/*
 * Inicia o loop do menu interativo do CineCapi.
 *   buyQueue     - fila de compra (clientes aguardando)
 *   stacks       - pilhas de ingressos [NUM_MOVIES]
 *   roomQueues   - filas de exibição por sala [NUM_MOVIES]
 */
void mainMenu(Queue *buyQueue,
              Stack stacks[],
              Queue roomQueues[]);

/* ------------------------------------------------------------------ */
/*  Preenchimento automático                                           */
/* ------------------------------------------------------------------ */

/* Preenche a fila de compra com usuários de exemplo */
void fillUserQueue(Queue *buyQueue);

/* Preenche todas as pilhas com ingressos de exemplo */
void fillTicketStacks(Stack stacks[]);

/* ------------------------------------------------------------------ */
/*  Operações de venda                                                 */
/* ------------------------------------------------------------------ */

/*
 * Vende um ingresso do filme de índice movieIdx para o 1º usuário
 * da fila de compra e o move para a fila de exibição da sala.
 * Retorna 1 em sucesso, 0 caso contrário.
 */
int sellTicket(Queue *buyQueue,
               Stack stacks[],
               Queue roomQueues[],
               int movieIdx);

/* Vende ingressos até esvaziar a fila de compra (fluxo automático) */
void sellAllTickets(Queue *buyQueue,
                    Stack stacks[],
                    Queue roomQueues[]);

/* ------------------------------------------------------------------ */
/*  Visualização / relatórios                                         */
/* ------------------------------------------------------------------ */

/* Mostra os usuários aguardando na fila de compra */
void showPendingUsers(const Queue *buyQueue);

/* Mostra todos os clientes já atendidos, por sala */
void showAttendedUsers(const Queue roomQueues[]);

/* Mostra ingressos disponíveis em cada pilha */
void showAvailableTickets(const Stack stacks[]);

/* Mostra quantos ingressos foram vendidos por filme */
void showSoldTickets(const Queue roomQueues[]);

/* Mostra resumo geral do sistema */
void showSystemStatus(const Queue *buyQueue,
                      const Stack stacks[],
                      const Queue roomQueues[]);

/* Busca um cliente pelo nome na fila de compra e exibe sua posição */
void searchUserInBuyQueue(const Queue *buyQueue);

/* Busca um ingresso pelo nome do filme em uma pilha específica */
void searchTicketInStack(const Stack *stack, int movieIdx);

void showNextUser(const Queue *buyQueue);
void showLastUser(const Queue *buyQueue);

#endif /* SYSTEM_H */
