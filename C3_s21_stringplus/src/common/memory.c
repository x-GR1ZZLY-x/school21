#include "../s21_string.h"

void* s21_memchr(const void* str, int c, s21_size n) {
  const unsigned char* ptr = (const unsigned char*)str;
  unsigned char ch = (unsigned char)c;
  void* result = S21_NULL;
  int match = 0;

  for (s21_size i = 0; i < n; ++i) {
    if (ptr[i] == ch && !match) {
      result = (void*)&ptr[i];
      match = 1;
    }
  }
  return result;
}

int s21_memcmp(const void* str1, const void* str2, s21_size n) {
  const unsigned char* s1 = (const unsigned char*)str1;
  const unsigned char* s2 = (const unsigned char*)str2;
  int result = 0;
  int match = 0;
  s21_size i = 0;
  while (i < n && !match) {
    if (s1[i] != s2[i]) {
      result = s1[i] - s2[i];
      match = 1;
    }
    ++i;
  }

  return result;
}

void* s21_memcpy(void* dest, const void* src, s21_size n) {
  unsigned char* d = (unsigned char*)dest;
  const unsigned char* s = (const unsigned char*)src;

  for (s21_size i = 0; i < n; ++i) {
    d[i] = s[i];
  }
  return dest;
}

void* s21_memset(void* str, int c, s21_size n) {
  unsigned char* s = (unsigned char*)str;
  unsigned char val = (unsigned char)c;
  for (s21_size i = 0; i < n; ++i) {
    s[i] = val;
  }

  return str;
}