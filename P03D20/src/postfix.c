#include "postfix.h"

int priority(const char *oper) {
    int p = 0;
    if (strcmp(oper, "+") == 0 || strcmp(oper, "-") == 0) {
        p = 1;
    } else if (strcmp(oper, "*") == 0 || strcmp(oper, "/") == 0) {
        p = 2;
    } else if (strcmp(oper, "sin") == 0 || strcmp(oper, "cos") == 0 || strcmp(oper, "tan") == 0 ||
               strcmp(oper, "ctg") == 0 || strcmp(oper, "sqrt") == 0 || strcmp(oper, "ln") == 0) {
        p = 2;
    }
    return p;
}

void number_or_variable(option **postfix_option, int *num_postfix_option, const option *current_option) {
    (*num_postfix_option)++;
    *postfix_option = (option *)realloc(*postfix_option, sizeof(option) * (*num_postfix_option));
    (*postfix_option)[(*num_postfix_option) - 1] = *current_option;
}

void convert_unary_minus_to_postfix(option *infix_option, option **postfix_option, int *num_postfix_option,
                                    int *i) {
    const option *next_option = &infix_option[*i + 1];

    if (next_option->type == OPT_BKT_OPEN && infix_option[*i + 2].elements[0] == '#') {
        *i = *i + 2;
    } else if (next_option->type == OPT_BKT_OPEN &&
               (infix_option[*i + 2].type == OPT_NUM || infix_option[*i + 2].type == OPT_VAR)) {
        char new_elements[50];
        new_elements[0] = '-';

        for (int j = 1; infix_option[*i + 2].elements[j - 1] != '\0'; j++) {
            new_elements[j] = infix_option[*i + 2].elements[j - 1];
            if (infix_option[*i + 2].elements[j - 1] == '\0') {
                new_elements[j + 1] = '\0';
            }
        }

        (*num_postfix_option)++;
        *postfix_option = (option *)realloc(*postfix_option, sizeof(option) * (*num_postfix_option));
        (*postfix_option)[(*num_postfix_option) - 1].type = infix_option[*i + 2].type;
        strcpy((*postfix_option)[(*num_postfix_option) - 1].elements, new_elements);
        *i = *i + 2;
    } else if (next_option->elements[0] == '#') {
        *i = *i + 1;
    }

    if (next_option->type == OPT_NUM || next_option->type == OPT_VAR) {
        char new_elements[50];
        new_elements[0] = '-';

        for (int j = 1; next_option->elements[j - 1] != '\0'; j++) {
            new_elements[j] = next_option->elements[j - 1];

            if (next_option->elements[j - 1] == '\0') {
                new_elements[j + 1] = '\0';
            }
        }

        (*num_postfix_option)++;
        *postfix_option = (option *)realloc(*postfix_option, sizeof(option) * (*num_postfix_option));
        (*postfix_option)[(*num_postfix_option) - 1].type = next_option->type;
        strcpy((*postfix_option)[(*num_postfix_option) - 1].elements, new_elements);
        *i = *i + 1;
    }
}

void process_binary_operator(stack *operator_stack, option **postfix_option, int *num_postfix_option,
                             const option *current_option) {
    while (!empty_stack(operator_stack) &&
           priority(top_stack(operator_stack)) >= priority(current_option->elements) &&
           strcmp(top_stack(operator_stack), "(") != 0) {
        char *oper = pop_stack(operator_stack);
        (*num_postfix_option)++;
        *postfix_option = (option *)realloc(*postfix_option, sizeof(option) * (*num_postfix_option));
        (*postfix_option)[(*num_postfix_option) - 1].type = OPT_OPERATOR;
        strcpy((*postfix_option)[(*num_postfix_option) - 1].elements, oper);
        free(oper);
    }

    push_stack(operator_stack, current_option->elements);
}

void closing_bkt(stack *operator_stack, option **postfix_option, int *num_postfix_option) {
    while (!empty_stack(operator_stack) && strcmp(top_stack(operator_stack), "(") != 0) {
        char *oper = pop_stack(operator_stack);
        (*num_postfix_option)++;
        *postfix_option = (option *)realloc(*postfix_option, sizeof(option) * (*num_postfix_option));
        (*postfix_option)[(*num_postfix_option) - 1].type = OPT_OPERATOR;
        strcpy((*postfix_option)[(*num_postfix_option) - 1].elements, oper);
        free(oper);
    }

    char *oper2 = pop_stack(operator_stack);
    free(oper2);

    if (!empty_stack(operator_stack) && top_stack(operator_stack)[0] != '(') {
        if (strcmp(top_stack(operator_stack), "sin") == 0 || strcmp(top_stack(operator_stack), "cos") == 0 ||
            strcmp(top_stack(operator_stack), "tan") == 0 || strcmp(top_stack(operator_stack), "ctg") == 0 ||
            strcmp(top_stack(operator_stack), "sqrt") == 0 || strcmp(top_stack(operator_stack), "ln") == 0) {
            char *func = pop_stack(operator_stack);
            (*num_postfix_option)++;
            *postfix_option = (option *)realloc(*postfix_option, sizeof(option) * (*num_postfix_option));
            (*postfix_option)[(*num_postfix_option) - 1].type = OPT_FUNC;
            strcpy((*postfix_option)[(*num_postfix_option) - 1].elements, func);
            free(func);
        }
    }
}

