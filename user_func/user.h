#ifndef USER_H
#define USER_H

#include "../ticket_func/ticket.h"

#define MAX_USER_NAME 100

typedef struct
{
    char name[MAX_USER_NAME];
    int age;
    Ticket ticket; /* ingresso comprado (preenchido após venda) */
    int hasTicket; /* 0 = ainda não comprou | 1 = já comprou    */
} User;

/* Inicializa um usuário com nome e idade (sem ingresso) */
void createUser(User *u, const char *name, int age);

/* Imprime os dados básicos do usuário */
void printUser(const User *u);

/* Imprime o par usuário -> ingresso */
void printUserTicketPair(const User *u);

#endif /* USER_H */
