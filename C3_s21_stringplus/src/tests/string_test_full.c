#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

// mem tests
START_TEST(S21TestForMemchr1) {
  unsigned char buf[] = {1, 2, 3, 4, 5};

  ck_assert_ptr_eq(s21_memchr(buf, 3, sizeof(buf)),
                   memchr(buf, 3, sizeof(buf)));
}
END_TEST

START_TEST(S21TestForMemchr2) {
  unsigned char buf[] = "Hello world";

  ck_assert_ptr_eq(s21_memchr(buf, 'w', sizeof(buf)),
                   memchr(buf, 'w', sizeof(buf)));
}
END_TEST

START_TEST(S21TestForMemchr3) {
  unsigned char buf[] = "Hello world";

  ck_assert_ptr_eq(s21_memchr(buf, 'e', sizeof(buf)),
                   memchr(buf, 'e', sizeof(buf)));
}
END_TEST

START_TEST(S21TestForMemcmp1) {
  const char* str1 = "Hello world";
  const char* str2 = "Hello world";

  ck_assert_int_eq(s21_memcmp(str1, str2, strlen(str1)),
                   memcmp(str1, str2, strlen(str1)));
}
END_TEST

START_TEST(S21TestForMemcmp2) {
  const char* str1 = "Hello world";
  const char* str2 = "Hello worldvsvsdvsdvs";

  ck_assert_int_eq(s21_memcmp(str1, str2, strlen(str1)),
                   memcmp(str1, str2, strlen(str1)));
}
END_TEST

START_TEST(S21TestForMemcmp3) {
  const char* str1 = "Hello world\n";
  const char* str2 = "Hello world";

  ck_assert_int_eq(s21_memcmp(str1, str2, strlen(str1)),
                   memcmp(str1, str2, strlen(str1)));
}
END_TEST

START_TEST(S21TestForMemcpy1) {
  char dest[20];
  char* source = "Hello string";

  ck_assert_ptr_eq(s21_memcpy(dest, source, strlen(source)),
                   memcpy(dest, source, strlen(source)));
}
END_TEST

START_TEST(S21TestForMemcpy2) {
  char dest[5];
  char* source = "ww\nwe";

  ck_assert_ptr_eq(s21_memcpy(dest, source, strlen(source)),
                   memcpy(dest, source, strlen(source)));
}
END_TEST

START_TEST(S21TestForMemcpy3) {
  char dest[15];
  char* source = "s\n\0sas .,a32";

  ck_assert_ptr_eq(s21_memcpy(dest, source, strlen(source)),
                   memcpy(dest, source, strlen(source)));
}
END_TEST

START_TEST(S21TestForMemset1) {
  char str[] = "Hello world";
  char a = 'm';

  ck_assert_ptr_eq(s21_memset(str, a, sizeof(str)),
                   memset(str, a, sizeof(str)));
}
END_TEST

START_TEST(S21TestForMemset2) {
  char str[20];
  int a = 0;

  ck_assert_ptr_eq(s21_memset(str, a, sizeof(str)),
                   memset(str, a, sizeof(str)));
}
END_TEST

START_TEST(S21TestForMemset3) {
  char str[] = " c cuvvv h ibbib";
  char a = '\0';

  ck_assert_ptr_eq(s21_memset(str, a, strlen(str)),
                   memset(str, a, strlen(str)));
}
END_TEST

// search info tests
START_TEST(test_strlen_basic) {
  const char* str = "Hello";

  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strlen_empty) {
  const char* str = "";

  ck_assert_int_eq(s21_strlen(str), strlen(str));
}
END_TEST

START_TEST(test_strncmp_equal) {
  const char* a = "Hello";
  const char* b = "Hello";

  ck_assert_int_eq(s21_strncmp(a, b, 5), strncmp(a, b, 5));
}
END_TEST

START_TEST(test_strncmp_diff) {
  const char* a = "Hello";
  const char* b = "Hellp";

  ck_assert_int_eq(s21_strncmp(a, b, 5), strncmp(a, b, 5));
}
END_TEST

START_TEST(test_strncmp_zero) {
  ck_assert_int_eq(s21_strncmp("abc", "xyz", 0), strncmp("abc", "xyz", 0));
}
END_TEST

