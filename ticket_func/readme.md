# ticket_func

Módulo responsável pela estrutura e operações relacionadas a **ingressos** (`Ticket`).

## Arquivos

- `ticket.h` — definição da struct `Ticket`, constantes e protótipos
- `ticket.c` — implementação das funções e dados globais dos filmes

## Struct Ticket

```c
typedef struct {
    char  movieName[100]; // Nome do filme
    int   room;           // Sala de exibição
    char  sessionTime[20];// Horário da sessão
    float price;          // Preço do ingresso
} Ticket;
```

## Dados globais

| Variável | Descrição                          |
| -------- | ---------------------------------- |
| `MOVIES` | Nomes dos filmes disponíveis       |
| `ROOMS`  | Salas correspondentes a cada filme |
| `TIMES`  | Horários das sessões               |
| `PRICES` | Preços dos ingressos               |

## Funções

| Função         | Descrição                                |
| -------------- | ---------------------------------------- |
| `createTicket` | Preenche um `Ticket` com os dados dados  |
| `printTicket`  | Imprime os campos de um `Ticket` na tela |
