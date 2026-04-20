CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -g
TARGET  = cinecapi

# Fontes em cada subdiretório
SRCS = main.c \
       queue_func/queue.c \
       stack_func/stack.c \
       system_fuc/system.c \
       ticket_func/ticket.c \
       user_func/user.c

OBJS = $(SRCS:.c=.o)

# Diretórios com headers
INCLUDES = -I. \
           -Iqueue_func \
           -Istack_func \
           -Isystem_fuc \
           -Iticket_func \
           -Iuser_func

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)