START_TEST(test_strcspn_basic) {
  const char* s1 = "abcdef";
  const char* s2 = "xdy";

  ck_assert_int_eq(s21_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

START_TEST(test_strcspn_no_match) {
  const char* s1 = "abcdef";
  const char* s2 = "xyz";

  ck_assert_int_eq(s21_strcspn(s1, s2), strcspn(s1, s2));
}
END_TEST

START_TEST(test_strchr_found) {
  const char* str = "Hello";

  ck_assert_ptr_eq(s21_strchr(str, 'e'), strchr(str, 'e'));
}
END_TEST

START_TEST(test_strchr_not_found) {
  const char* str = "Hello";

  ck_assert_ptr_eq(s21_strchr(str, 'x'), strchr(str, 'x'));
}
END_TEST

START_TEST(test_strrchr_basic) {
  const char* str = "Hello Hello";

  ck_assert_ptr_eq(s21_strrchr(str, 'l'), strrchr(str, 'l'));
}
END_TEST

START_TEST(test_strpbrk_basic) {
  const char* s1 = "abcdef";
  const char* s2 = "xdy";

  ck_assert_ptr_eq(s21_strpbrk(s1, s2), strpbrk(s1, s2));
}
END_TEST

START_TEST(test_strpbrk_none) {
  ck_assert_ptr_eq(s21_strpbrk("abc", "xyz"), strpbrk("abc", "xyz"));
}
END_TEST

START_TEST(test_strstr_basic) {
  const char* h = "Hello world";
  const char* n = "world";

  ck_assert_ptr_eq(s21_strstr(h, n), strstr(h, n));
}
END_TEST

START_TEST(test_strstr_empty_needle) {
  const char* h = "Hello";

  ck_assert_ptr_eq(s21_strstr(h, ""), strstr(h, ""));
}
END_TEST

// copy tests
START_TEST(s21TestStrncat) {
  char dest1[50] = "Hello";
  char dest2[50] = "Hello";

  ck_assert_str_eq(s21_strncat(dest1, " World", 3),
                   strncat(dest2, " World", 3));

  ck_assert_str_eq(s21_strncat(dest1, "!!!", 2), strncat(dest2, "!!!", 2));

  ck_assert_str_eq(s21_strncat(dest1, "Yay", 0), strncat(dest2, "Yay", 0));
}
END_TEST

START_TEST(s21TestStrncatEmptySrc) {
  char dest1[50] = "Test";
  char dest2[50] = "Test";

  ck_assert_str_eq(s21_strncat(dest1, "", 5), strncat(dest2, "", 5));

  ck_assert_str_eq(s21_strncat(dest1, "", 0), strncat(dest2, "", 0));
}
END_TEST

START_TEST(s21TestStrncatEmptyDest) {
  char dest1[50] = "";
  char dest2[50] = "";

  ck_assert_str_eq(s21_strncat(dest1, "Yep", 1), strncat(dest2, "Yep", 1));

  ck_assert_str_eq(s21_strncat(dest1, "Too long", 10),
                   strncat(dest2, "Too long", 10));
}
END_TEST

START_TEST(s21TestStrncatNMoreThanSrc) {
  char dest1[50] = "Hi";
  char dest2[50] = "Hi";

  ck_assert_str_eq(s21_strncat(dest1, "World", 10),
                   strncat(dest2, "World", 10));
}
END_TEST

START_TEST(s21TestStrncpy) {
  char dest1[50];
  char dest2[50];

  s21_strncpy(dest1, "Hello", 2);
  dest1[2] = '\0';
  strncpy(dest2, "Hello", 2);
  dest2[2] = '\0';
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(s21TestStrncpyFullCopy) {
  char dest1[50];
  char dest2[50];

  s21_strncpy(dest1, "Hello", 10);
  strncpy(dest2, "Hello", 10);
  ck_assert_mem_eq(dest1, dest2, 10);
}
END_TEST

START_TEST(s21TestStrncpyZeroN) {
  char dest1[50] = "XXXX";
  char dest2[50] = "XXXX";

  volatile s21_size n = 0;

  s21_strncpy(dest1, "Hello", n);
  strncpy(dest2, "Hello", n);

  ck_assert_mem_eq(dest1, dest2, sizeof(dest1));
}
END_TEST

START_TEST(s21TestStrncpyEmptySrc) {
  char dest1[50] = {0};
  char dest2[50] = {0};

  s21_size n1 = 5;
  s21_strncpy(dest1, "", n1);
  strncpy(dest2, "", n1);
  ck_assert_mem_eq(dest1, dest2, n1);

  volatile s21_size n2 = 0;
  s21_strncpy(dest1, "", n2);
  strncpy(dest2, "", n2);
  ck_assert_mem_eq(dest1, dest2, sizeof(dest1));
}
END_TEST

START_TEST(s21TestStrncpyExactLength) {
  char dest1[50];
  char dest2[50];

  s21_strncpy(dest1, "Test", 4);
  dest1[4] = '\0';
  strncpy(dest2, "Test", 4);
  dest2[4] = '\0';
  ck_assert_str_eq(dest1, dest2);
}
END_TEST

// special tests
START_TEST(s21TestTokenizerWhenNormalStrOne) {
  char str1[] = ";;Hello-world;;";
  char str2[] = ";;Hello-world;;";
  const char delim[] = "-;";

  ck_assert_str_eq(s21_strtok(str1, delim), strtok(str2, delim));
  ck_assert_str_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_ptr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
}
END_TEST

START_TEST(s21TestTokenizerWhenNormalStrTwo) {
  char str1[] = ";;Hello- a.b world;;";
  char str2[] = ";;Hello- a.b world;;";
  const char delim[] = "-; .";

  ck_assert_str_eq(s21_strtok(str1, delim), strtok(str2, delim));
  ck_assert_str_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_str_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_str_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
}
END_TEST

START_TEST(s21TestTokenizerWhenNormalStrThree) {
  char str1[] = "Value1,,,Value2,,Value";
  char str2[] = "Value1,,,Value2,,Value";
  const char delim[] = ",";

  ck_assert_str_eq(s21_strtok(str1, delim), strtok(str2, delim));
  ck_assert_str_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_str_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
  ck_assert_ptr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
}
END_TEST

START_TEST(s21TestTokenizerWhenOnlyDelim) {
  char str1[] = "-..-..-.---..";
  char str2[] = "-..-..-.---..";
  const char delim[] = "-.";

  ck_assert_ptr_eq(s21_strtok(str1, delim), strtok(str2, delim));
  ck_assert_ptr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
}
END_TEST

START_TEST(s21TestTokenizerWhenStrEmpty) {
  char str1[] = "";
  const char delim[] = "-_! ";

  ck_assert_ptr_eq(s21_strtok(str1, delim), strtok(str1, delim));
  ck_assert_ptr_eq(s21_strtok(NULL, delim), strtok(NULL, delim));
}
END_TEST

START_TEST(s21TestStrErrWhenErrnoMoreThanMaxNumLinux) {
  ck_assert_str_eq(s21_strerror(134), strerror(134));
  ck_assert_str_eq(s21_strerror(1000), strerror(1000));
}
END_TEST

START_TEST(s21TestStrErrWhenErrnoLessThan0Linux) {
  ck_assert_str_eq(s21_strerror(-1), strerror(-1));
  ck_assert_str_eq(s21_strerror(-1000), strerror(-1000));
}
END_TEST

START_TEST(s21TestStrErrWhenErrnoMormalLinux) {
  ck_assert_str_eq(s21_strerror(21), strerror(21));
  ck_assert_str_eq(s21_strerror(121), strerror(121));
}
END_TEST
// sprintf tests----------------------------------------------------------------
/* %c */
START_TEST(test_sprintf_char_width) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%5c", 'A');
  sprintf(b2, "%5c", 'A');
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_char_minus) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%-5c", 'A');
  sprintf(b2, "%-5c", 'A');
  ck_assert_str_eq(b1, b2);
}
END_TEST

/* %s */
START_TEST(test_sprintf_string_precision) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%.3s", "Hello");
  sprintf(b2, "%.3s", "Hello");
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_string_width) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%10s", "Hi");
  sprintf(b2, "%10s", "Hi");
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_string_minus) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%-10s", "Hi");
  sprintf(b2, "%-10s", "Hi");
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_string_width_precision) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%10.3s", "Hello");
  sprintf(b2, "%10.3s", "Hello");
  ck_assert_str_eq(b1, b2);
}
END_TEST

