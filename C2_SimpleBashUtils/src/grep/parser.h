#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int ignore_case;   // -i
  int invert;        // -v
  int count;         // -c
  int list_files;    // -l
  int line_number;   // -n
  int pattern_flag;  // -e
  char *pattern;
} ParseResult;

int ParseFlags(ParseResult *result, char *argv);

int AppendPattern(ParseResult *result, char *new_pattern);

void Normalization(ParseResult *result);

int Parsing(ParseResult *result, int argc, char **argv);

#endif