#include "../s21_decimal.h"

int divByTen(s21_decimal *result) {
  int flag = 0;
  unsigned long long interm = 0;
  unsigned long long cur = 0;
  int scale = (result->bits[3] >> 16) & 0xFF;
  for (int i = 2; i >= 0; i--) {
    unsigned long long val =
        (unsigned long long)(unsigned int)result->bits[i] + (interm << 32);
    cur = val / 10;
    interm = val % 10;
    result->bits[i] = (unsigned int)cur;
  }
  result->bits[3] += ((--scale) << 16);
  return flag;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int flag = 0;
  if (result != NULL) {
    *result = value;
    int scale = (value.bits[3] >> 16) & 0xFF;
    for (int i = 0; i < scale; i++) {
      divByTen(result);
    }
    result->bits[3] &= (1u << 31);
  } else {
    flag = 1;
  }
  return flag;
}