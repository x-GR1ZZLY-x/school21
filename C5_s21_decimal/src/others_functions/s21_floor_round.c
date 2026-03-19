#include "../s21_decimal.h"

int get_scale(s21_decimal value) { return (value.bits[3] >> 16) & 0xFF; }

int get_sign(s21_decimal value) { return (value.bits[3] >> 31) & 1; }

int s21_round(s21_decimal value, s21_decimal *result) {
  int exit = 0;
  if (result) {
    *result = value;

    int scale = get_scale(value);
    int sign = get_sign(value);

    if (scale != 0) {
      unsigned long long temp;
      unsigned int remain = 0;

      for (int s = 0; s < scale - 1; s++) {
        remain = 0;
        for (int i = 2; i >= 0; i--) {
          temp = ((unsigned long long)remain << 32 |
                  (unsigned int)result->bits[i]);
          result->bits[i] = (unsigned int)(temp / 10);
          remain = (unsigned int)(temp % 10);
        }
      }
      remain = 0;
      for (int i = 2; i >= 0; i--) {
        temp =
            ((unsigned long long)remain << 32) | (unsigned int)result->bits[i];
        result->bits[i] = (unsigned int)(temp / 10);
        remain = (unsigned int)(temp % 10);
      }
      if (remain >= 5) {
        unsigned int carry = 1;
        for (int i = 0; i < 3 && carry; i++) {
          unsigned long long sum = (unsigned long long)result->bits[i] + carry;
          result->bits[i] = (unsigned int)sum;
          carry = (sum >> 32);
        }
      }
      result->bits[3] &= ~0x00FF0000;
      if (sign)
        result->bits[3] |= 0x80000000;
      else
        result->bits[3] &= ~0x80000000;
    }
  } else
    exit = 1;
  return exit;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  int exit = 0;
  if (result) {
    *result = value;

    int scale = get_scale(value);
    int sign = get_sign(value);

    if (scale != 0) {
      unsigned int remain = 0;
      unsigned long long temp = 0;
      int had_fraction = 0;

      for (int s = 0; s < scale; s++) {
        remain = 0;
        for (int i = 2; i >= 0; i--) {
          temp = ((unsigned long long)remain << 32) |
                 (unsigned int)result->bits[i];
          result->bits[i] = (unsigned int)(temp / 10);
          remain = (unsigned int)(temp % 10);
        }

        if (remain != 0) had_fraction = 1;
      }
      if (sign && had_fraction) {
        unsigned long long tmp;
        unsigned int carry = 1;
        for (int i = 0; i < 3 && carry; i++) {
          tmp = (unsigned long long)result->bits[i] + carry;
          result->bits[i] = (unsigned int)tmp;
          carry = (tmp >> 32);
        }
      }
      result->bits[3] &= ~0x00FF0000;
      if (sign)
        result->bits[3] |= 0x80000000;
      else
        result->bits[3] &= ~0x80000000;
    }
  } else
    exit = 1;
  return exit;
}