/* %d и %i */

START_TEST(test_sprintf_int_negative) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%d", -123);
  sprintf(b2, "%d", -123);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_int_zero) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%d", 0);
  sprintf(b2, "%d", 0);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_int_plus) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%+d", 123);
  sprintf(b2, "%+d", 123);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_int_space) {
  char b1[256], b2[256];
  s21_sprintf(b1, "% d", 123);
  sprintf(b2, "% d", 123);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_int_width) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%10d", 123);
  sprintf(b2, "%10d", 123);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_int_width_minus) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%-10d", 123);
  sprintf(b2, "%-10d", 123);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_int_width_zero) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%010d", 123);
  sprintf(b2, "%010d", 123);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_int_precision) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%.5d", 123);
  sprintf(b2, "%.5d", 123);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_int_precision_zero) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%.0d", 0);
  sprintf(b2, "%.0d", 0);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_int_width_precision) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%10.5d", 123);
  sprintf(b2, "%10.5d", 123);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_int_i) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%i", 123);
  sprintf(b2, "%i", 123);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_int_h) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%hd", (short)32767);
  sprintf(b2, "%hd", (short)32767);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_int_l) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%ld", 2147483647L);
  sprintf(b2, "%ld", 2147483647L);
  ck_assert_str_eq(b1, b2);
}
END_TEST

