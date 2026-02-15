#include "s21_sprintf.h"

#include <stdarg.h>

#include "../s21_string.h"

int s21_sprintf(char* str, const char* format, ...) {
  va_list args;
  va_start(args, format);

  char* out = str;
  const char* p = format;
  s21_format_info info;

  while (*p) {
    if (*p == '%') {
      p++;
      p = s21_convert_format((char*)p, &info, &out, &args);
    } else {
      *out++ = *p++;
    }
  }

  *out = '\0';
  va_end(args);
  return (int)(out - str);
}
