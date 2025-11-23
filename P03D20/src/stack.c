#include "stack.h"

void init_stack(stack *stack, int size) {
    stack->data = (char **)malloc(size * sizeof(char *));
    stack->size = size;
    stack->top = -1;
}

void push_stack(stack *stack, const char *elem) {
    int success = 0;

    if (stack->top < stack->size - 1) {
        stack->top++;
        stack->data[stack->top] = (char *)malloc(strlen(elem) + 1);
        if (stack->data[stack->top]) {
            strcpy(stack->data[stack->top], elem);
            success = 1;
        }
    }

    if (!success && stack->top >= stack->size - 1) {
        int new_size = stack->size * 2;
        char **new_data = (char **)realloc(stack->data, new_size * sizeof(char *));
        if (new_data) {
            stack->data = new_data;
            stack->size = new_size;
            push_stack(stack, elem);
        }
    }
}

char *pop_stack(stack *stack) {
    char *elem = NULL;

    if (stack->top >= 0) {
        elem = stack->data[stack->top];
        stack->data[stack->top] = NULL;
        stack->top--;
    }

    return elem;
}

char *top_stack(stack *stack) {
    char *elem = NULL;

    if (stack->top >= 0) {
        elem = stack->data[stack->top];
    }

    return elem;
}

int empty_stack(stack *stack) { return stack->top == -1; }

void destroy_stack(stack *stack) {
    if (stack && stack->data) {
        for (int i = 0; i <= stack->top; i++) {
            if (stack->data[i]) {
                free(stack->data[i]);
            }
        }
        free(stack->data);
        stack->data = NULL;
        stack->top = -1;
        stack->size = 0;
    }
}