/* %u */
START_TEST(test_sprintf_unsigned_width) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%10u", 123);
  sprintf(b2, "%10u", 123);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_unsigned_precision) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%.5u", 123);
  sprintf(b2, "%.5u", 123);
  ck_assert_str_eq(b1, b2);
}
END_TEST

/* %o */
START_TEST(test_sprintf_octal_hash) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%#o", 123);
  sprintf(b2, "%#o", 123);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_octal_hash_zero) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%#o", 0);
  sprintf(b2, "%#o", 0);
  ck_assert_str_eq(b1, b2);
}
END_TEST

/* %x и %X */
START_TEST(test_sprintf_hex_hash) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%#x", 255);
  sprintf(b2, "%#x", 255);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_hex_hash_upper) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%#X", 255);
  sprintf(b2, "%#X", 255);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_hex_hash_zero) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%#x", 0);
  sprintf(b2, "%#x", 0);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_hex_width_zero) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%010x", 255);
  sprintf(b2, "%010x", 255);
  ck_assert_str_eq(b1, b2);
}
END_TEST

/* %f */
START_TEST(test_sprintf_float_negative) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%f", -3.14);
  sprintf(b2, "%f", -3.14);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_float_plus) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%+f", 3.14);
  sprintf(b2, "%+f", 3.14);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_float_space) {
  char b1[256], b2[256];
  s21_sprintf(b1, "% f", 3.14);
  sprintf(b2, "% f", 3.14);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_float_precision) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%.2f", 3.14159);
  sprintf(b2, "%.2f", 3.14159);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_float_hash) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%#.0f", 3.14);
  sprintf(b2, "%#.0f", 3.14);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_float_width) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%10f", 3.14);
  sprintf(b2, "%10f", 3.14);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_float_width_minus) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%-10f", 3.14);
  sprintf(b2, "%-10f", 3.14);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_float_width_zero) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%010f", 3.14);
  sprintf(b2, "%010f", 3.14);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_float_L) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%Lf", 3.14L);
  sprintf(b2, "%Lf", 3.14L);
  ck_assert_str_eq(b1, b2);
}
END_TEST

/* %e и %E */
START_TEST(test_sprintf_exp_upper) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%E", 1234.5);
  sprintf(b2, "%E", 1234.5);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_exp_precision) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%.2e", 1234.5);
  sprintf(b2, "%.2e", 1234.5);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_exp_negative) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%e", -1234.5);
  sprintf(b2, "%e", -1234.5);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_exp_small) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%e", 0.00123);
  sprintf(b2, "%e", 0.00123);
  ck_assert_str_eq(b1, b2);
}
END_TEST

