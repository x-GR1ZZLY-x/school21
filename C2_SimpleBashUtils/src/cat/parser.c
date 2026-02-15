#include "parser.h"

int ParseLong(char *arg, CatFlags *f) {
  int flag = 0;
  if (strcmp(arg, "--number") == 0) {
    f->number = 1;
  } else if (strcmp(arg, "--number-nonblank") == 0) {
    f->number_nonblank = 1;
    f->number = 0;
  } else if (strcmp(arg, "--squeeze-blank") == 0) {
    f->squeeze_blank = 1;
  } else {
    fprintf(stderr, "invalid option '%s'\n", arg);
    flag = 1;
  }
  return flag;
}

int ParseShort(char *arg, CatFlags *f) {
  int flag = 0;
  for (int j = 1; arg[j]; j++) {
    switch (arg[j]) {
      case 'b':
        f->number_nonblank = 1;
        f->number = 0;
        break;
      case 'n':
        if (f->number_nonblank == 0) f->number = 1;
        break;
      case 's':
        f->squeeze_blank = 1;
        break;
      case 'e':
        f->show_ends = 1;
        f->show_nonprinting = 1;
        break;
      case 'E':
        f->show_ends = 1;
        break;
      case 't':
        f->show_tabs = 1;
        f->show_nonprinting = 1;
        break;
      case 'T':
        f->show_tabs = 1;
        break;
      case 'v':
        f->show_nonprinting = 1;
        break;
      default:
        fprintf(stderr, "invalid option '%c'\n", arg[j]);
        flag = 1;
        break;
    }
  }
  return flag;
}

int ParseFlags(int argc, char **argv, CatFlags *f) {
  *f = (CatFlags){0};
  int i = 1;
  int flag = 0;    // ошибка
  int result = 1;  // первый файл
  int stop = 0;    // дальше флагов нет

  while (i < argc && !flag && !stop && argv[i][0] == '-' && argv[i][1]) {
    if (strcmp(argv[i], "--") == 0) {
      result = i + 1;
      stop = 1;
    } else if (argv[i][1] == '-') {
      if (ParseLong(argv[i], f) == 1) flag = 1;
    } else {
      if (ParseShort(argv[i], f) == 1) flag = 1;
    }
    i++;
  }

  if (flag) {
    result = argc;
  } else if (result == 1) {
    result = i;
  }

  return result;
}