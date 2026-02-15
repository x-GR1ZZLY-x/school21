#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <string.h>

typedef struct {
  int number;
  int number_nonblank;
  int squeeze_blank;
  int show_ends;
  int show_tabs;
  int show_nonprinting;
} CatFlags;

int ParseLong(char *arg, CatFlags *f);

int ParseShort(char *arg, CatFlags *f);

int ParseFlags(int argc, char **argv, CatFlags *f);

#endif