/* %g и %G */
START_TEST(test_sprintf_g_normal) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%g", 123.456);
  sprintf(b2, "%g", 123.456);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_g_upper) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%G", 0.00001);
  sprintf(b2, "%G", 0.00001);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_g_hash) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%#g", 1.5);
  sprintf(b2, "%#g", 1.5);
  ck_assert_str_eq(b1, b2);
}
END_TEST

/* %p */
START_TEST(test_sprintf_pointer_null) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%p", (void*)NULL);
  sprintf(b2, "%p", (void*)NULL);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_pointer_width) {
  char b1[256], b2[256];
  int x = 42;
  s21_sprintf(b1, "%20p", (void*)&x);
  sprintf(b2, "%20p", (void*)&x);
  ck_assert_str_eq(b1, b2);
}
END_TEST

/* %% */
START_TEST(test_sprintf_percent_simple) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%%");
  sprintf(b2, "%%");
  ck_assert_str_eq(b1, b2);
}
END_TEST

/* * и .* */
START_TEST(test_sprintf_width_star) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%*d", 10, 42);
  sprintf(b2, "%*d", 10, 42);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_width_star_neg) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%*d", -10, 42);
  sprintf(b2, "%*d", -10, 42);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_precision_star) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%.*f", 2, 3.14159);
  sprintf(b2, "%.*f", 2, 3.14159);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_precision_star_neg) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%.*f", -2, 3.14159);
  sprintf(b2, "%.*f", -2, 3.14159);
  ck_assert_str_eq(b1, b2);
}
END_TEST

START_TEST(test_sprintf_width_precision_star) {
  char b1[256], b2[256];
  s21_sprintf(b1, "%*.*f", 10, 2, 3.14159);
  sprintf(b2, "%*.*f", 10, 2, 3.14159);
  ck_assert_str_eq(b1, b2);
}
END_TEST

// special tests-----------------------------------------------
START_TEST(s21TestToUpperBasic) {
  char* result = s21_to_upper("hello world");
  ck_assert_str_eq(result, "HELLO WORLD");
  free(result);
}
END_TEST

START_TEST(s21TestToUpperMixed) {
  char* result = s21_to_upper("HeLLo WoRLd");
  ck_assert_str_eq(result, "HELLO WORLD");
  free(result);
}
END_TEST

START_TEST(s21TestToUpperSpecialChars) {
  char* result = s21_to_upper("hello!@#$%");
  ck_assert_str_eq(result, "HELLO!@#$%");
  free(result);
}
END_TEST

