# queue_func

Módulo responsável pela implementação da **fila circular** (`Queue`) de usuários, usando vetor estático.

## Arquivos

- `queue.h` — definição da struct `Queue` e protótipos
- `queue.c` — implementação das funções

## Struct Queue

```c
typedef struct {
    User data[MAX_QUEUE]; // Vetor de usuários (capacidade: 50)
    int  front;           // Índice do primeiro elemento
    int  rear;            // Índice da próxima posição livre
    int  size;            // Quantidade de elementos na fila
} Queue;
```

## Como funciona a fila circular

A fila usa **wrap-around** com o operador `%`:

```
rear  = (rear  + 1) % MAX_QUEUE;  // ao enfileirar
front = (front + 1) % MAX_QUEUE;  // ao desenfileirar
```

Isso permite reutilizar posições liberadas no início do vetor sem deslocar elementos.

## Funções

| Função              | Descrição                                              |
|---------------------|--------------------------------------------------------|
| `initQueue`         | Inicializa a fila (front=rear=size=0)                  |
| `isQueueEmpty`      | Retorna 1 se vazia                                     |
| `isQueueFull`       | Retorna 1 se cheia                                     |
| `enqueue`           | Insere um `User` no fim da fila                        |
| `dequeue`           | Remove e retorna o `User` do início                    |
| `peekFront`         | Consulta o início sem remover                          |
| `queueSize`         | Retorna o número de elementos                          |
| `searchUserByName`  | Busca por nome; retorna índice lógico ou -1            |
| `printQueue`        | Imprime todos os usuários (fila de compra)             |
| `printRoomQueue`    | Imprime usuários com ingressos (fila de exibição)      |
