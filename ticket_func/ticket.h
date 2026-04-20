#ifndef TICKET_H
#define TICKET_H

#define MAX_MOVIE_NAME 100
#define MAX_TIME 20

/* Numero de filmes disponiveis no cinema */
#define NUM_MOVIES 3

typedef struct
{
    char movieName[MAX_MOVIE_NAME];
    int room;
    char sessionTime[MAX_TIME];
    float price;
} Ticket;

/* Dados globais dos filmes disponíveis */
extern const char *MOVIES[NUM_MOVIES];
extern const int ROOMS[NUM_MOVIES];
extern const char *TIMES[NUM_MOVIES];
extern const float PRICES[NUM_MOVIES];

/* Preenche um ticket com os dados fornecidos */
void createTicket(Ticket *t,
                  const char *movieName,
                  int room,
                  const char *sessionTime,
                  float price);

/* Imprime os campos de um ticket */
void printTicket(const Ticket *t);

#endif /* TICKET_H */