START_TEST(s21TestToUpperNull) {
  char* result = s21_to_upper(S21_NULL);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(s21TestToUpperOnlySpecial) {
  char* result = s21_to_upper("12345!@#$%");
  ck_assert_str_eq(result, "12345!@#$%");
  free(result);
}
END_TEST

START_TEST(test_to_lower_basic) {
  char str[] = "HeLLo, WoRLd!";
  char* res = s21_to_lower(str);

  ck_assert_ptr_nonnull(res);
  ck_assert_str_eq(res, "hello, world!");

  free(res);
}
END_TEST

START_TEST(test_to_lower_alreadylow) {
  char str[] = "already lower";
  char* res = s21_to_lower(str);

  ck_assert_ptr_nonnull(res);
  ck_assert_str_eq(res, str);

  free(res);
}
END_TEST

START_TEST(s21TestInsertEnd) {
  char* result = s21_insert("Hello", " World", 5);
  ck_assert_str_eq(result, "Hello World");
  free(result);
}
END_TEST

START_TEST(s21TestInsertEmptyStr) {
  char* result = s21_insert("Hello", "", 3);
  ck_assert_str_eq(result, "Hello");
  free(result);
}
END_TEST

START_TEST(s21TestInsertEmptySrc) {
  char* result = s21_insert("", "Hello", 0);
  ck_assert_str_eq(result, "Hello");
  free(result);
}
END_TEST

START_TEST(s21TestInsertNullSrc) {
  char* result = s21_insert(S21_NULL, "Hello", 0);
  ck_assert_str_eq(result, "Hello");
  free(result);
}
END_TEST

START_TEST(s21TestInsertNullSrcNonZeroIndex) {
  char* result = s21_insert(S21_NULL, "Hello", 5);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(s21TestInsertNullSrcEmptyStr) {
  char* result = s21_insert(S21_NULL, "", 0);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(s21TestInsertNullStr) {
  char* result = s21_insert("Hello", S21_NULL, 0);
  ck_assert_str_eq(result, "Hello");
  free(result);
}
END_TEST

START_TEST(s21TestInsertBothNull) {
  char* result = s21_insert(S21_NULL, S21_NULL, 0);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(s21TestInsertInvalidIndex) {
  char* result = s21_insert("Hello", "World", 100);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(s21TestInsertAtExactLength) {
  char* result = s21_insert("Test", "!", 4);
  ck_assert_str_eq(result, "Test!");
  free(result);
}
END_TEST

START_TEST(s21TestInsertOneChar) {
  char* result = s21_insert("AC", "B", 1);
  ck_assert_str_eq(result, "ABC");
  free(result);
}
END_TEST

START_TEST(s21TestInsertBothEmpty) {
  char* result = s21_insert("", "", 0);
  ck_assert_str_eq(result, "");
  free(result);
}
END_TEST

START_TEST(s21TestInsertEmptySrcNonZeroIndex) {
  char* result = s21_insert("", "Hello", 1);
  ck_assert_ptr_null(result);
}
END_TEST

START_TEST(test_trim_space) {
  char* res = s21_trim("   Hello World   ", " ");

  ck_assert_ptr_nonnull(res);
  ck_assert_str_eq(res, "Hello World");

  free(res);
}
END_TEST

START_TEST(test_trim_char) {
  char* res = s21_trim("xxxHello Worldxxx", "x");

  ck_assert_ptr_nonnull(res);
  ck_assert_str_eq(res, "Hello World");

  free(res);
}
END_TEST

START_TEST(test_trim_all) {
  char* res = s21_trim("xxxxx", "x");

  ck_assert_ptr_nonnull(res);
  ck_assert_str_eq(res, "");

  free(res);
}
END_TEST

Suite* s21_string_suite(void) {
  Suite* s = suite_create("s21_string");

  TCase* tc_mem = tcase_create("mem");
  TCase* tc_search = tcase_create("search");
  TCase* tc_info = tcase_create("info");
  TCase* tc_copy = tcase_create("copy");
  TCase* tc_special = tcase_create("special");
  TCase* tc_sprintf = tcase_create("sprintf");

  // mem copy tests
  tcase_add_test(tc_mem, S21TestForMemchr1);
  tcase_add_test(tc_mem, S21TestForMemchr2);
  tcase_add_test(tc_mem, S21TestForMemchr3);

  tcase_add_test(tc_mem, S21TestForMemcmp1);
  tcase_add_test(tc_mem, S21TestForMemcmp2);
  tcase_add_test(tc_mem, S21TestForMemcmp3);

  tcase_add_test(tc_mem, S21TestForMemcpy1);
  tcase_add_test(tc_mem, S21TestForMemcpy2);
  tcase_add_test(tc_mem, S21TestForMemcpy3);

  tcase_add_test(tc_mem, S21TestForMemset1);
  tcase_add_test(tc_mem, S21TestForMemset2);
  tcase_add_test(tc_mem, S21TestForMemset3);
  // search and info tests
  // info.c
  tcase_add_test(tc_info, test_strlen_basic);
  tcase_add_test(tc_info, test_strlen_empty);

  tcase_add_test(tc_info, test_strncmp_equal);
  tcase_add_test(tc_info, test_strncmp_diff);
  tcase_add_test(tc_info, test_strncmp_zero);

  tcase_add_test(tc_info, test_strcspn_basic);
  tcase_add_test(tc_info, test_strcspn_no_match);

  // search.c
  tcase_add_test(tc_search, test_strchr_found);
  tcase_add_test(tc_search, test_strchr_not_found);

  tcase_add_test(tc_search, test_strrchr_basic);

  tcase_add_test(tc_search, test_strpbrk_basic);
  tcase_add_test(tc_search, test_strpbrk_none);

  tcase_add_test(tc_search, test_strstr_basic);
  tcase_add_test(tc_search, test_strstr_empty_needle);
  // copy tests
  tcase_add_test(tc_copy, s21TestStrncat);
  tcase_add_test(tc_copy, s21TestStrncatEmptySrc);
  tcase_add_test(tc_copy, s21TestStrncatEmptyDest);
  tcase_add_test(tc_copy, s21TestStrncatNMoreThanSrc);

  tcase_add_test(tc_copy, s21TestStrncpy);
  tcase_add_test(tc_copy, s21TestStrncpyFullCopy);
  tcase_add_test(tc_copy, s21TestStrncpyZeroN);
  tcase_add_test(tc_copy, s21TestStrncpyEmptySrc);
  tcase_add_test(tc_copy, s21TestStrncpyExactLength);

  // special tests
  tcase_add_test(tc_special, s21TestTokenizerWhenNormalStrOne);
  tcase_add_test(tc_special, s21TestTokenizerWhenNormalStrTwo);
  tcase_add_test(tc_special, s21TestTokenizerWhenNormalStrThree);
  tcase_add_test(tc_special, s21TestTokenizerWhenOnlyDelim);
  tcase_add_test(tc_special, s21TestTokenizerWhenStrEmpty);
  tcase_add_test(tc_special, s21TestStrErrWhenErrnoMoreThanMaxNumLinux);
  tcase_add_test(tc_special, s21TestStrErrWhenErrnoLessThan0Linux);
  tcase_add_test(tc_special, s21TestStrErrWhenErrnoMormalLinux);

  tcase_add_test(tc_special, s21TestToUpperBasic);
  tcase_add_test(tc_special, s21TestToUpperMixed);
  tcase_add_test(tc_special, s21TestToUpperSpecialChars);
  tcase_add_test(tc_special, s21TestToUpperNull);
  tcase_add_test(tc_special, s21TestToUpperOnlySpecial);
  tcase_add_test(tc_special, test_to_lower_basic);
  tcase_add_test(tc_special, test_to_lower_alreadylow);

  tcase_add_test(tc_special, s21TestInsertEnd);
  tcase_add_test(tc_special, s21TestInsertEmptyStr);
  tcase_add_test(tc_special, s21TestInsertEmptySrc);
  tcase_add_test(tc_special, s21TestInsertNullSrc);
  tcase_add_test(tc_special, s21TestInsertNullSrcNonZeroIndex);
  tcase_add_test(tc_special, s21TestInsertNullSrcEmptyStr);
  tcase_add_test(tc_special, s21TestInsertNullStr);
  tcase_add_test(tc_special, s21TestInsertBothNull);
  tcase_add_test(tc_special, s21TestInsertInvalidIndex);
  tcase_add_test(tc_special, s21TestInsertAtExactLength);
  tcase_add_test(tc_special, s21TestInsertOneChar);
  tcase_add_test(tc_special, s21TestInsertBothEmpty);
  tcase_add_test(tc_special, s21TestInsertEmptySrcNonZeroIndex);
  tcase_add_test(tc_special, test_trim_all);
  tcase_add_test(tc_special, test_trim_char);
  tcase_add_test(tc_special, test_trim_space);

  // sprintf tests
  tcase_add_test(tc_sprintf, test_sprintf_char_width);
  tcase_add_test(tc_sprintf, test_sprintf_char_minus);

  tcase_add_test(tc_sprintf, test_sprintf_string_precision);
  tcase_add_test(tc_sprintf, test_sprintf_string_width);
  tcase_add_test(tc_sprintf, test_sprintf_string_minus);
  tcase_add_test(tc_sprintf, test_sprintf_string_width_precision);

  tcase_add_test(tc_sprintf, test_sprintf_int_negative);
  tcase_add_test(tc_sprintf, test_sprintf_int_zero);
  tcase_add_test(tc_sprintf, test_sprintf_int_plus);
  tcase_add_test(tc_sprintf, test_sprintf_int_space);
  tcase_add_test(tc_sprintf, test_sprintf_int_width);
  tcase_add_test(tc_sprintf, test_sprintf_int_width_minus);
  tcase_add_test(tc_sprintf, test_sprintf_int_width_zero);
  tcase_add_test(tc_sprintf, test_sprintf_int_precision);
  tcase_add_test(tc_sprintf, test_sprintf_int_precision_zero);
  tcase_add_test(tc_sprintf, test_sprintf_int_width_precision);
  tcase_add_test(tc_sprintf, test_sprintf_int_i);
  tcase_add_test(tc_sprintf, test_sprintf_int_h);
  tcase_add_test(tc_sprintf, test_sprintf_int_l);

  tcase_add_test(tc_sprintf, test_sprintf_unsigned_width);
  tcase_add_test(tc_sprintf, test_sprintf_unsigned_precision);

  tcase_add_test(tc_sprintf, test_sprintf_octal_hash);
  tcase_add_test(tc_sprintf, test_sprintf_octal_hash_zero);

  tcase_add_test(tc_sprintf, test_sprintf_hex_hash);
  tcase_add_test(tc_sprintf, test_sprintf_hex_hash_upper);
  tcase_add_test(tc_sprintf, test_sprintf_hex_hash_zero);
  tcase_add_test(tc_sprintf, test_sprintf_hex_width_zero);

  tcase_add_test(tc_sprintf, test_sprintf_float_negative);
  tcase_add_test(tc_sprintf, test_sprintf_float_plus);
  tcase_add_test(tc_sprintf, test_sprintf_float_space);
  tcase_add_test(tc_sprintf, test_sprintf_float_precision);
  tcase_add_test(tc_sprintf, test_sprintf_float_hash);
  tcase_add_test(tc_sprintf, test_sprintf_float_width);
  tcase_add_test(tc_sprintf, test_sprintf_float_width_minus);
  tcase_add_test(tc_sprintf, test_sprintf_float_width_zero);
  tcase_add_test(tc_sprintf, test_sprintf_float_L);

  tcase_add_test(tc_sprintf, test_sprintf_exp_upper);
  tcase_add_test(tc_sprintf, test_sprintf_exp_precision);
  tcase_add_test(tc_sprintf, test_sprintf_exp_negative);
  tcase_add_test(tc_sprintf, test_sprintf_exp_small);

  tcase_add_test(tc_sprintf, test_sprintf_g_normal);
  tcase_add_test(tc_sprintf, test_sprintf_g_upper);
  tcase_add_test(tc_sprintf, test_sprintf_g_hash);

  tcase_add_test(tc_sprintf, test_sprintf_pointer_null);
  tcase_add_test(tc_sprintf, test_sprintf_pointer_width);

  tcase_add_test(tc_sprintf, test_sprintf_percent_simple);

  tcase_add_test(tc_sprintf, test_sprintf_width_star);
  tcase_add_test(tc_sprintf, test_sprintf_width_star_neg);
  tcase_add_test(tc_sprintf, test_sprintf_precision_star);
  tcase_add_test(tc_sprintf, test_sprintf_precision_star_neg);
  tcase_add_test(tc_sprintf, test_sprintf_width_precision_star);

  suite_add_tcase(s, tc_mem);
  suite_add_tcase(s, tc_info);
  suite_add_tcase(s, tc_search);
  suite_add_tcase(s, tc_copy);
  suite_add_tcase(s, tc_special);
  suite_add_tcase(s, tc_sprintf);
  suite_add_tcase(s, tc_mem);
  suite_add_tcase(s, tc_info);
  suite_add_tcase(s, tc_search);
  suite_add_tcase(s, tc_copy);
  suite_add_tcase(s, tc_special);
  suite_add_tcase(s, tc_sprintf);

  return s;
}

int main(void) {
  int failsCounter = 0;

  Suite* s;
  SRunner* sr;

  s = s21_string_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);

  failsCounter = srunner_ntests_failed(sr);

  srunner_free(sr);

  return (failsCounter == 0) ? 0 : 1;
}
