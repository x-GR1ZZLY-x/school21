#include "parser.h"

int ParseFlags(ParseResult *result, char *argv) {
  int error = 0;
  int j = 1;
  while (argv[j] && !error) {
    switch (argv[j]) {
      case 'i':
        result->ignore_case = 1;
        break;
      case 'v':
        result->invert = 1;
        break;
      case 'c':
        result->count = 1;
        break;
      case 'l':
        result->list_files = 1;
        break;
      case 'n':
        result->line_number = 1;
        break;
      case 'e':
        result->pattern_flag = 1;
        break;
      default:
        error = 1;
        fprintf(stderr, "invalid option '%c'\n", argv[j]);
        break;
    }
    ++j;
  }
  return error;
}

int AppendPattern(ParseResult *result, char *new_pattern) {
  int error = 0;
  int not_first_pattern = 0;
  char *temp = NULL;
  if (new_pattern == NULL || result == NULL) {
    fprintf(stderr, "invalid pattern\n");
    error = 1;
  } else {
    not_first_pattern = (result->pattern != NULL);
  }
  if (!error && !not_first_pattern) {
    size_t len = strlen(new_pattern) + 3;
    temp = malloc(len);
    if (temp == NULL) {
      error = 1;
    } else {
      snprintf(temp, len, "(%s)", new_pattern);
    }
  } else if (!error && not_first_pattern) {
    size_t len = strlen(new_pattern) + 3;
    size_t old_len = strlen(result->pattern);
    temp = realloc(result->pattern, old_len + len);
    if (temp == NULL) {
      error = 1;
      free(result->pattern);
      result->pattern = NULL;
    } else {
      snprintf(temp + old_len - 1, len, "|%s)", new_pattern);
    }
  }
  if (!error) {
    result->pattern = temp;
  }

  return error;
}

void Normalization(ParseResult *result) {
  if (result->list_files == 1) {
    result->count = 0;
    result->line_number = 0;
  }
  if (result->count == 1) {
    result->line_number = 0;
  }
}

int Parsing(ParseResult *result, int argc, char **argv) {
  *result = (ParseResult){0};
  int i = 1;
  int error = 0;
  int first_file = argc;
  int has_pattern = 0;
  while (i < argc && !error && first_file == argc) {
    int is_double_dash = (strcmp(argv[i], "--") == 0);
    int is_flag = (argv[i][0] == '-' && argv[i][1] != '\0' && !is_double_dash);
    result->pattern_flag = 0;
    result->pattern_flag = (is_flag && argv[i][1] == 'e');
    if (is_double_dash) {
      if (i + 1 < argc && !has_pattern) {
        error = AppendPattern(result, argv[i + 1]);
        has_pattern = !error;
        ++i;
      }
      if (i + 1 < argc) {
        first_file = i + 1;
      }
    } else if (result->pattern_flag) {
      if (i + 1 < argc) {
        error = AppendPattern(result, argv[i + 1]);
        has_pattern = !error;
        ++i;
      } else {
        error = 1;
      }
    } else if (is_flag) {
      error = ParseFlags(result, argv[i]);
      if (result->pattern_flag && i + 1 < argc) {
        error = AppendPattern(result, argv[i + 1]);
        has_pattern = !error;
        ++i;
      } else if (i + 1 >= argc) {
        error = 1;
      }
    } else if (!has_pattern) {
      error = AppendPattern(result, argv[i]);
      has_pattern = !error;
    } else {
      first_file = i;
    }
    ++i;
  }
  Normalization(result);
  if (!has_pattern) {
    error = 1;
  }
  return first_file;
}