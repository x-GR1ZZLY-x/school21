#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <string.h>

typedef struct {
    char **data;
    int size;
    int top;
} stack;

void init_stack(stack *stack, int size);
void push_stack(stack *stack, const char *elem);
char *pop_stack(stack *stack);
char *top_stack(stack *stack);
int empty_stack(stack *stack);
void destroy_stack(stack *stack);

#endif