#include "../s21_string.h"

char* s21_strncat(char* dest, const char* src, s21_size n) {
  char* d = dest;

  while (*d) d++;
  while (n-- && *src) *d++ = *src++;
  *d = '\0';

  return dest;
}

char* s21_strncpy(char* dest, const char* src, s21_size n) {
  char* d = dest;
  const char* s = src;

  while (n && *s) {
    *d++ = *s++;
    n--;
  }

  while (n--) {
    *d++ = '\0';
  }

  return dest;
}