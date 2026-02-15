CC = gcc
CFLAGS = -Wall -Wextra -Werror -std=c11
SRCS = main.c parser.c process_files.c ../common/file_utils.c
OBJS = $(SRCS:.c=.o)
TARGET = s21_grep

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild
