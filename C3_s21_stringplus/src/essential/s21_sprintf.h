#ifndef S21_SPRINTF_H
#define S21_SPRINTF_H

#include <stdarg.h>

#define S21_NULL (void*)0
typedef unsigned long s21_size;

#define IS_NEGATIVE(str) ((str)[0] == '-')
#define IS_ZERO(str) ((str)[0] == '0' && (str)[1] == '\0')

typedef struct {
  int flag_minus;
  int flag_plus;
  int flag_space;
  int flag_lattice;
  int flag_null;

  int width;
  int width_from_arg;
  int precision;
  int precision_from_arg;
  char length;

  char specifer;
} s21_format_info;

void buffer_add_char(char** buf, char c);
void buffer_add_string(char** buf, const char* str, s21_size len);
void buffer_add_repeat(char** buf, char c, int count);
void format_char(char** buf, char c, s21_format_info* info);
void format_string(char** buf, const char* str, s21_format_info* info);
void format_percent(char** buf, s21_format_info* info);
int get_sign_char(const char* num_str, s21_format_info* info);
int get_prefix(char* prefix, s21_format_info* info, int is_zero,
               int leading_zeros);
void write_int_content(char** buf, int sign, const char* prefix, int prefix_len,
                       const char* num_str, int num_len, int leading_zeros,
                       int skip_num);
void write_int_left(char** buf, int sign, const char* prefix, int prefix_len,
                    const char* num_str, int num_len, int leading_zeros,
                    int padding, int skip_num);
void write_int_right_zero(char** buf, int sign, const char* prefix,
                          int prefix_len, const char* num_str, int num_len,
                          int leading_zeros, int padding, int skip_num);
void write_int_right(char** buf, int sign, const char* prefix, int prefix_len,
                     const char* num_str, int num_len, int leading_zeros,
                     int padding, int skip_num);
void format_integer(char** buf, const char* num_str, s21_format_info* info);
void write_float_left(char** buf, int sign, const char* num_str, int num_len,
                      int padding);
void write_float_right(char** buf, int sign, const char* num_str, int num_len,
                       int padding, char pad_char);
void format_float(char** buf, const char* num_str, s21_format_info* info);
void format_pointer(char** buf, const char* addr_str, s21_format_info* info);
int s21_format_value(char** buf, const char* converted, s21_format_info* info);
char* s21_parse_format(char* format, s21_format_info* info);
char* s21_convert_format(char* format, s21_format_info* info, char** str,
                         va_list* args);
void s21_process_width_precision(s21_format_info* info, va_list* args);
void s21_handler(s21_format_info* info, char* converted, va_list* args);

#endif