CC = gcc
CFLAGS = -Wall -g
TARGET = cinema
OBJS = main.o fila.o pilha.o ingresso.o cliente.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)