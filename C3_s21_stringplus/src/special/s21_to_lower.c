#include <stdlib.h>

#include "../s21_string.h"

void* s21_to_lower(const char* str) {
  char* result = S21_NULL;

  if (str != S21_NULL) {
    s21_size len = s21_strlen(str);
    result = (char*)malloc((len + 1) * sizeof(char));

    if (result != S21_NULL) {
      for (s21_size i = 0; i <= len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
          result[i] = str[i] + 32;  // 'a' - 'A' = 32
        } else {
          result[i] = str[i];
        }
      }
    }
  }

  return result;
}