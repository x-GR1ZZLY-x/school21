#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

#include "../s21_string.h"
#include "s21_sprintf.h"

void s21_reverse(char* str) {
  int len = s21_strlen(str);
  for (int i = 0; i < len / 2; i++) {
    char tmp = str[i];
    str[i] = str[len - 1 - i];
    str[len - 1 - i] = tmp;
  }
}

void s21_int_to_str(long long num, char* res) {
  int i = 0;
  if (num == 0) {
    res[i++] = '0';
    res[i] = '\0';
  } else {
    if (num < 0) num = -num;
    while (num > 0) {
      res[i++] = (num % 10) + '0';
      num /= 10;
    }
    res[i] = '\0';
    s21_reverse(res);
  }
}

void s21_ull_to_str(unsigned long long num, char* res) {
  char buff[100];
  int i = 0;
  if (num == 0) {
    res[0] = '0';
    res[1] = '\0';
  } else {
    while (num > 0) {
      buff[i++] = (num % 10) + '0';
      num /= 10;
    }
    for (int j = 0; j < i; j++) res[j] = buff[i - 1 - j];
    res[i] = '\0';
  }
}

/* char **str -> char *converted */
void s21_handle_int(s21_format_info* info, char* converted, va_list* args) {
  long long val = 0;
  if (info->length == 'l') {
    val = (long long)va_arg(*args, long);
  } else if (info->length == 'h') {
    val = (short)va_arg(*args, int);
  } else {
    val = va_arg(*args, int);
  }

  int neg = (val < 0) ? 1 : 0;
  if (neg) val = -val;
  char buff[512] = {0};
  if (!(val == 0 && info->precision == 0)) s21_int_to_str(val, buff);

  char* ptr = converted;

  if (neg) {
    *ptr++ = '-';
  }

  /* ведущие нули выполняет format_integer */

  char* src = buff;
  while (*src) {
    *ptr++ = *src++;
  }
  *ptr = '\0';
}

unsigned long long s21_get_unsigned_val(s21_format_info* info, va_list* args) {
  unsigned long long val = 0;
  if (info->length == 'l') {
    val = (unsigned long long)va_arg(*args, unsigned long);
  } else if (info->length == 'h') {
    val = (unsigned short)va_arg(*args, unsigned int);
  } else {
    val = (unsigned int)va_arg(*args, unsigned int);
  }
  return val;
}

void s21_uitoa(unsigned long long val, s21_format_info* info, char* buff) {
  int quant = 10;
  char* elem = "0123456789";
  if (info->specifer == 'o')
    quant = 8;
  else if (info->specifer == 'x') {
    quant = 16;
    elem = "0123456789abcdef";
  } else if (info->specifer == 'X') {
    quant = 16;
    elem = "0123456789ABCDEF";
  }

  int i = 0;
  if (!(val == 0 && info->precision == 0)) {
    unsigned long long cpyval = val;
    if (cpyval == 0) {
      buff[i++] = '0';
    }
    while (cpyval > 0) {
      buff[i++] = elem[cpyval % quant];
      cpyval /= quant;
    }
  }
  buff[i] = '\0';
  s21_reverse(buff);
}

/* char **str -> char *converted */
void s21_handle_unsigned(s21_format_info* info, char* converted,
                         va_list* args) {
  unsigned long long val = s21_get_unsigned_val(info, args);
  char buff[512] = {0};
  s21_uitoa(val, info, buff);

  char* ptr = buff;
  char* dst = converted;
  while (*ptr) {
    *dst++ = *ptr++;
  }
  *dst = '\0';
}

void s21_float_to_str(long double val, int prec, char* res, int force_dot) {
  long double scale = powl(10.0, prec);
  val = roundl(val * scale) / scale;
  unsigned long long int_part = (unsigned long long)val;
  long double diff = (val - (long double)int_part) * scale;
  unsigned long long frac_part = (unsigned long long)roundl(diff);

  char num_str[256] = {0};
  s21_ull_to_str(int_part, num_str);
  s21_strncat(res, num_str, s21_strlen(num_str));

  if (prec > 0 || force_dot) s21_strncat(res, ".", 1);
  if (prec > 0) {
    char frac_str[128] = {0};
    s21_ull_to_str(frac_part, frac_str);
    int zeros = prec - s21_strlen(frac_str);
    while (zeros-- > 0) s21_strncat(res, "0", 1);
    s21_strncat(res, frac_str, s21_strlen(frac_str));
  }
}

void s21_handle_exp(long double val, s21_format_info* info, char* buff) {
  int pow = 0;
  if (val != 0) {
    while (fabsl(val) >= 10.0) {
      val /= 10.0;
      pow++;
    }
    while (fabsl(val) < 1.0) {
      val *= 10.0;
      pow--;
    }
  }
  s21_float_to_str(val, info->precision, buff, info->flag_lattice);
  s21_strncat(buff,
              (info->specifer == 'E' || info->specifer == 'G') ? "E" : "e", 1);
  s21_strncat(buff, (pow >= 0) ? "+" : "-", 1);
  if (abs(pow) < 10) s21_strncat(buff, "0", 1);
  char pow_str[16];
  s21_int_to_str(abs(pow), pow_str);
  s21_strncat(buff, pow_str, s21_strlen(pow_str));
}

