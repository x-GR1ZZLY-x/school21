#include "process_files.h"

void GrepBeforeFileHook(const char *filename, void *context) {
  GrepContext *ctx = (GrepContext *)context;
  ctx->filename = filename;
  ctx->match_count = 0;
}

int CompileRegex(GrepContext *ctx) {
  int error = 0;
  int flags = REG_EXTENDED;

  if (ctx->options->ignore_case) {
    flags |= REG_ICASE;
  }

  if (regcomp(&ctx->regex, ctx->options->pattern, flags) != 0) {
    error = 1;
  }

  return error;
}

void FreeRegex(GrepContext *ctx) { regfree(&ctx->regex); }

int MatchLine(GrepContext *ctx, char *line) {
  int matched = (regexec(&ctx->regex, line, 0, NULL, 0) == 0);

  if (ctx->options->invert) {
    matched = !matched;
  }

  return matched;
}

void OutputLine(GrepContext *ctx, char *line, int line_number) {
  if (ctx->many_files) {
    printf("%s:", ctx->filename);
  }
  if (ctx->options->line_number) {
    printf("%d:", line_number);
  }
  printf("%s", line);
  size_t len = strlen(line);
  if (len == 0 || line[len - 1] != '\n') {
    printf("\n");
  }
}

void Output(GrepContext *ctx) {
  if (ctx->options->list_files) {
    printf("%s\n", ctx->filename);
  } else {
    if (ctx->many_files) {
      printf("%s:", ctx->filename);
    }
    if (ctx->options->count && !ctx->options->list_files) {
      printf("%d\n", ctx->match_count);
    }
  }
}

void GrepProcessStream(FILE *file, void *context) {
  GrepContext *ctx = context;
  char buffer[1024];
  int matched = 0;
  int line_counter = 0;
  while (fgets(buffer, sizeof(buffer), file) != NULL) {
    ++line_counter;
    matched = (MatchLine(ctx, buffer));
    if (matched) {
      ctx->match_count += 1;
    }
    if (matched && !ctx->options->count && !ctx->options->list_files) {
      OutputLine(ctx, buffer, line_counter);
    }
  }
  if (ctx->options->count ||
      (ctx->options->list_files && ctx->match_count > 0)) {
    Output(ctx);
  }
}