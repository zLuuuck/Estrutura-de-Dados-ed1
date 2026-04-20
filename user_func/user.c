#include <stdio.h>
#include <string.h>
#include "user.h"

void createUser(User *u, const char *name, int age)
{
    strncpy(u->name, name, MAX_USER_NAME - 1);
    u->name[MAX_USER_NAME - 1] = '\0';
    u->age = age;
    u->hasTicket = 0;
}

void printUser(const User *u)
{
    printf("  Usuario : %s (Idade: %d)\n", u->name, u->age);
}

void printUserTicketPair(const User *u)
{
    printf("  [Usuario] %s (Idade: %d)\n", u->name, u->age);
    if (u->hasTicket)
    {
        printf("  [Ingresso]\n");
        printTicket(&u->ticket);
    }
    else
    {
        printf("  [Ingresso] Nenhum ingresso associado.\n");
    }
}
