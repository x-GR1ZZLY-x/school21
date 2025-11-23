#include "parse.h"

int is_operator(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }

int my_isdigit(char c) { return (c >= '0' && c <= '9'); }

int my_isalpha(char c) { return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')); }

void handle_number(const char *expr, option **opts, int *num_opts, int *i) {
    char num[50] = {'\0'};
    int j = 0;
    int dot_count = 0;
    int error = 0;
    int _break = 0;

    while ((my_isdigit(expr[*i]) || expr[*i] == '.') && !_break) {
        if (expr[*i] == '.') dot_count++;
        if (dot_count > 1 || j >= 49) _break = 1;
        num[j++] = expr[(*i)++];
    }

    if (j == 0 || (j == 1 && num[0] == '.')) error = 1;

    if (!error) {
        num[j] = '\0';

        (*num_opts)++;
        option *tmp = (option *)realloc(*opts, sizeof(option) * (*num_opts));
        if (tmp == NULL) return;
        *opts = tmp;

        (*opts)[(*num_opts) - 1].type = OPT_NUM;
        strcpy((*opts)[(*num_opts) - 1].elements, num);
        (*opts)[(*num_opts) - 1].elements[j] = '\0';
    }
}

void handle_unary_minus(option **opts, int *num_opts, int *i) {
    (*num_opts)++;
    option *tmp = (option *)realloc(*opts, sizeof(option) * (*num_opts));
    if (tmp == NULL) return;
    *opts = tmp;

    (*opts)[(*num_opts) - 1].type = OPT_OPERATOR;
    strcpy((*opts)[(*num_opts) - 1].elements, "#");
    (*i)++;
}

void handle_operator(const char *expr, option **opts, int *num_opts, int *i) {
    (*num_opts)++;
    option *tmp = (option *)realloc(*opts, sizeof(option) * (*num_opts));
    if (tmp == NULL) return;
    *opts = tmp;

    (*opts)[(*num_opts) - 1].type = OPT_OPERATOR;
    (*opts)[(*num_opts) - 1].elements[0] = expr[*i];
    (*opts)[(*num_opts) - 1].elements[1] = '\0';
    (*i)++;
}

void handle_open_bracket(option **opts, int *num_opts, int *i) {
    (*num_opts)++;
    option *tmp = (option *)realloc(*opts, sizeof(option) * (*num_opts));
    if (tmp == NULL) return;
    *opts = tmp;

    (*opts)[(*num_opts) - 1].type = OPT_BKT_OPEN;
    strcpy((*opts)[(*num_opts) - 1].elements, "(");
    (*i)++;
}

void handle_close_bracket(option **opts, int *num_opts, int *i) {
    (*num_opts)++;
    option *tmp = (option *)realloc(*opts, sizeof(option) * (*num_opts));
    if (tmp == NULL) return;
    *opts = tmp;

    (*opts)[(*num_opts) - 1].type = OPT_BKT_CLOSE;
    strcpy((*opts)[(*num_opts) - 1].elements, ")");
    (*i)++;
}

void handle_function_or_variable(const char *expr, option **opts, int *num_opts, int *i) {
    char id[50] = {'\0'};
    int j = 0;
    int error = 0;

    while (expr[*i] && my_isalpha(expr[*i]) && j < 49) {
        id[j++] = expr[(*i)++];
    }
    id[j] = '\0';

    if (j == 0) error = 1;

    if (!error) {
        (*num_opts)++;
        option *tmp = (option *)realloc(*opts, sizeof(option) * (*num_opts));
        if (tmp == NULL) error = 1;
        if (!error) *opts = tmp;
    }

    if (!error) {
        if (strcmp(id, "sin") == 0 || strcmp(id, "cos") == 0 || strcmp(id, "tan") == 0 ||
            strcmp(id, "ctg") == 0 || strcmp(id, "sqrt") == 0 || strcmp(id, "ln") == 0) {
            (*opts)[(*num_opts) - 1].type = OPT_FUNC;
        } else if (strcmp(id, "x") == 0) {
            (*opts)[(*num_opts) - 1].type = OPT_VAR;
        } else {
            (*num_opts)--;
            return;
        }
        strcpy((*opts)[(*num_opts) - 1].elements, id);
        (*opts)[(*num_opts) - 1].elements[j] = '\0';
    }
}

int process_expression_loops(const char *expr, option **opts, int *num_opts, int *error, int *bracket_count) {
    int i = 0;
    while (expr[i] != '\0' && !*error) {
        if (expr[i] == ' ') {
            (i)++;
        } else if (my_isdigit(expr[i]) || expr[i] == '.') {
            int prev = *num_opts;
            handle_number(expr, opts, num_opts, &i);
            if (*num_opts == prev) *error = 1;
        } else if (expr[i] == '-' && (i == 0 || expr[i - 1] == '(' || is_operator(expr[i - 1]))) {
            int prev = *num_opts;
            handle_unary_minus(opts, num_opts, &i);
            if (*num_opts == prev) *error = 1;
        } else if (is_operator(expr[i])) {
            int prev = *num_opts;
            handle_operator(expr, opts, num_opts, &i);
            if (*num_opts == prev) *error = 1;
        } else if (expr[i] == '(') {
            (*bracket_count)++;
            int prev = *num_opts;
            handle_open_bracket(opts, num_opts, &i);
            if (*num_opts == prev) *error = 1;
        } else if (expr[i] == ')') {
            (*bracket_count)--;
            if (*bracket_count < 0) *error = 1;
            int prev = *num_opts;
            handle_close_bracket(opts, num_opts, &i);
            if (*num_opts == prev) *error = 1;
        } else if (my_isalpha(expr[i])) {
            int prev = *num_opts;
            handle_function_or_variable(expr, opts, num_opts, &i);
            if (*num_opts == prev) *error = 1;
        } else {
            *error = 1;
        }
    }
    return *error;
}

int parse_expression(const char *expr, option **opts, int *num_opts) {
    int error = 0;
    int bracket_count = 0;

    process_expression_loops(expr, opts, num_opts, &error, &bracket_count);

    if (bracket_count != 0) {
        error = 1;
    }

    if (*num_opts == 0) {
        error = 1;
    }

    if (error && *opts) {
        free(*opts);
        *opts = NULL;
        *num_opts = 0;
    }

    return error;
}
