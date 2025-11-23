#ifndef OPTION_H
#define OPTION_H

typedef enum {
    OPT_NUM,       // числа
    OPT_OPERATOR,  // операторы
    OPT_FUNC,      // функции
    OPT_VAR,       // переменные
    OPT_BKT_OPEN,  // открывающая скобка
    OPT_BKT_CLOSE  // закрывающая скобка
} option_type;

typedef struct {
    option_type type;
    char elements[50];
} option;

#endif