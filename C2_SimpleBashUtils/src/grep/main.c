#include "../common/file_utils.h"
#include "parser.h"
#include "process_files.h"

int main(int argc, char **argv) {
  ParseResult result;
  int first_file = Parsing(&result, argc, argv);
  int error = 0;
  if (!result.pattern) {
    error = 1;
  }

  if (!error && first_file < argc) {
    GrepContext ctx;
    ctx.options = &result;
    ctx.many_files = 0;
    ctx.filename = NULL;

    if (argc - first_file > 1) {
      ctx.many_files = 1;
    }
    error = CompileRegex(&ctx);

    if (!error) {
      ProcessFiles(argc, argv, first_file, GrepProcessStream,
                   GrepBeforeFileHook, &ctx);
      FreeRegex(&ctx);
    }

  } else {
    error = 1;
  }
  return error;
}