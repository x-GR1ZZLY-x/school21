#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int flag = 0;

  if (result != NULL) {
    *result = value;
    result->bits[3] ^= (1u << 31);
  } else {
    flag = 1;
  }
  return flag;
}