CC = gcc
AR = ar
ARFLAGS = rcs

CFLAGS = -Wall -Wextra -Werror -std=c11
GCOV_FLAGS = -O0 -g --coverage
LDFLAGS = --coverage -lcheck -lsubunit -lm

LIB_NAME = s21_decimal.a

SRCS = operations/s21_add_and_sub.c \
       operations/s21_mul.c \
	   operations/s21_div.c \
       converters/s21_from_int_to_decimal.c \
       converters/s21_from_float_to_decimal.c \
       converters/s21_from_decimal_to_int.c \
       converters/s21_from_decimal_to_float.c \
       others_functions/s21_negate.c \
       others_functions/s21_truncate.c \
       others_functions/s21_floor_round.c \
	   comparison/s21_compare_functions.c \
	   comparison/s21_help_functions.c 

OBJS = $(SRCS:.c=.o)

HDRS = s21_decimal.h

TEST_SRCS = tests/s21_decimal_tests.c
TEST_OBJS = $(TEST_SRCS:.c=.o)
TEST_BIN = test

all: $(LIB_NAME)

$(LIB_NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(LIB_NAME) $(TEST_OBJS)
	$(CC) $(GCOV_FLAGS) $(TEST_OBJS) $(LIB_NAME) $(LDFLAGS) -o $(TEST_BIN)
	-./$(TEST_BIN)

gcov_report: clean
	for src in $(SRCS); do \
		dir=$$(dirname $$src); \
		base=$$(basename $$src .c); \
		$(CC) $(GCOV_FLAGS) -c $$src -o $$dir/$$base.gcov.o; \
	done
	$(AR) $(ARFLAGS) $(LIB_NAME).cov.a \
		$(foreach src,$(SRCS),$(dir $(src))$(notdir $(basename $(src))).gcov.o)
	$(CC) $(GCOV_FLAGS) $(TEST_SRCS) $(LIB_NAME).cov.a $(LDFLAGS) -o $(TEST_BIN)
	-./$(TEST_BIN)
	gcovr --root . --filter ".*\.c" --exclude "tests" --html-details -o gcov_report.html

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(LIB_NAME) $(TEST_BIN)
	rm -f $(LIB_NAME).cov.a
	rm -f *.gcno *.gcda
	rm -f operations/*.gcno operations/*.gcda operations/*.gcov.o
	rm -f comparison/*.gcno comparison/*.gcda comparison/*.gcov.o
	rm -f converters/*.gcno converters/*.gcda converters/*.gcov.o
	rm -f others_functions/*.gcno others_functions/*.gcda others_functions/*.gcov.o
	rm -f tests/*.gcno tests/*.gcda tests/*.o
	rm -f *.html *.css

rebuild: clean all

.PHONY: all clean rebuild test gcov_report