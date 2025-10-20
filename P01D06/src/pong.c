#include <stdio.h>

int leftr(int y, char left_ry) {
    if (left_ry == 'a' && y != 1) {
        y -= 1;
    } else if (left_ry == 'z' && y != 21) {
        y += 1;
    }
    return y;
}

int rightr(int y, char right_ry) {
    if (right_ry == 'k' && y != 1) {
        y -= 1;
    } else if (right_ry == 'm' && y != 21) {
        y += 1;
    }
    return y;
}

int pole(int l, int r, int ball_x, int ball_y, int lscore, int rscore) {
    for (int i = 0; i < 25; i++) {
        if (i == 0 || i == 24) {
            for (int j = 0; j < 80; j++) {
                printf("-");
                if (j == 79) {
                    printf("\n");
                }
            }
        } else {
            for (int j = 0; j < 80; j++) {
                if (i == ball_y && j == ball_x) {
                    printf("*");
                } else if ((j == 1 && (i == l || i == l + 1 || i == l + 2)) ||
                           (j == 78 && (i == r || i == r + 1 || i == r + 2))) {
                    printf("|");
                } else if (j == 39) {
                    printf("|");
                } else if (i == 4 && j == 35) {
                    printf("%d", lscore);
                } else if (i == 4 && j == 43) {
                    printf("%d", rscore);
                } else if (((lscore < 9) || (i != 4) || (j != 37)) &&
                           ((rscore < 9) || (i != 4) || (j != 45))) {
                    printf(" ");
                }
            }
            printf("\n");
        }
    }
    return 0;
}

int main() {
    int left_score = 0;
    int right_score = 0;
    int ball_x = 39;
    int ball_y = 13;
    int ball_xs = -1, ball_ys = 0;
    int left_ry = 12, right_ry = 12;
    int left_enter, right_enter, probel;

    pole(left_ry, right_ry, ball_x, ball_y, left_score, right_score);
    while (left_score != 21 && right_score != 21) {
        scanf("%lc%lc%lc%*c", &left_enter, &probel, &right_enter);

        printf("%d %d\n", left_enter, right_enter);

        if ((left_enter != 97 && left_enter != 122 && left_enter != 32) || (probel != 32) ||
            (right_enter != 107 && right_enter != 109 && right_enter != 32)) {
            return 1;
        }

        left_ry = leftr(left_ry, left_enter);
        right_ry = rightr(right_ry, right_enter);

        if (((ball_x) == 2) &&
            (((ball_y) != left_ry) || ((ball_y) != left_ry + 1) || ((ball_y) != left_ry + 2))) {
            right_score++;
            ball_x = 39;
            ball_y = 13;
            ball_xs = -1, ball_ys = 0;
            left_ry = 12, right_ry = 12;
        } else if (((ball_x + ball_xs) == 2) &&
                   (((ball_y + ball_ys) == left_ry) || ((ball_y + ball_ys) == left_ry + 1) ||
                    ((ball_y + ball_ys) == left_ry + 2)) &&
                   (ball_ys == 0 && (ball_y + ball_ys) == left_ry)) {
            ball_xs = -ball_xs;
            ball_ys = -1;
        } else if (((ball_x + ball_xs) == 2) &&
                   (((ball_y + ball_ys) == left_ry) || ((ball_y + ball_ys) == left_ry + 1) ||
                    ((ball_y + ball_ys) == left_ry + 2)) &&
                   (ball_ys == 0 && (ball_y + ball_ys) == (left_ry + 2))) {
            ball_xs = -ball_xs;
            ball_ys = 1;
        }

        else if (((ball_x + ball_xs) == 2) &&
                 (((ball_y + ball_ys) == left_ry) || ((ball_y + ball_ys) == left_ry + 1) ||
                  ((ball_y + ball_ys) == left_ry + 2))) {
            ball_xs = -ball_xs;
        }

        if (((ball_x) == 77) &&
            (((ball_y) != right_ry) || ((ball_y) != right_ry + 1) || ((ball_y) != right_ry + 2))) {
            ball_x = 39;
            ball_y = 13;
            ball_xs = 1, ball_ys = 0;
            left_ry = 12, right_ry = 12;
            left_score++;
        } else if (((ball_x + ball_xs) == 77) &&
                   (((ball_y + ball_ys) == right_ry) || ((ball_y + ball_ys) == right_ry + 1) ||
                    ((ball_y + ball_ys) == right_ry + 2)) &&
                   (ball_ys == 0 && (ball_y + ball_ys) == right_ry)) {
            ball_xs = -ball_xs;
            ball_ys = -1;
        } else if (((ball_x + ball_xs) == 77) &&
                   (((ball_y + ball_ys) == right_ry) || ((ball_y + ball_ys) == right_ry + 1) ||
                    ((ball_y + ball_ys) == right_ry + 2)) &&
                   (ball_ys == 0 && (ball_y + ball_ys) == (right_ry + 2))) {
            ball_xs = -ball_xs;
            ball_ys = 1;
        } else if (((ball_x + ball_xs) == 77) &&
                   (((ball_y + ball_ys) == left_ry) || ((ball_y + ball_ys) == left_ry + 1) ||
                    ((ball_y + ball_ys) == left_ry + 2))) {
            ball_xs = -ball_xs;
        }

        if (((ball_y + ball_ys) == 0) || ((ball_y + ball_ys) == 24)) {
            ball_ys = -ball_ys;
        }
        ball_x += ball_xs;
        ball_y += ball_ys;
        pole(left_ry, right_ry, ball_x, ball_y, left_score, right_score);
        printf("%d %d\n", left_enter, right_enter);
    }
    if (right_score == 21) {
        printf("Right player Win");
    } else if (left_score == 21) {
        printf("Left player Win");
    }

    return 0;
}
