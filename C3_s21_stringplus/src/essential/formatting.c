#include "../s21_string.h"
#include "s21_sprintf.h"

void buffer_add_char(char** buf, char c) {
  **buf = c;
  (*buf)++;
}

void buffer_add_string(char** buf, const char* str, s21_size len) {
  if (len > 0) {
    s21_memcpy(*buf, str, len);
    *buf += len;
  }
}

void buffer_add_repeat(char** buf, char c, int count) {
  if (count > 0) {
    s21_memset(*buf, c, count);
    *buf += count;
  }
}

void format_char(char** buf, char c, s21_format_info* info) {
  int padding = info->width > 1 ? info->width - 1 : 0;

  if (!info->flag_minus && padding > 0) buffer_add_repeat(buf, ' ', padding);

  buffer_add_char(buf, c);

  if (info->flag_minus && padding > 0) buffer_add_repeat(buf, ' ', padding);
}

void format_string(char** buf, const char* str, s21_format_info* info) {
  if (str == S21_NULL) str = "(null)";

  int len = (int)s21_strlen(str);
  if (info->precision >= 0 && info->precision < len) len = info->precision;

  int padding = info->width > len ? info->width - len : 0;

  if (!info->flag_minus && padding > 0) buffer_add_repeat(buf, ' ', padding);

  buffer_add_string(buf, str, len);

  if (info->flag_minus && padding > 0) buffer_add_repeat(buf, ' ', padding);
}

void format_percent(char** buf, s21_format_info* info) {
  int padding = info->width > 1 ? info->width - 1 : 0;

  if (!info->flag_minus && padding > 0)
    buffer_add_repeat(buf, info->flag_null ? '0' : ' ', padding);

  buffer_add_char(buf, '%');

  if (info->flag_minus && padding > 0) buffer_add_repeat(buf, ' ', padding);
}

int get_sign_char(const char* num_str, s21_format_info* info) {
  if (IS_NEGATIVE(num_str)) return '-';
  if (info->flag_plus && s21_strchr("di", info->specifer)) return '+';
  if (info->flag_space && s21_strchr("di", info->specifer)) return ' ';
  return 0;
}

int get_prefix(char* prefix, s21_format_info* info, int is_zero,
               int leading_zeros) {
  int len = 0;

  if (info->flag_lattice && !is_zero) {
    if (info->specifer == 'o' && leading_zeros == 0)
      prefix[len++] = '0';
    else if (info->specifer == 'x') {
      prefix[len++] = '0';
      prefix[len++] = 'x';
    } else if (info->specifer == 'X') {
      prefix[len++] = '0';
      prefix[len++] = 'X';
    }
  }

  prefix[len] = '\0';
  return len;
}

void write_int_content(char** buf, int sign, const char* prefix, int prefix_len,
                       const char* num_str, int num_len, int leading_zeros,
                       int skip_num) {
  if (sign) buffer_add_char(buf, sign);
  buffer_add_string(buf, prefix, prefix_len);
  buffer_add_repeat(buf, '0', leading_zeros);
  if (!skip_num) buffer_add_string(buf, num_str, num_len);
}

void write_int_left(char** buf, int sign, const char* prefix, int prefix_len,
                    const char* num_str, int num_len, int leading_zeros,
                    int padding, int skip_num) {
  write_int_content(buf, sign, prefix, prefix_len, num_str, num_len,
                    leading_zeros, skip_num);
  buffer_add_repeat(buf, ' ', padding);
}

void write_int_right_zero(char** buf, int sign, const char* prefix,
                          int prefix_len, const char* num_str, int num_len,
                          int leading_zeros, int padding, int skip_num) {
  if (sign) buffer_add_char(buf, sign);
  buffer_add_string(buf, prefix, prefix_len);
  buffer_add_repeat(buf, '0', padding);
  buffer_add_repeat(buf, '0', leading_zeros);
  if (!skip_num) buffer_add_string(buf, num_str, num_len);
}

void write_int_right(char** buf, int sign, const char* prefix, int prefix_len,
                     const char* num_str, int num_len, int leading_zeros,
                     int padding, int skip_num) {
  buffer_add_repeat(buf, ' ', padding);
  write_int_content(buf, sign, prefix, prefix_len, num_str, num_len,
                    leading_zeros, skip_num);
}

