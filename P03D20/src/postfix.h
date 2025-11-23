#ifndef POSTFIX
#define POSTFIX

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "option.h"
#include "stack.h"

int priority(const char *oper);
void number_or_variable(option **postfix_option, int *num_postfix_option, const option *current_option);
void convert_unary_minus_to_postfix(option *infix_option, option **postfix_option, int *num_postfix_option,
                                    int *i);
void process_binary_operator(stack *operator_stack, option **postfix_option, int *num_postfix_option,
                             const option *current_option);
void closing_bkt(stack *operator_stack, option **postfix_option, int *num_postfix_option);
void infix_to_postfix(option *infix_option, int num_infix_option, option **postfix_option,
                      int *num_postfix_option);

char *double_to_string(double num);
void push_xvalue(const option *option, stack *operand_stack, double x);
void apply_operator(const option *option, stack *operand_stack);
void apply_math_function(const option *option, stack *operand_stack);
double calculation(const option *options, int option_count, double x);

#endif
