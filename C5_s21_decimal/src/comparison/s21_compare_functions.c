#include "s21_compare.h"

int s21_compare(s21_decimal a, s21_decimal b) {
  int result = 0;

  if (s21_is_zero(a) == 1 && s21_is_zero(b) == 1) {
    result = 0;
  } else {
    int sign_a = s21_get_sign(a);
    int sign_b = s21_get_sign(b);

    if (sign_a != sign_b) {
      if (sign_a == 1) {
        result = -1;
      } else {
        result = 1;
      }
    } else {
      s21_normalization(&a, &b);
      result = s21_compare_mantissa(a, b);
      if (sign_a == 1) {
        result = -result;
      }
    }
  }
  return result;
}

int s21_is_less(s21_decimal a, s21_decimal b) { return s21_compare(a, b) < 0; }

int s21_is_greater(s21_decimal a, s21_decimal b) {
  return s21_compare(a, b) > 0;
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
  return s21_compare(a, b) == 0;
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_greater(a, b);
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_less(a, b);
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_equal(a, b);
}
