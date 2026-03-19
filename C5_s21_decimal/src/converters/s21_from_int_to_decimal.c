#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int flag = 0;
  if (dst == NULL) {
    flag = 1;
  } else {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    if (src < 0) {
      dst->bits[3] = 1 << 31;
      unsigned int srcCopy = (unsigned int)src;
      dst->bits[0] = -srcCopy;
    } else {
      dst->bits[0] = src;
    }
  }
  return flag;
}