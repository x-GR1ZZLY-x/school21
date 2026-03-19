#include "../s21_decimal.h"

int is_zero_96(unsigned int bits[3]) {
  return bits[0] == 0 && bits[1] == 0 && bits[2] == 0;
}

int compare_96(unsigned int a[3], unsigned int b[3]) {
  int exit = 0;
  for (int i = 2; i >= 0; i--) {
    if (a[i] != b[i]) {
      if (a[i] > b[i]) {
        exit = 1;
      } else {
        exit = -1;
      }
      break;
    }
  }
  return exit;
}

void sub_96(unsigned int a[3], unsigned int b[3]) {
  unsigned long long borrow = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long long tmp = (unsigned long long)a[i] - b[i] - borrow;
    if ((unsigned long long)a[i] < b[i] + borrow)
      borrow = 1;
    else
      borrow = 0;
    a[i] = (unsigned int)tmp;
  }
}

int mul10_96(unsigned int bits[3]) {
  unsigned long long carry = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long long tmp = (unsigned long long)bits[i] * 10 + carry;
    bits[i] = (unsigned int)tmp;
    carry = tmp >> 32;
  }
  return carry != 0;
}

void add_96(unsigned int a[3], unsigned int b[3]) {
  unsigned long long carry = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long long tmp = (unsigned long long)a[i] + b[i] + carry;
    a[i] = (unsigned int)tmp;
    carry = tmp >> 32;
  }
}

void div10_96(unsigned int bits[3]) {
  unsigned long long rem = 0;
  for (int i = 2; i >= 0; i--) {
    unsigned long long cur = (unsigned int)bits[i] + (rem << 32);
    bits[i] = (unsigned int)(cur / 10);
    rem = cur % 10;
  }
}

void base10_div_96(unsigned int dividend[3], unsigned int divisor[3],
                   unsigned int quotient[3], unsigned int rem[3]) {
  quotient[0] = quotient[1] = quotient[2] = 0;
  rem[0] = dividend[0];
  rem[1] = dividend[1];
  rem[2] = dividend[2];
  if (compare_96(rem, divisor) >= 0) {
    unsigned int temp_B[3] = {divisor[0], divisor[1], divisor[2]};
    unsigned int mult[3] = {1, 0, 0};
    while (1) {
      unsigned int next_B[3] = {temp_B[0], temp_B[1], temp_B[2]};
      if (mul10_96(next_B)) break;
      if (compare_96(next_B, rem) > 0) break;
      mul10_96(mult);
      temp_B[0] = next_B[0];
      temp_B[1] = next_B[1];
      temp_B[2] = next_B[2];
    }
    while (!is_zero_96(mult)) {
      while (compare_96(rem, temp_B) >= 0) {
        sub_96(rem, temp_B);
        add_96(quotient, mult);
      }
      div10_96(temp_B);
      div10_96(mult);
    }
  }
}

int div_align_scales(unsigned int remainder[3], int *scale1, int scale2,
                     int res_sign) {
  int exit = 0;
  while (*scale1 < scale2) {
    if (mul10_96(remainder)) {
      exit = res_sign ? 2 : 1;
      break;
    }
    (*scale1)++;
  }
  return exit;
}

void div_calc_fractional(unsigned int remainder[3], unsigned int b[3],
                         unsigned int quotient[3], int *result_scale) {
  while (!is_zero_96(remainder) && *result_scale < 28) {
    unsigned int rem_copy[3] = {remainder[0], remainder[1], remainder[2]};
    unsigned int q_copy[3] = {quotient[0], quotient[1], quotient[2]};
    if (mul10_96(remainder) || mul10_96(quotient)) {
      remainder[0] = rem_copy[0];
      remainder[1] = rem_copy[1];
      remainder[2] = rem_copy[2];
      quotient[0] = q_copy[0];
      quotient[1] = q_copy[1];
      quotient[2] = q_copy[2];
      break;
    }
    (*result_scale)++;
    int digit = 0;
    while (compare_96(remainder, b) >= 0) {
      sub_96(remainder, b);
      digit++;
    }
    unsigned long long tmp = (unsigned long long)quotient[0] + digit;
    quotient[0] = (unsigned int)tmp;
    unsigned long long carry = tmp >> 32;
    if (carry) {
      tmp = (unsigned long long)quotient[1] + carry;
      quotient[1] = (unsigned int)tmp;
      quotient[2] += (unsigned int)(tmp >> 32);
    }
  }
}

void div_normalize(unsigned int quotient[3], int *result_scale) {
  while (*result_scale > 0) {
    unsigned long long r_norm = 0;
    for (int i = 2; i >= 0; i--) {
      unsigned long long cur = (unsigned int)quotient[i] + (r_norm << 32);
      r_norm = cur % 10;
    }
    if (r_norm == 0) {
      div10_96(quotient);
      (*result_scale)--;
    } else {
      break;
    }
  }
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int exit = 0;
  if (!result) {
    exit = 1;
  } else {
    result->bits[0] = result->bits[1] = result->bits[2] = result->bits[3] = 0;
    if (is_zero_96((unsigned int *)value_2.bits)) {
      exit = 3;
    } else {
      int sign1 = (value_1.bits[3] >> 31) & 1;
      int sign2 = (value_2.bits[3] >> 31) & 1;
      int sc1 = (value_1.bits[3] >> 16) & 0xFF;
      int sc2 = (value_2.bits[3] >> 16) & 0xFF;
      unsigned int rem[3] = {value_1.bits[0], value_1.bits[1], value_1.bits[2]};
      unsigned int b[3] = {value_2.bits[0], value_2.bits[1], value_2.bits[2]};
      exit = div_align_scales(rem, &sc1, sc2, sign1 ^ sign2);
      if (!exit) {
        unsigned int q[3] = {0}, t_rem[3] = {0};
        int res_scale = sc1 - sc2;
        base10_div_96(rem, b, q, t_rem);
        rem[0] = t_rem[0];
        rem[1] = t_rem[1];
        rem[2] = t_rem[2];
        div_calc_fractional(rem, b, q, &res_scale);
        div_normalize(q, &res_scale);
        result->bits[0] = q[0];
        result->bits[1] = q[1];
        result->bits[2] = q[2];
        result->bits[3] = (res_scale << 16);
        if (sign1 != sign2) result->bits[3] += (1u << 31);
      }
    }
  }
  return exit;
}