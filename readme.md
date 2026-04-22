# 🎬 CineCapi – Sistema de Venda de Ingressos

Sistema de gerenciamento de vendas para um cinema, desenvolvido em **linguagem C** como estudo dirigido da disciplina de Estruturas de Dados.  
O projeto utiliza **filas circulares** para organizar os clientes e **pilhas estáticas** para controlar o estoque de ingressos, implementadas manualmente com vetores.

---

## 📌 Funcionalidades

- ✅ Cadastro automático de clientes e ingressos (dados de exemplo)
- ✅ Venda de ingressos por filme (escolha manual)
- ✅ Venda automática até esvaziar a fila de espera
- ✅ Visualização de:
  - Clientes aguardando na fila
  - Clientes já atendidos por sala
  - Ingressos disponíveis (pilhas)
  - Ingressos vendidos
  - Status geral do sistema
- 🔍 Busca de cliente por nome na fila
- 🔍 Busca de ingresso por filme
- 👀 Espiar próximo e último cliente da fila (sem remover)
- 🖥️ Interface de terminal com limpeza de tela e pausa controlada

---

## 📁 Estrutura do Projeto

```
.
├── main.c                 # Ponto de entrada do programa
├── main.h                 # Cabeçalho central
├── Makefile               # Automação da compilação
├── .gitignore
├── queue_func/            # Implementação da fila circular
│   ├── queue.h
│   ├── queue.c
│   └── readme.md
├── stack_func/            # Implementação da pilha estática
│   ├── stack.h
│   ├── stack.c
│   └── readme.md
├── user_func/             # Definição do tipo User (cliente)
│   ├── user.h
│   ├── user.c
│   └── readme.md
├── ticket_func/           # Definição do tipo Ticket (ingresso) e dados dos filmes
│   ├── ticket.h
│   ├── ticket.c
│   └── readme.md
└── system_fuc/            # Lógica de alto nível: menu, vendas, relatórios
    ├── system.h
    ├── system.c
    └── readme.md
```

> Os arquivos `readme.md` dentro de cada pasta contêm uma breve descrição do módulo.

---

## ⚙️ Requisitos

- Compilador GCC (MinGW no Windows, GCC no Linux)
- Make (opcional, mas recomendado)
- Sistema operacional Windows ou Linux

---

## 🔨 Como Compilar

### Usando Make (recomendado)

```bash
make
```

Isso gerará o executável `cinecapi` (Linux) ou `cinecapi.exe` (Windows).

### Manualmente (sem Make)

```bash
gcc -Wall -Wextra -std=c99 -c queue_func/queue.c -o queue_func/queue.o
gcc -Wall -Wextra -std=c99 -c stack_func/stack.c -o stack_func/stack.o
gcc -Wall -Wextra -std=c99 -c user_func/user.c -o user_func/user.o
gcc -Wall -Wextra -std=c99 -c ticket_func/ticket.c -o ticket_func/ticket.o
gcc -Wall -Wextra -std=c99 -c system_fuc/system.c -o system_fuc/system.o
gcc -Wall -Wextra -std=c99 -c main.c -o main.o
gcc -o cinecapi main.o queue_func/queue.o stack_func/stack.o user_func/user.o ticket_func/ticket.o system_fuc/system.o
```

### Limpar arquivos objeto

```bash
make clean
```

---

## ▶️ Como Executar

Após compilar, execute:

```bash
./cinecapi        # Linux / Mac
cinecapi.exe      # Windows
```

O menu interativo será exibido. Use os números para navegar.

---

## 🎮 Exemplo de Uso

```
=========================================
      CineCapi - Sistema de Ingressos    
=========================================
  Fila de compra : 0 cliente(s)
  Interestelar        : 0 ingresso(s) | 0 na sala
  Perdido em Marte    : 0 ingresso(s) | 0 na sala
  Hail Mary Project   : 0 ingresso(s) | 0 na sala
-----------------------------------------
  [1] Preencher fila de clientes (auto)
  [2] Preencher pilhas de ingressos (auto)
  [3] Vender ingresso (escolher filme)
  ...
  [0] Sair
-----------------------------------------
  Opcao: 1
```

Após preencher os dados, escolha a opção `3`, selecione o filme e veja a venda acontecer!

---

## 👥 Autores

- **Caio Federico Esquivel Lovera Arze**
- **Lucas Toterol Rodrigues**

*Estudo Dirigido – 1º Bimestre – Estruturas de Dados*  
*Universidade Tuiuti do Paraná – 2026*

---

## 📄 Licença

Este projeto é para fins educacionais. Sinta-se livre para estudar e modificar.

---
