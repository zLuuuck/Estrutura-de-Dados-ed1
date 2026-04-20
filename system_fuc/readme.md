# system_fuc

Módulo responsável pelo **fluxo principal** do sistema CineCapi: menu interativo, preenchimento automático, vendas e relatórios.

## Arquivos

- `system.h` — protótipos de todas as funções do sistema
- `system.c` — implementação completa

## Funções

### Menu

| Função     | Descrição                                  |
| ---------- | ------------------------------------------ |
| `mainMenu` | Loop principal do menu interativo de texto |

### Preenchimento automático

| Função             | Descrição                                         |
| ------------------ | ------------------------------------------------- |
| `fillUserQueue`    | Adiciona 10 clientes de exemplo na fila de compra |
| `fillTicketStacks` | Empilha 10 ingressos em cada pilha de filme       |

### Vendas

| Função           | Descrição                                                         |
| ---------------- | ----------------------------------------------------------------- |
| `sellTicket`     | Vende 1 ingresso de um filme específico para o 1º cliente da fila |
| `sellAllTickets` | Vende ingressos em loop até esvaziar a fila de compra             |

### Visualização

| Função                 | Descrição                                   |
| ---------------------- | ------------------------------------------- |
| `showPendingUsers`     | Clientes ainda aguardando na fila de compra |
| `showAttendedUsers`    | Clientes já atendidos, organizados por sala |
| `showAvailableTickets` | Ingressos disponíveis em cada pilha         |
| `showSoldTickets`      | Contagem de ingressos vendidos por filme    |
| `showSystemStatus`     | Resumo geral de todas as estruturas         |

## Fluxo de venda

```
Fila de compra  -->  dequeue(cliente)
Pilha do filme  -->  pop(ingresso)
cliente.ticket  =   ingresso
                -->  enqueue(roomQueue[filme], cliente)
```
