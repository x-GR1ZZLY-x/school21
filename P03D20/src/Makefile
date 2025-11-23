CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = graph.c parse.c postfix.c stack.c 
TARGET = ../build/graph

all:
	$(CC) -o $(TARGET) $(SRC) $(CFLAGS)

run:
	./$(TARGET)

clean:
	rm -rf $(TARGET)