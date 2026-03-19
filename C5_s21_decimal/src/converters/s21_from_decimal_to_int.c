#include "../s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int flag = 0;
  if (!dst) {
    flag = 1;
  }
  int scale = (src.bits[3] >> 16) & 0xFF;
  int sign = (src.bits[3] >> 31) & 1;

  while (!flag && scale > 0) {
    unsigned long long temp = 0;
    unsigned int remainder = 0;
    for (int i = 2; i >= 0; --i) {
      temp = ((unsigned long long)remainder << 32) | (unsigned int)src.bits[i];
      src.bits[i] = (unsigned int)(temp / 10);
      remainder = (unsigned int)(temp % 10);
    }
    --scale;
  }
  if (src.bits[1] != 0 || src.bits[2] != 0) {
    flag = 1;
  }
  if (!flag) {
    unsigned int value = (unsigned int)src.bits[0];

    unsigned int int_max = ~(1u << 31);
    unsigned int int_min_abs = (1u << 31);

    if (!sign) {
      if (value > int_max) {
        flag = 1;
      } else {
        *dst = (int)value;
      }
    } else {
      if (value > int_min_abs) {
        flag = 1;
      } else if (value == int_min_abs) {
        *dst = (int)(1u << 31);
      } else {
        *dst = -(int)value;
      }
    }
  }
  return flag;
}
