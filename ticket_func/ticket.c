#include <stdio.h>
#include <string.h>
#include "ticket.h"

/* ------------------------------------------------------------------ */
/*  Dados globais dos filmes                                           */
/* ------------------------------------------------------------------ */

const char *MOVIES[NUM_MOVIES] = {
    "Interestelar",
    "Matrix",
    "O Senhor dos Aneis"};

const int ROOMS[NUM_MOVIES] = {1, 2, 3};

const char *TIMES[NUM_MOVIES] = {
    "14:00",
    "16:30",
    "19:00"};

const float PRICES[NUM_MOVIES] = {28.50f, 25.00f, 32.00f};

/* ------------------------------------------------------------------ */
/*  Funções de ticket                                                  */
/* ------------------------------------------------------------------ */

void createTicket(Ticket *t,
                  const char *movieName,
                  int room,
                  const char *sessionTime,
                  float price)
{
    strncpy(t->movieName, movieName, MAX_MOVIE_NAME - 1);
    t->movieName[MAX_MOVIE_NAME - 1] = '\0';

    t->room = room;

    strncpy(t->sessionTime, sessionTime, MAX_TIME - 1);
    t->sessionTime[MAX_TIME - 1] = '\0';

    t->price = price;
}

void printTicket(const Ticket *t)
{
    printf("  Filme   : %s\n", t->movieName);
    printf("  Sala    : %d\n", t->room);
    printf("  Horario : %s\n", t->sessionTime);
    printf("  Preco   : R$ %.2f\n", t->price);
}
