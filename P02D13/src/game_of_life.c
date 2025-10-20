#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXROWS 25
#define MAXCOLS 80

void read_from_file(const char *filename, int *current);
void input(int ch, int *delay);
void neighbourhood(int *current, int *next);
void field(int *field, int n, int m);
void current_to_next(int *current, int *next);
void output(int *current);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }
    int current[MAXROWS][MAXCOLS];
    int next[MAXROWS][MAXCOLS];
    int delay = 600;
    int last_key = ERR;
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);
    read_from_file(argv[1], &current[0][0]);
    while (1) {
        neighbourhood(&current[0][0], &next[0][0]);
        output(&next[0][0]);
        current_to_next(&current[0][0], &next[0][0]);
        printw("\n%d", delay);
        refresh();

        int elapsed = 0;
        int ch = ERR;

        while (elapsed < delay) {
            ch = getch();
            if (ch == ' ') break;
            if ((ch == 'A' || ch == 'Z' || ch == 'a' || ch == 'z') && last_key == ERR) {
                last_key = ch;
            }
            napms(10);
            elapsed += 10;
        }
        if (ch == ' ') {
            break;
        }
        if (last_key != ERR) {
            input(last_key, &delay);
            last_key = ERR;
        }
    }
    endwin();
    return 0;
}

void input(int ch, int *delay) {
    if ((ch == 'A' || ch == 'a') && *delay > 100) {
        *delay -= 100;
    }
    if ((ch == 'Z' || ch == 'z') && *delay < 2000) {
        *delay += 100;
    }
}

void read_from_file(const char *filename, int *current) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        endwin();
        fprintf(stderr, "Не удалось открыть файл: %s\n", filename);
        exit(1);
    }
    int count = 0;
    for (int i = 0; i < MAXROWS; ++i) {
        for (int j = 0; j < MAXCOLS; ++j) {
            int ch;
            do {
                ch = fgetc(fp);
                if (ch == EOF) {
                    endwin();
                    fprintf(stderr, "Ошибка: недостаточно символов в файле");
                    fclose(fp);
                    exit(1);
                }
            } while (ch != '0' && ch != '1');
            *(current + i * MAXCOLS + j) = (ch == '1') ? 1 : 0;
            count++;
        }
    }

    int extra;
    while ((extra = fgetc(fp)) != EOF) {
        if (extra == '0' || extra == '1') {
            endwin();
            fprintf(stderr, "Ошибка: файл содержит лишние символы");
            fclose(fp);
            exit(1);
        }
    }
    fclose(fp);
}

void neighbourhood(int *current, int *next) {
    for (int y = 0; y < MAXROWS; ++y) {
        for (int x = 0; x < MAXCOLS; ++x) {
            int neighbours = 0;
            for (int dy = -1; dy <= 1; dy++) {
                for (int dx = -1; dx <= 1; dx++) {
                    if (dy == 0 && dx == 0) continue;
                    int ny = (y + dy + MAXROWS) % MAXROWS;
                    int nx = (x + dx + MAXCOLS) % MAXCOLS;
                    if (*(current + ny * MAXCOLS + nx)) neighbours++;
                }
            }
            if (*(current + y * MAXCOLS + x) == 1) {
                *(next + y * MAXCOLS + x) = (neighbours == 2 || neighbours == 3) ? 1 : 0;
            } else {
                *(next + y * MAXCOLS + x) = (neighbours == 3) ? 1 : 0;
            }
        }
    }
}

void current_to_next(int *current, int *next) {
    for (int i = 0; i < MAXROWS; ++i) {
        for (int j = 0; j < MAXCOLS; ++j) {
            *(current + i * MAXCOLS + j) = *(next + i * MAXCOLS + j);
        }
    }
}

void output(int *current) {
    clear();
    for (int i = 0; i < MAXROWS; ++i) {
        for (int j = 0; j < MAXCOLS; ++j) {
            mvaddch(i, j, *(current + i * MAXCOLS + j) ? '*' : ' ');
        }
    }
}