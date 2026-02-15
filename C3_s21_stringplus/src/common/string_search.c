#include "../s21_string.h"

char* s21_strchr(const char* str, int c) {
  char* result = S21_NULL;
  s21_size i = 0;
  int found = 0;

  while (str[i] != '\0' && !found) {
    if (str[i] == (char)c) {
      result = (char*)(str + i);
      found = 1;
    } else {
      i++;
    }
  }

  if (!found && c == '\0') {
    result = (char*)(str + i);
  }

  return result;
}
// Searches for the first occurrence of the character c (an unsigned char)
// in the string pointed to, by the argument str

char* s21_strrchr(const char* str, int c) {
  char* result = S21_NULL;
  s21_size i = 0;

  while (str[i] != '\0') {
    if (str[i] == (char)c) {
      result = (char*)(str + i);
    }
    i++;
  }

  if (c == '\0') {
    result = (char*)(str + i);
  }

  return result;
}
// Searches for the last occurrence of the character c (an unsigned char)
// in the string pointed to by the argument str

char* s21_strpbrk(const char* str1, const char* str2) {
  while (*str1) {
    const char* temp = str2;
    while (*temp) {
      if (*str1 == *temp) {
        return (char*)str1;
      }
      temp++;
    }
    str1++;
  }
  return S21_NULL;
}
// Finds the first character in the string str1 that matches any character
// specified in str2.

char* s21_strstr(const char* haystack, const char* needle) {
  char* result = S21_NULL;
  s21_size i = 0;
  int found = 0;

  if (*needle == '\0') {
    result = (char*)haystack;
  } else {
    while (haystack[i] != '\0' && !found) {
      s21_size h = i;
      s21_size n = 0;

      while (haystack[h] != '\0' && needle[n] != '\0' &&
             haystack[h] == needle[n]) {
        h++;
        n++;
      }

      if (needle[n] == '\0') {
        result = (char*)(haystack + i);
        found = 1;
      } else {
        i++;
      }
    }
  }

  return result;
}
// Finds the first occurrence of the entire string needle (not including
// the terminating null character) which appears in the string haystack.