void infix_to_postfix(option *infix_option, int num_infix_option, option **postfix_option,
                      int *num_postfix_option) {
    stack operator_stack;
    init_stack(&operator_stack, num_infix_option);

    for (int i = 0; i < num_infix_option; i++) {
        const option *current_option = &infix_option[i];
        if (current_option->type == OPT_NUM || current_option->type == OPT_VAR) {
            number_or_variable(postfix_option, num_postfix_option, current_option);
        } else if (current_option->type == OPT_OPERATOR) {
            if (current_option->elements[0] == '#') {
                convert_unary_minus_to_postfix(infix_option, postfix_option, num_postfix_option, &i);
            } else {
                process_binary_operator(&operator_stack, postfix_option, num_postfix_option, current_option);
            }
        } else if (current_option->type == OPT_FUNC) {
            push_stack(&operator_stack, current_option->elements);
        } else if (current_option->type == OPT_BKT_OPEN) {
            push_stack(&operator_stack, current_option->elements);
        } else if (current_option->type == OPT_BKT_CLOSE) {
            closing_bkt(&operator_stack, postfix_option, num_postfix_option);
        }
    }

    while (!empty_stack(&operator_stack)) {
        char *oper = pop_stack(&operator_stack);
        (*num_postfix_option)++;
        *postfix_option = (option *)realloc(*postfix_option, sizeof(option) * (*num_postfix_option));
        (*postfix_option)[(*num_postfix_option) - 1].type = OPT_OPERATOR;
        strcpy((*postfix_option)[(*num_postfix_option) - 1].elements, oper);
        free(oper);
    }

    destroy_stack(&operator_stack);
}

char *double_to_string(double num) {
    char *str = (char *)malloc(20);
    snprintf(str, 20, "%lf", num);
    return str;
}

void push_xvalue(const option *option, stack *operand_stack, double x) {
    double elements = (option->elements[0] == '-') ? -x : x;
    char *temp_str = double_to_string(elements);
    push_stack(operand_stack, temp_str);
    free(temp_str);
}

void apply_operator(const option *option, stack *operand_stack) {
    double operand2 = atof(top_stack(operand_stack));
    char *oper = pop_stack(operand_stack);
    free(oper);

    double operand1 = atof(top_stack(operand_stack));
    char *oper2 = pop_stack(operand_stack);
    free(oper2);

    double result = 0.0;

    if (strcmp(option->elements, "+") == 0) {
        result = operand1 + operand2;
    } else if (strcmp(option->elements, "-") == 0) {
        result = operand1 - operand2;
    } else if (strcmp(option->elements, "*") == 0) {
        result = operand1 * operand2;
    } else if (strcmp(option->elements, "/") == 0) {
        result = operand1 / operand2;
    }

    char *result_str = double_to_string(result);
    push_stack(operand_stack, result_str);
    free(result_str);
}

void apply_math_function(const option *option, stack *operand_stack) {
    double operand = atof(top_stack(operand_stack));
    char *oper = pop_stack(operand_stack);
    free(oper);

    double result = 0.0;

    if (strcmp(option->elements, "sin") == 0) {
        result = sin(operand);
    } else if (strcmp(option->elements, "cos") == 0) {
        result = cos(operand);
    } else if (strcmp(option->elements, "tan") == 0) {
        result = tan(operand);
    } else if (strcmp(option->elements, "ctg") == 0) {
        result = 1.0 / tan(operand);
    } else if (strcmp(option->elements, "sqrt") == 0) {
        result = sqrt(operand);
    } else if (strcmp(option->elements, "ln") == 0) {
        result = log(operand);
    }

    char *result_str = double_to_string(result);
    push_stack(operand_stack, result_str);
    free(result_str);
}

double calculation(const option *options, int option_count, double x) {
    stack operand_stack;
    init_stack(&operand_stack, option_count);

    for (int i = 0; i < option_count; ++i) {
        const option *current_option = &options[i];
        switch (current_option->type) {
            case OPT_NUM:
                push_stack(&operand_stack, current_option->elements);
                break;
            case OPT_VAR:
                push_xvalue(current_option, &operand_stack, x);
                break;
            case OPT_OPERATOR:
                apply_operator(current_option, &operand_stack);
                break;
            case OPT_FUNC:
                apply_math_function(current_option, &operand_stack);
                break;
            default:
                break;
        }
    }

    double result = atof(top_stack(&operand_stack));
    char *result_str = pop_stack(&operand_stack);
    free(result_str);

    destroy_stack(&operand_stack);

    return result;
}
