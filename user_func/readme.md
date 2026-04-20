# user_func

Módulo responsável pela estrutura e operações relacionadas a **clientes** (`User`).

## Arquivos

- `user.h` — definição da struct `User` e protótipos
- `user.c` — implementação das funções

## Struct User

```c
typedef struct {
    char   name[100];  // Nome do cliente
    int    age;        // Idade
    Ticket ticket;     // Ingresso comprado (após venda)
    int    hasTicket;  // 0 = sem ingresso | 1 = com ingresso
} User;
```

## Funções

| Função                | Descrição                                |
| --------------------- | ---------------------------------------- |
| `createUser`          | Inicializa um `User` com nome e idade    |
| `printUser`           | Imprime os dados básicos do usuário      |
| `printUserTicketPair` | Imprime o par usuário → ingresso na tela |