void format_integer(char** buf, const char* num_str, s21_format_info* info) {
  int sign = get_sign_char(num_str, info);
  if (IS_NEGATIVE(num_str)) num_str++;
  int is_zero = IS_ZERO(num_str);
  int num_len = (int)s21_strlen(num_str);
  int precision = info->precision < 0 ? 1 : info->precision;
  int skip_output = (precision == 0 && is_zero);
  if (skip_output) num_len = 0;

  int leading_zeros = precision > num_len ? precision - num_len : 0;
  char prefix[4] = "";
  int prefix_len = get_prefix(prefix, info, is_zero, leading_zeros);

  int content_len = (sign ? 1 : 0) + prefix_len + leading_zeros + num_len;
  int padding = info->width > content_len ? info->width - content_len : 0;
  int use_zero_pad = (info->flag_null && info->precision < 0);

  if (info->flag_minus)
    write_int_left(buf, sign, prefix, prefix_len, num_str, num_len,
                   leading_zeros, padding, skip_output);
  else if (use_zero_pad)
    write_int_right_zero(buf, sign, prefix, prefix_len, num_str, num_len,
                         leading_zeros, padding, skip_output);
  else
    write_int_right(buf, sign, prefix, prefix_len, num_str, num_len,
                    leading_zeros, padding, skip_output);
}

void write_float_left(char** buf, int sign, const char* num_str, int num_len,
                      int padding) {
  if (sign) buffer_add_char(buf, sign);
  buffer_add_string(buf, num_str, num_len);
  buffer_add_repeat(buf, ' ', padding);
}

void write_float_right(char** buf, int sign, const char* num_str, int num_len,
                       int padding, char pad_char) {
  if (pad_char == '0') {
    if (sign) buffer_add_char(buf, sign);
    buffer_add_repeat(buf, '0', padding);
  } else {
    buffer_add_repeat(buf, ' ', padding);
    if (sign) buffer_add_char(buf, sign);
  }
  buffer_add_string(buf, num_str, num_len);
}

void format_float(char** buf, const char* num_str, s21_format_info* info) {
  int is_negative = IS_NEGATIVE(num_str);
  if (is_negative) num_str++;

  int num_len = (int)s21_strlen(num_str);

  int sign = 0;
  if (is_negative)
    sign = '-';
  else if (info->flag_plus)
    sign = '+';
  else if (info->flag_space)
    sign = ' ';

  int sign_len = sign ? 1 : 0;
  int content_len = sign_len + num_len;
  int padding = info->width > content_len ? info->width - content_len : 0;
  char pad_char = info->flag_null ? '0' : ' ';

  if (info->flag_minus)
    write_float_left(buf, sign, num_str, num_len, padding);
  else
    write_float_right(buf, sign, num_str, num_len, padding, pad_char);
}

void format_pointer(char** buf, const char* addr_str, s21_format_info* info) {
  int num_len = (int)s21_strlen(addr_str);
  int content_len = 2 + num_len;
  int padding = info->width > content_len ? info->width - content_len : 0;

  if (!info->flag_minus && padding > 0) buffer_add_repeat(buf, ' ', padding);

  buffer_add_string(buf, "0x", 2);
  buffer_add_string(buf, addr_str, num_len);

  if (info->flag_minus && padding > 0) buffer_add_repeat(buf, ' ', padding);
}

int s21_format_value(char** buf, const char* converted, s21_format_info* info) {
  int result = 0;

  switch (info->specifer) {
    case 'c':
      format_char(buf, converted[0], info);
      break;
    case 's':
      format_string(buf, converted, info);
      break;
    case '%':
      format_percent(buf, info);
      break;
    case 'd':
    case 'i':
    case 'u':
    case 'o':
    case 'x':
    case 'X':
      format_integer(buf, converted, info);
      break;
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      format_float(buf, converted, info);
      break;
    case 'p':
      format_pointer(buf, converted, info);
      break;
    default:
      result = -1;
      break;
  }

  return result;
}