#include "../s21_string.h"
#include "s21_sprintf.h"

void init_format_struct(s21_format_info* info) {
  info->flag_minus = 0;
  info->flag_plus = 0;
  info->flag_lattice = 0;
  info->flag_space = 0;
  info->flag_null = 0;

  info->precision = -1;
  info->precision_from_arg = 0;
  info->width = 0;
  info->width_from_arg = 0;
  info->length = '\0';

  info->specifer = '\0';
}

char* parse_flags(char* format, s21_format_info* info) {
  int parsing = 1;

  while (parsing && *format) {
    switch (*format) {
      case '-':
        info->flag_minus = 1;
        format++;
        break;
      case '+':
        info->flag_plus = 1;
        format++;
        break;
      case '#':
        info->flag_lattice = 1;
        format++;
        break;
      case '0':
        info->flag_null = 1;
        format++;
        break;
      case ' ':
        info->flag_space = 1;
        format++;
        break;
      default:
        parsing = 0;
        break;
    }
  }

  return format;
}

char* parse_width(char* format, s21_format_info* info) {
  if (*format == '*') {
    info->width_from_arg = 1;
    format++;
  } else {
    while (*format >= '0' && *format <= '9') {
      info->width = info->width * 10 + (*format - '0');
      format++;
    }
  }

  return format;
}

char* parse_precision(char* format, s21_format_info* info) {
  if (*format == '.') {
    format++;

    if (*format == '*') {
      info->precision_from_arg = 1;
      format++;
    } else {
      info->precision = 0;
      while (*format >= '0' && *format <= '9') {
        info->precision = info->precision * 10 + (*format - '0');
        format++;
      }
    }
  }

  return format;
}

char* parse_length(char* format, s21_format_info* info) {
  if (*format == 'h' || *format == 'l' || *format == 'L') {
    info->length = *format;
    format++;
  }

  return format;
}

char* parse_specifer(char* format, s21_format_info* info) {
  if (*format && s21_strchr("cdieEfgGosuxXpn%", *format)) {
    info->specifer = *format;
    format++;
  }

  return format;
}

void normalization(s21_format_info* info) {
  if (info->flag_plus) {
    info->flag_space = 0;
  }
  if ((info->precision >= 0 && s21_strchr("diuoxX", info->specifer)) ||
      info->flag_minus) {
    info->flag_null = 0;
  }
  if (info->specifer == '%') {
    info->flag_null = 0;
    info->flag_plus = 0;
    info->flag_space = 0;
  }
  if (info->specifer == 'n') {
    info->flag_minus = 0;
    info->flag_plus = 0;
    info->flag_space = 0;
    info->flag_null = 0;
    info->flag_lattice = 0;
    info->width = 0;
    info->width_from_arg = 0;
    info->precision = -1;
    info->precision_from_arg = 0;
  }
}

char* s21_parse_format(char* format, s21_format_info* info) {
  init_format_struct(info);

  format = parse_flags(format, info);
  format = parse_width(format, info);
  format = parse_precision(format, info);
  format = parse_length(format, info);
  format = parse_specifer(format, info);

  normalization(info);

  return format;
}