#include "../common/file_utils.h"
#include "process_files.h"

int main(int argc, char **argv) {
  CatContext ctx;
  int first_file = ParseFlags(argc, argv, &ctx.flags);
  if (first_file < argc) {
    ProcessFiles(argc, argv, first_file, ProcessStream, NULL, &ctx);
  }

  return 0;
}