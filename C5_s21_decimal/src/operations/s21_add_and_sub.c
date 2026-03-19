#include "../s21_decimal.h"

int divByTenForOperations(s21_decimal *result) {
  int flag = 0;
  unsigned long long interm = 0;
  unsigned long long cur = 0;
  for (int i = 2; i >= 0; i--) {
    unsigned long long val = (unsigned int)result->bits[i] + (interm << 32);
    cur = val / 10;
    interm = val % 10;
    result->bits[i] = (unsigned int)cur;
  }

  int rounder = 0;
  if (interm > 5) {
    rounder = 1;
  } else if (interm == 5) {
    int lastNum = result->bits[0] % 10;
    if (lastNum % 2 != 0) {
      rounder = 1;
    }
  }
  if (rounder == 1) {
    unsigned long long numRound = 1;
    for (int i = 0; i < 3; i++) {
      unsigned long long val = (unsigned int)result->bits[i] + numRound;
      (result)->bits[i] = (unsigned int)(val & 0xFFFFFFFF);
      numRound = val >> 32;
    }
    if (numRound > 0) {
      flag = 1;
    }
  }
  return flag;
}

int mulByTenForOperations(s21_decimal *dst) {
  int res = 0;
  unsigned long long temp = 0;
  s21_decimal dstCopy = *dst;
  for (int i = 0; i < 3; i++) {
    unsigned long long val = (unsigned int)dst->bits[i];
    temp = val * 10 + temp;
    (dst)->bits[i] = (unsigned int)(temp & 0xFFFFFFFF);
    temp = temp >> 32;
  }
  if (temp != 0) {
    res = 1;
    *dst = dstCopy;
  }
  return res;
}

// здесь long long для вычитания
int sunTwoNum(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
              int factor) {
  int flag = 0;
  long long temp = 0;
  for (int i = 0; i < 3; i++) {
    long long val1 = (unsigned int)value_1.bits[i];
    long long val2 = (unsigned int)value_2.bits[i];
    temp = val1 + (long long)factor * val2 + temp;
    result->bits[i] = (unsigned int)(temp & 0xFFFFFFFF);
    temp = temp >> 32;
  }
  if (temp != 0) flag = 1;
  return flag;
}

void alignScale(s21_decimal *val_to_mul, s21_decimal *val_to_div,
                int scale_small, int *scale_big) {
  int diff = *scale_big - scale_small;
  int done = 0;
  for (int i = 0; i < diff; i++) {
    if (mulByTenForOperations(val_to_mul)) break;
    done++;
  }
  for (int i = 0; i < diff - done; i++) divByTenForOperations(val_to_div);
  *scale_big = scale_small + done;
}

int handleOverflow(s21_decimal *v1, s21_decimal *v2, s21_decimal *result,
                   int factor, int *scale) {
  int flag = 1;
  while (flag == 1 && *scale > 0) {
    divByTenForOperations(v1);
    divByTenForOperations(v2);
    (*scale)--;
    flag = sunTwoNum(*v1, *v2, result, factor);
  }
  return flag;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  int isneg = 0;
  int factor = 1;
  int sign1 = (value_1.bits[3] >> 31) & 1;
  int sign2 = (value_2.bits[3] >> 31) & 1;
  int scale1 = (value_1.bits[3] >> 16) & 0xFF;
  int scale2 = (value_2.bits[3] >> 16) & 0xFF;
  int min_scale = (scale1 < scale2) ? scale1 : scale2;
  if (sign1 != sign2) factor = -1;
  if (sign1) s21_negate(value_1, &value_1);
  if (sign2) s21_negate(value_2, &value_2);
  if (sign1 == sign2) isneg = sign1;
  if (scale1 > scale2)
    alignScale(&value_2, &value_1, scale2, &scale1);
  else if (scale1 < scale2)
    alignScale(&value_1, &value_2, scale1, &scale2);
  scale1 = (scale1 > scale2) ? scale1 : scale2;
  value_1.bits[3] = (scale1 << 16);
  value_2.bits[3] = (scale1 << 16);
  if (s21_is_greater(value_1, value_2)) {
    if (sign1) isneg = sign1;
    flag = sunTwoNum(value_1, value_2, result, factor);
  } else {
    if (sign2) isneg = sign2;
    flag = sunTwoNum(value_2, value_1, result, factor);
  }
  if (flag == 1)
    flag = handleOverflow(&value_1, &value_2, result, factor, &scale1);
  if (flag == 1) {
    memset(result, 0, sizeof(s21_decimal));
    flag = isneg ? 2 : 1;
  } else {
    while (scale1 > min_scale) {
      unsigned long long rem = 0;
      for (int i = 2; i >= 0; i--) {
        unsigned long long cur = (unsigned int)result->bits[i] + (rem << 32);
        rem = cur % 10;
      }
      if (rem == 0) {
        rem = 0;
        for (int i = 2; i >= 0; i--) {
          unsigned long long cur = (unsigned int)result->bits[i] + (rem << 32);
          result->bits[i] = (unsigned int)(cur / 10);
          rem = cur % 10;
        }
        scale1--;
      } else {
        break;
      }
    }
    result->bits[3] = (scale1 << 16);
    if (isneg) result->bits[3] |= (1u << 31);
  }
  if (result->bits[0] == 0 && result->bits[1] == 0 && result->bits[2] == 0)
    result->bits[3] = 0;
  return flag;
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_negate(value_2, &value_2);
  return s21_add(value_1, value_2, result);
}