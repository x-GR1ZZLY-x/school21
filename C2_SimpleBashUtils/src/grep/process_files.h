#ifndef PROCESS_FILES_H
#define PROCESS_FILES_H

#include <regex.h>

#include "../common/file_utils.h"
#include "parser.h"

typedef struct {
  ParseResult *options;
  regex_t regex;
  int match_count;
  int many_files;
  const char *filename;
} GrepContext;

void GrepBeforeFileHook(const char *filename, void *context);

int CompileRegex(GrepContext *ctx);

void FreeRegex(GrepContext *ctx);

int MatchLine(GrepContext *ctx, char *line);

void OutputLine(GrepContext *ctx, char *line, int line_number);

void Output(GrepContext *ctx);

void GrepProcessStream(FILE *file, void *context);

#endif