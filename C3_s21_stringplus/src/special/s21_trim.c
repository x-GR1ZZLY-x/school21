#include <stdlib.h>

#include "../s21_string.h"

int s21_strchr_bool(const char* str, char c) {
  int found = 0;
  if (str != S21_NULL) {
    for (s21_size i = 0; str[i] != '\0' && !found; i++) {
      if (str[i] == c) {
        found = 1;
      }
    }
  }
  return found;
}

void* s21_trim(const char* src, const char* trim_chars) {
  char* result = S21_NULL;

  if (src != S21_NULL) {
    const char* chars_to_trim;
    if (trim_chars != S21_NULL && trim_chars[0] != '\0') {
      chars_to_trim = trim_chars;
    } else {
      chars_to_trim = " \t\n\v\f\r";
    }

    s21_size src_len = s21_strlen(src);
    s21_size start = 0;
    s21_size end = src_len;

    while (start < src_len && s21_strchr_bool(chars_to_trim, src[start])) {
      start++;
    }

    while (end > start && s21_strchr_bool(chars_to_trim, src[end - 1])) {
      end--;
    }

    s21_size result_len = end - start;
    result = (char*)malloc((result_len + 1) * sizeof(char));

    if (result != S21_NULL) {
      s21_strncpy(result, src + start, result_len);
      result[result_len] = '\0';
    }
  }

  return result;
}