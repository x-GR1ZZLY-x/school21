#ifndef PARSE_H
#define PARSE_H

#include <stdlib.h>
#include <string.h>

#include "option.h"

int is_operator(char c);
int my_isdigit(char c);
int my_isalpha(char c);

void handle_number(const char *expr, option **opts, int *num_opts, int *i);
void handle_unary_minus(option **opts, int *num_opts, int *i);
void handle_operator(const char *expr, option **opts, int *num_opts, int *i);
void handle_open_bracket(option **opts, int *num_opts, int *i);
void handle_close_bracket(option **opts, int *num_opts, int *i);
void handle_function_or_variable(const char *expr, option **opts, int *num_opts, int *i);

int parse_expression(const char *expr, option **opts, int *num_opts);
int process_expression_loops(const char *expr, option **opts, int *num_opts, int *error, int *bracket_count);

#endif
