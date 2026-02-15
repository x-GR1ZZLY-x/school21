#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>

typedef void (*StreamProcessor)(FILE *file, void *context);

typedef void (*BeforeFileHook)(const char *filename, void *context);

void ProcessFile(const char *name, StreamProcessor processor, void *context);

void ProcessFiles(int argc, char **argv, int start_index,
                  StreamProcessor processor, BeforeFileHook before,
                  void *context);

#endif