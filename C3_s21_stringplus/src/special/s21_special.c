#include "../s21_string.h"
#include "s21_hfileforspecial.h"

char* mergeStr(char* str, int errnum);
int checkChar(char ch, const char* delim);

char* s21_strerror(int errnum) {
  static const char* err_mes[] = {ERR_LIST};
  char* result;
  if (MAX_ERRN == 0 || (errnum < 0 || errnum > MAX_ERRN)) {
    result = mergeStr("Unknown error ", errnum);
  } else if (errnum >= 0 && errnum <= MAX_ERRN) {
    result = ((char*)err_mes[errnum]);
  }
  return result;
}

char* s21_strtok(char* str, const char* delim) {
  static char* point = S21_NULL;
  char* pointForReturn = S21_NULL;
  int ender = 0;
  if (str == S21_NULL) {
    str = point;
  }
  if (str == S21_NULL) {
    ender = 1;
  } else {
    while (ender != 1 && checkChar(*str, delim) == 1) {
      str++;
    }
    if (*str == '\0') {
      point = S21_NULL;
    } else {
      pointForReturn = str;
      while (checkChar(*str, delim) == 0 && *str != '\0') {
        str++;
      }
      if (*str == '\0') {
        point = S21_NULL;
      } else {
        *str = '\0';
        point = str + 1;
      }
    }
  }
  return pointForReturn;
}

char* mergeStr(char* str, int errnum) {
  static char arr[100];
  int index = 0;
  while (str[index] != '\0') {
    arr[index] = str[index];
    index++;
  }
  if (errnum < 0) {
    arr[index] = '-';
    errnum *= -1;
    index++;
  }
  if (errnum == 0) {
    arr[index] = '0';
    arr[index + 1] = '\0';
  } else {
    char err[100];
    int indexForErr = 0;
    while (errnum != 0) {
      err[indexForErr] = (errnum % 10) + '0';
      errnum = errnum / 10;
      indexForErr++;
    }
    while (indexForErr != 0) {
      indexForErr--;
      arr[index] = err[indexForErr];
      index++;
    }
  }
  arr[index] = '\0';
  return arr;
}

int checkChar(char ch, const char* delim) {
  int res = 0;
  int index = 0;
  while (delim[index] != '\0' && res == 0) {
    if (delim[index] == ch) {
      res = 1;
    }
    index++;
  }
  return res;
}
