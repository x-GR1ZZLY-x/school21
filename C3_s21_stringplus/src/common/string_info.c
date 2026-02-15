#include "../s21_string.h"

s21_size s21_strlen(const char* str) {
  s21_size len = 0;

  while (str[len] != '\0') {
    len++;
  }

  return len;
}
// Computes the length of the string str up to but not including the
// terminating null character.
int s21_strncmp(const char* str1, const char* str2, s21_size n) {
  s21_size i = 0;
  int result = 0;

  while (i < n && result == 0) {
    unsigned char c1 = (unsigned char)str1[i];
    unsigned char c2 = (unsigned char)str2[i];

    if (c1 != c2) {
      result = c1 - c2;
    } else if (c1 == '\0') {
      i = n;
    } else {
      i++;
    }
  }

  return result;
}
// Compares at most the first n bytes of str1 and str2.
s21_size s21_strcspn(const char* str1, const char* str2) {
  s21_size len = 0;
  int found = 0;

  while (str1[len] != '\0' && !found) {
    s21_size j = 0;

    while (str2[j] != '\0' && !found) {
      if ((unsigned char)str1[len] == (unsigned char)str2[j]) {
        found = 1;
      } else {
        j++;
      }
    }

    if (!found) {
      len++;
    }
  }

  return len;
}
// Calculates the length of the initial segment of str1 which consists
// entirely of characters not in str2.