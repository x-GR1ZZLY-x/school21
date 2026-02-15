#ifndef PROCESS_FILES_H
#define PROCESS_FILES_H

#include "parser.h"

typedef struct {
  CatFlags flags;
} CatContext;

void PrintChar(int ch, CatFlags *flags);

void Printing(int *is_line_start, int ch, int line_number, int is_current_empty,
              CatFlags *flags);

void LineNumber(int ch, int *line_number, int *is_line_start,
                int is_current_empty, CatFlags *flags);

void ProcessStream(FILE *file, void *context);

/*void ProcessFile(char *name, CatFlags *flags);

void ProcessFiles(int argc, char **argv, int start, CatFlags *flags);*/

#endif