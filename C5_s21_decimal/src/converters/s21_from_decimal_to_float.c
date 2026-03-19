#include <math.h>

#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal value, float *dst) {
  int exit = 0;
  if (dst) {
    double temp = 0.0;

    temp += (double)value.bits[0];
    temp += (double)value.bits[1] * pow(2, 32);
    temp += (double)value.bits[2] * pow(2, 64);

    int scale = (value.bits[3] >> 16) & 0xFF;
    temp /= pow(10, scale);

    int sign = (value.bits[3] >> 31) & 1;
    if (sign) temp *= -1;

    if (isinf(temp)) exit = 1;

    *dst = (float)temp;
  } else
    exit = 1;
  return exit;
}
