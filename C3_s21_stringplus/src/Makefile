CC = gcc
AR = ar
ARFLAGS = rcs

CFLAGS = -Wall -Wextra -Werror -std=c11 -O0 -g --coverage
LDFLAGS = --coverage -lcheck -lsubunit -lm

LIB_NAME = s21_string.a

SRCS = \
	./common/memory.c \
	./common/string_copy.c \
	./common/string_info.c \
	./common/string_search.c \
	./special/s21_special.c \
	./special/s21_insert.c \
	./special/s21_to_lower.c \
	./special/s21_to_upper.c \
	./special/s21_trim.c \
	./essential/convert.c \
	./essential/formatting.c \
	./essential/parser.c \
	./essential/s21_sprintf.c

OBJS = $(SRCS:.c=.o)

HDRS = \
	s21_string.h \
	./special/s21_hfileforspecial.h \
	./essential/s21_sprintf.h

TEST_SRCS = tests/string_test_full.c
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_BIN = test

all: $(LIB_NAME)

$(LIB_NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(LIB_NAME) $(TEST_OBJS)
	$(CC) $(CFLAGS) $(TEST_OBJS) $(LIB_NAME) $(LDFLAGS) -o $(TEST_BIN)
	-./$(TEST_BIN)

gcov_report: test
	gcovr \
	--root . \
	--filter ".*(common|special|essential)/.*\.c" \
	--exclude "tests" \
	--html-details \
	-o gcov_report.html

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(LIB_NAME) $(TEST_BIN)
	rm -f *.gcno *.gcda */*.gcno */*.gcda
	rm -f *.html *.css

rebuild: clean all

.PHONY: all clean rebuild test gcov_report