void s21_handle_g(long double val, s21_format_info* info, char* buff) {
  int org = (info->precision == 0) ? 1 : info->precision;
  int pow = 0;
  long double copy = val;
  if (copy != 0) {
    while (fabsl(copy) >= 10.0) {
      copy /= 10.0;
      pow++;
    }
    while (fabsl(copy) < 1.0) {
      copy *= 10.0;
      pow--;
    }
  }
  if (org > pow && pow >= -4) {
    info->precision = org - 1 - pow;
    s21_float_to_str(val, info->precision, buff, 0);
  } else {
    info->precision = org - 1;
    s21_handle_exp(val, info, buff);
  }
  if (!info->flag_lattice && s21_strchr(buff, '.')) {
    int len = s21_strlen(buff);
    char* ptr = buff + len - 1;
    while (*ptr == '0') {
      *ptr = '\0';
      ptr--;
    }
    if (*ptr == '.') *ptr = '\0';
  }
}

/* char **str -> char *converted */
void s21_handle_float(s21_format_info* info, char* converted, va_list* args) {
  long double val = 0.0L;
  if (info->length == 'L') {
    val = va_arg(*args, long double);
  } else {
    val = (long double)va_arg(*args, double);
  }
  if (info->precision < 0) info->precision = 6;

  char* ptr = converted;

  if (val < 0.0L) {
    *ptr++ = '-';
    val = -val;
  }

  char buff[512] = {0};
  if (info->specifer == 'f') {
    s21_float_to_str(val, info->precision, buff, info->flag_lattice);
  } else if (info->specifer == 'e' || info->specifer == 'E') {
    s21_handle_exp(val, info, buff);
  } else if (info->specifer == 'g' || info->specifer == 'G') {
    s21_handle_g(val, info, buff);
  }

  /* копируем buff в converted */
  char* src = buff;
  while (*src) {
    *ptr++ = *src++;
  }
  *ptr = '\0';
}

/* char **str -> char *converted */
void s21_handle_char(s21_format_info* info, char* converted, va_list* args) {
  (void)info;
  char ch = (char)va_arg(*args, int);
  converted[0] = ch;
  converted[1] = '\0';
}

/* char **str -> char *converted */
void s21_handle_string(s21_format_info* info, char* converted, va_list* args) {
  char* string = va_arg(*args, char*);
  if (string == S21_NULL) string = "(null)";

  int len = s21_strlen(string);
  if (info->precision >= 0 && info->precision < len) len = info->precision;

  for (int i = 0; i < len; i++) {
    converted[i] = string[i];
  }
  converted[len] = '\0';
}

/* char **str -> char *converted */
void s21_handle_pointer(s21_format_info* info, char* converted, va_list* args) {
  (void)info;
  void* ptr = va_arg(*args, void*);
  unsigned long long val = (unsigned long long)ptr;

  if (val == 0) {
    char* strnil = "(nil)";
    char* dst = converted;
    while (*strnil) {
      *dst++ = *strnil++;
    }
    *dst = '\0';
  } else {
    char buff[512] = {0};
    int index = 0;
    char* elem = "0123456789abcdef";
    while (val > 0) {
      buff[index++] = elem[val % 16];
      val /= 16;
    }
    buff[index] = '\0';
    s21_reverse(buff);

    /* 0x добавит format_pointer */
    char* src = buff;
    char* dst = converted;
    while (*src) {
      *dst++ = *src++;
    }
    *dst = '\0';
  }
}

/* char **str -> char *converted */
void s21_handle_percent(s21_format_info* info, char* converted) {
  (void)info;
  converted[0] = '%';
  converted[1] = '\0';
}

void s21_process_width_precision(s21_format_info* info, va_list* args) {
  if (info->width_from_arg) {
    info->width = va_arg(*args, int);
    if (info->width < 0) {
      info->width = -info->width;
      info->flag_minus = 1;
    }
  }
  if (info->precision_from_arg) {
    info->precision = va_arg(*args, int);
    if (info->precision < 0) {
      info->precision = -1;
    }
  }
}

void s21_handler(s21_format_info* info, char* converted, va_list* args) {
  switch (info->specifer) {
    case 'd':
    case 'i':
      s21_handle_int(info, converted, args);
      break;
    case 'u':
    case 'o':
    case 'x':
    case 'X':
      s21_handle_unsigned(info, converted, args);
      break;
    case 'c':
      s21_handle_char(info, converted, args);
      break;
    case 's':
      s21_handle_string(info, converted, args);
      break;
    case 'p':
      s21_handle_pointer(info, converted, args);
      break;
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      s21_handle_float(info, converted, args);
      break;
    case '%':
      s21_handle_percent(info, converted);
      break;

    default:
      converted[0] = '\0';
      break;
  }
}

char* s21_convert_format(char* format, s21_format_info* info, char** str,
                         va_list* args) {
  format = s21_parse_format(format, info);
  s21_process_width_precision(info, args);

  char converted[1024] = {0};

  s21_handler(info, converted, args);

  s21_format_value(str, converted, info);

  return format;
}