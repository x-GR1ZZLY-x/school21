#include "process_files.h"

void PrintChar(int ch, CatFlags *flags) {
  if (flags->show_tabs && ch == '\t') {
    printf("^I");
  } else if (flags->show_ends && ch == '\n') {
    printf("$\n");
  } else if (flags->show_nonprinting && ch >= 0 && ch < 32 && ch != '\n' &&
             ch != '\t') {
    printf("^%c", ch + 64);
  } else {
    putchar(ch);
  }
}

void Printing(int *is_line_start, int ch, int line_number, int is_current_empty,
              CatFlags *flags) {
  if (*is_line_start) {
    if (flags->number ||
        (flags->number_nonblank && !is_current_empty)) {  //-n -b
      printf("%6d\t", line_number);
    }
    *is_line_start = 0;
  }
  PrintChar(ch, flags);  //-e -t -v
}

void LineNumber(int ch, int *line_number, int *is_line_start,
                int is_current_empty, CatFlags *flags) {
  if (ch == '\n') {
    if (!(flags->number_nonblank && is_current_empty)) {
      (*line_number)++;
    }
    *is_line_start = 1;
  }
}

void ProcessStream(FILE *file, void *context) {
  CatContext *ctx = (CatContext *)context;
  CatFlags *flags = &ctx->flags;
  int ch;
  int line_number = 1;    // номер строки
  int is_line_start = 1;  // флаг начало строки
  int is_prev_empty = 0;  // флаг предыдущая строка пустая
  int is_current_empty = 0;
  while ((ch = fgetc(file)) != EOF) {
    int char_for_print = 1;  // флаг символ надо печатать

    if (is_line_start && ch == '\n') {
      is_current_empty = 1;
    } else {
      is_current_empty = 0;
    }

    if (flags->squeeze_blank && ch == '\n' && is_prev_empty &&
        is_current_empty) {
      char_for_print = 0;
    }

    if (char_for_print) {
      Printing(&is_line_start, ch, line_number, is_current_empty, flags);
      LineNumber(ch, &line_number, &is_line_start, is_current_empty, flags);
    }

    is_prev_empty = is_current_empty;
  }
}

/*void ProcessFile(char *name, CatFlags *flags) {
  FILE *file = fopen(name, "r");
  if (!file) {
    fprintf(stderr, "Cannot open %s\n", name);
    return;
  }
  ProcessStream(file, flags);
  fclose(file);
}

void ProcessFiles(int argc, char **argv, int start, CatFlags *flags) {
  for (int i = start; i < argc; ++i) {
    ProcessFile(argv[i], flags);
  }
}*/