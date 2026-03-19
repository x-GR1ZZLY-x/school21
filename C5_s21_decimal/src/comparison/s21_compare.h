
#ifndef S21_COMPARE_H
#define S21_COMPARE_H
#include <stdint.h>

#include "../s21_decimal.h"
int s21_get_sign(s21_decimal d);
int s21_get_scale(s21_decimal d);
void s21_set_scale(s21_decimal *d, int scale);
int s21_is_zero(s21_decimal d);
int s21_compare_mantissa(s21_decimal a, s21_decimal b);
int s21_mul10(s21_decimal *d);
void s21_div10(s21_decimal *d);
void s21_normalization(s21_decimal *a, s21_decimal *b);
int s21_compare(s21_decimal a, s21_decimal b);
#endif