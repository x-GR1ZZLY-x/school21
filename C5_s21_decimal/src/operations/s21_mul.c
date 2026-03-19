#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit = 0;
  if (result) {
    s21_decimal res = {0};

    int scale1 = (value_1.bits[3] >> 16) & 0xFF;
    int scale2 = (value_2.bits[3] >> 16) & 0xFF;

    int sign1 = (value_1.bits[3] >> 31) & 1;
    int sign2 = (value_2.bits[3] >> 31) & 1;

    int result_sign = sign1 ^ sign2;
    int result_scale = scale1 + scale2;

    unsigned long long temp[6] = {0};

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        unsigned long long mul = (unsigned long long)value_1.bits[i] *
                                 (unsigned long long)value_2.bits[j];
        temp[i + j] += mul;
      }
    }
    for (int i = 0; i < 5; i++) {
      temp[i + 1] += temp[i] >> 32;
      temp[i] &= 0xFFFFFFFF;
    }
    while (((temp[3] || temp[4] || temp[5]) || result_scale > 28) &&
           result_scale > 0) {
      unsigned long long remain = 0;
      for (int i = 5; i >= 0; i--) {
        unsigned long long cur = (remain << 32) | temp[i];
        temp[i] = cur / 10;
        remain = cur % 10;
      }
      result_scale--;
    }
    if (!temp[3] && !temp[4] && !temp[5]) {
      for (int i = 0; i < 3; i++) res.bits[i] = (unsigned int)temp[i];

      res.bits[3] = (result_scale << 16);
      if (result_sign) res.bits[3] |= 0x80000000;

      *result = res;
    } else
      exit = 1;
  } else
    exit = 1;
  if (result->bits[0] == 0 && result->bits[1] == 0 && result->bits[2] == 0) {
    result->bits[3] = 0;
  }
  return exit;
}
