#ifndef S21_STRING_H
#define S21_STRING_H

#define S21_NULL (void*)0

typedef unsigned long s21_size;

// сначала это
void* s21_memchr(const void* str, int c, s21_size n);
// 1
int s21_memcmp(const void* str1, const void* str2, s21_size n);
// 2
void* s21_memcpy(void* dest, const void* src, s21_size n);
// 3
void* s21_memset(void* str, int c, s21_size n);
// 4
char* s21_strncat(char* dest, const char* src, s21_size n);
// 5
char* s21_strchr(const char* str, int c);
// 6
int s21_strncmp(const char* str1, const char* str2, s21_size n);
// 7 дубликат версий shawannw и norenebo оставлена версия shawannw
char* s21_strncpy(char* dest, const char* src, s21_size n);
// 8
s21_size s21_strcspn(const char* str1, const char* str2);
// 9
char* s21_strerror(int errnum);
// 10 дупликат версий norenebo и tranjimm оставлена версия norenebo
s21_size s21_strlen(const char* str);
// 11
char* s21_strpbrk(const char* str1, const char* str2);
// 12
char* s21_strrchr(const char* str, int c);
// 13
char* s21_strstr(const char* haystack, const char* needle);
// 14
char* s21_strtok(char* str, const char* delim);
// 15
// это потом
// int s21_sscanf(const char *str, const char *format, ...);
// 16
int s21_sprintf(char* str, const char* format, ...);
// 17
// специальные
void* s21_to_upper(const char* str);
// 18
void* s21_to_lower(const char* str);
// 19
void* s21_insert(const char* src, const char* str, s21_size start_index);
// 20
void* s21_trim(const char* src, const char* trim_chars);
// 21
#endif