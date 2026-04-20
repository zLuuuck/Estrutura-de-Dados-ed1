# stack_func

Módulo responsável pela implementação da **pilha** (`Stack`) de ingressos, usando vetor estático.

## Arquivos

- `stack.h` — definição da struct `Stack` e protótipos
- `stack.c` — implementação das funções

## Struct Stack

```c
typedef struct {
    Ticket data[MAX_STACK]; // Vetor de ingressos (capacidade: 50)
    int    top;             // Índice do topo; -1 = pilha vazia
} Stack;
```

## Como funciona a pilha

A pilha segue a política **LIFO** (Last In, First Out):

- `push`: incrementa `top` e insere em `data[top]`
- `pop`: copia `data[top]` e decrementa `top`

## Funções

| Função                | Descrição                                     |
| --------------------- | --------------------------------------------- |
| `initStack`           | Inicializa a pilha (top = -1)                 |
| `isStackEmpty`        | Retorna 1 se vazia                            |
| `isStackFull`         | Retorna 1 se cheia                            |
| `push`                | Empilha um `Ticket`                           |
| `pop`                 | Desempilha e retorna o `Ticket` do topo       |
| `peekTop`             | Consulta o topo sem remover                   |
| `stackSize`           | Retorna o número de elementos                 |
| `searchTicketByMovie` | Busca por nome do filme; retorna índice ou -1 |
| `printStack`          | Imprime todos os tickets (topo → base)        |
