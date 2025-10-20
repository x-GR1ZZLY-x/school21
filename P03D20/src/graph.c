#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "option.h"
#include "parse.h"
#include "postfix.h"

#define HEIGHT 25
#define WIDTH 80

void fill_graph(int matrix[HEIGHT][WIDTH]);

void create_graphic(int matrix[HEIGHT][WIDTH], const option *postfix_options, int num_postfix_options);

void print_graph(int matrix[HEIGHT][WIDTH]);

int main() {
    int error = 0;
    char equation[100];

    printf("Введите выражение: ");
    if (fgets(equation, sizeof(equation), stdin) != NULL) {
        int len = strlen(equation);
        if (len > 0 && equation[len - 1] == '\n') {
            equation[len - 1] = '\0';
        }

        option *infix_options = NULL;
        int num_infix_options = 0;

        if (parse_expression(equation, &infix_options, &num_infix_options)) {
            error = 1;
        }

        if (!error) {
            option *postfix_options = NULL;
            int num_postfix_options = 0;

            infix_to_postfix(infix_options, num_infix_options, &postfix_options, &num_postfix_options);

            if (num_postfix_options == 0 || postfix_options == NULL) {
                error = 1;
            }

            if (!error) {
                int graphic_matrix[HEIGHT][WIDTH];
                fill_graph(graphic_matrix);
                create_graphic(graphic_matrix, postfix_options, num_postfix_options);
                print_graph(graphic_matrix);

                free(postfix_options);
            }
        }
        free(infix_options);
    } else {
        error = 1;
    }

    if (error) printf("n/a");
    return 0;
}

void fill_graph(int matrix[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            matrix[i][j] = '.';
        }
    }
}

void create_graphic(int matrix[HEIGHT][WIDTH], const option *postfix_options, int num_postfix_options) {
    int _break = 1;
    for (int i = 0; i < WIDTH && _break; i++) {
        double x = (i * 4.0 * M_PI) / (WIDTH - 1);
        double res = calculation(postfix_options, num_postfix_options, x);

        int y = (int)round((res + 1.0) * 12);
        if (y >= 0 && y < HEIGHT) {
            matrix[HEIGHT - 1 - y][i] = '*';
        }
    }
}

void print_graph(int matrix[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", matrix[i][j]);
        }
        printf("\n");
    }
}