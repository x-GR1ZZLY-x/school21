#include "../s21_decimal.h"

int fromStrToNum(char *numStr) {
  int mul = 1;
  int index = 7;
  int res = 0;
  while (index != -1) {
    if (numStr[index] != '.') {
      res += (numStr[index] - '0') * mul;
      mul *= 10;
    }
    index--;
  }
  return res;
}

int getDeg(char *numStr, int size) {
  int index = size - 1;
  int mul = 1;
  int res = -6;
  int sign = 1;
  if (numStr[9] == '-') {
    sign = -sign;
  }
  while (index != 9) {
    res += (numStr[index--] - '0') * mul * sign;
    mul *= 10;
  }
  return res;
}

void mulByTen(s21_decimal *dst) {
  unsigned long long temp = 0;
  for (int i = 0; i < 3; i++) {
    unsigned long long val =
        (unsigned int)
            dst->bits[i];  // здесь сразу приводим к беззнаковому инту чтобы
                           // старшие биты не заполнялись мусором при апкасте
    temp = val * 10 + temp;
    (dst)->bits[i] =
        (unsigned int)(temp & 0xFFFFFFFF);  // это значит что берем 32 младших
                                            // бита берем
    temp = temp >> 32;
  }
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int flag = 0;
  int isneg = 0;
  if (dst == NULL) flag = 1;
  if (isnan(src) == 1 || isinf(src) == 1) flag = 1;
  if (fabsf(src) > 7.9228162514264337593543950335e28) flag = 1;
  if (src > 0 && src < 1e-28) flag = 1;
  if (src < 0) {
    isneg = 1;
    float abssrc = fabsf(src);
    src = abssrc;
  }
  if (flag != 1) {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    char numStr[64];
    sprintf(numStr, "%.6e", fabsf(src));
    int mantis = fromStrToNum(numStr);
    int deg = getDeg(numStr, strlen(numStr));
    dst->bits[0] = mantis;
    if (deg > 0) {
      for (int i = 0; i < deg; i++) {
        mulByTen(dst);
      }
      deg = 0;
    } else {
      deg = -deg;
      while (deg > 28) {
        dst->bits[0] /= 10;
        deg--;
      }
    }
    dst->bits[3] = (isneg << 31);
    dst->bits[3] += (deg << 16);
  }
  return flag;
}