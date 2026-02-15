#include "file_utils.h"

void ProcessFile(const char *name, StreamProcessor processor, void *context) {
  FILE *file = fopen(name, "r");

  if (file != NULL) {
    processor(file, context);
    fclose(file);
  } else {
    fprintf(stderr, "Cannot open %s\n", name);
  }
}

void ProcessFiles(int argc, char **argv, int start_index,
                  StreamProcessor processor, BeforeFileHook before,
                  void *context) {
  for (int i = start_index; i < argc; i++) {
    if (before != NULL) {
      before(argv[i], context);
    }

    ProcessFile(argv[i], processor, context);
  }
}