#include <stdlib.h>

#include "../s21_string.h"

void* s21_insert(const char* src, const char* str, s21_size start_index) {
  char* result = S21_NULL;

  if (src != S21_NULL && str != S21_NULL) {
    s21_size src_len = s21_strlen(src);
    s21_size str_len = s21_strlen(str);

    if (start_index <= src_len) {
      s21_size result_len = src_len + str_len;
      result = (char*)malloc((result_len + 1) * sizeof(char));

      if (result != S21_NULL) {
        s21_strncpy(result, src, start_index);
        s21_strncpy(result + start_index, str, str_len);
        s21_strncpy(result + start_index + str_len, src + start_index,
                    src_len - start_index + 1);
      }
    }
  } else if (src == S21_NULL && str != S21_NULL) {
    if (start_index == 0) {
      s21_size str_len = s21_strlen(str);
      result = (char*)malloc((str_len + 1) * sizeof(char));
      if (result != S21_NULL) {
        s21_strncpy(result, str, str_len + 1);
      }
    }
  } else if (src != S21_NULL && str == S21_NULL) {
    s21_size src_len = s21_strlen(src);
    if (start_index <= src_len) {
      result = (char*)malloc((src_len + 1) * sizeof(char));
      if (result != S21_NULL) {
        s21_strncpy(result, src, src_len + 1);
      }
    }
  }

  return result;
}