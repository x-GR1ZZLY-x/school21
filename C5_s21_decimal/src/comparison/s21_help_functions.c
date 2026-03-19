#include "s21_compare.h"

int s21_get_sign(s21_decimal d) { return (d.bits[3] >> 31) & 1; }

int s21_get_scale(s21_decimal d) { return (d.bits[3] >> 16) & 0xFF; }

void s21_set_scale(s21_decimal *d, int scale) {
  d->bits[3] &= ~(0xFF << 16);
  d->bits[3] |= (scale << 16);
}

int s21_is_zero(s21_decimal d) {
  return d.bits[0] == 0 && d.bits[1] == 0 && d.bits[2] == 0;
}

int s21_compare_mantissa(s21_decimal a, s21_decimal b) {
  uint32_t a2 = (uint32_t)a.bits[2];
  uint32_t b2 = (uint32_t)b.bits[2];

  int result = 0;

  if (a2 != b2) {
    result = (a2 > b2) ? 1 : -1;
  } else {
    uint32_t a1 = (uint32_t)a.bits[1];
    uint32_t b1 = (uint32_t)b.bits[1];

    if (a1 != b1) {
      result = (a1 > b1) ? 1 : -1;
    } else {
      uint32_t a0 = (uint32_t)a.bits[0];
      uint32_t b0 = (uint32_t)b.bits[0];

      if (a0 != b0) {
        result = (a0 > b0) ? 1 : -1;
      }
    }
  }
  return result;
}

int s21_mul10(s21_decimal *d) {
  int overflow = 0;
  uint64_t tmp = 0;
  uint32_t carry = 0;

  for (int i = 0; i < 3; ++i) {
    tmp = (uint64_t)(uint32_t)d->bits[i] * 10 + carry;
    d->bits[i] = (uint32_t)tmp;
    carry = tmp >> 32;
  }
  if (carry != 0) {
    overflow = 1;
  }
  return overflow;
}

void s21_div10(s21_decimal *d) {
  uint64_t remainder = 0;
  uint64_t cur = 0;

  for (int i = 2; i >= 0; --i) {
    cur = (remainder << 32) | (uint32_t)d->bits[i];
    d->bits[i] = (uint32_t)(cur / 10);
    remainder = cur % 10;
  }
}

void s21_normalization(s21_decimal *a, s21_decimal *b) {
  int scale_a = s21_get_scale(*a);
  int scale_b = s21_get_scale(*b);

  while (scale_a < scale_b) {
    if (s21_mul10(a) == 0) {
      scale_a++;
      s21_set_scale(a, scale_a);
    } else {
      s21_div10(b);
      scale_b--;
      s21_set_scale(b, scale_b);
    }
  }

  while (scale_b < scale_a) {
    if (s21_mul10(b) == 0) {
      scale_b++;
      s21_set_scale(b, scale_b);
    } else {
      s21_div10(a);
      scale_a--;
      s21_set_scale(a, scale_a);
    }
  }
}
