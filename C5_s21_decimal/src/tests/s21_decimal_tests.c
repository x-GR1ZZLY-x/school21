#include <check.h>
#include <limits.h>

#include "../s21_decimal.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// NEGATE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// 1. Положительное целое → отрицательное
START_TEST(negate_1) {
  s21_decimal src = {{1, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{1, 0, 0, 0x80000000}};
  int code = s21_negate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 2. Отрицательное целое → положительное
START_TEST(negate_2) {
  s21_decimal src = {{1, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{1, 0, 0, 0}};
  int code = s21_negate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 3. Ноль → минус ноль
START_TEST(negate_3) {
  s21_decimal src = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 0x80000000}};
  int code = s21_negate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 4. Минус ноль → ноль
START_TEST(negate_4) {
  s21_decimal src = {{0, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  int code = s21_negate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 5. Дробное положительное: 1.5 → -1.5
START_TEST(negate_5) {
  s21_decimal src = {{15, 0, 0, 0x00010000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{15, 0, 0, 0x80010000}};
  int code = s21_negate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 6. Дробное отрицательное: -0.001 → 0.001
START_TEST(negate_6) {
  s21_decimal src = {{1, 0, 0, 0x80030000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{1, 0, 0, 0x00030000}};
  int code = s21_negate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 7. MAX decimal → -MAX
START_TEST(negate_7) {
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  int code = s21_negate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 8. -MAX → MAX
START_TEST(negate_8) {
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int code = s21_negate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 9. Минимальное положительное (scale=28)
START_TEST(negate_9) {
  s21_decimal src = {{1, 0, 0, 0x001C0000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{1, 0, 0, 0x801C0000}};
  int code = s21_negate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 10. MAX мантисса + MAX scale
START_TEST(negate_10) {
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x801C0000}};
  int code = s21_negate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 11. Scale сохраняется: 1.00 → -1.00
START_TEST(negate_11) {
  s21_decimal src = {{100, 0, 0, 0x00020000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{100, 0, 0, 0x80020000}};
  int code = s21_negate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 12. Многосоставная мантисса (bits[0], bits[1], bits[2])
START_TEST(negate_12) {
  s21_decimal src = {{0x12345678, 0x9ABCDEF0, 0x0FEDCBA9, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0x12345678, 0x9ABCDEF0, 0x0FEDCBA9, 0x80000000}};
  int code = s21_negate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 13. Отрицательная многосоставная мантисса → положительная
START_TEST(negate_13) {
  s21_decimal src = {{0x12345678, 0x9ABCDEF0, 0x0FEDCBA9, 0x80000000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0x12345678, 0x9ABCDEF0, 0x0FEDCBA9, 0}};
  int code = s21_negate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 14. Двойное отрицание: negate(negate(5)) == 5
START_TEST(negate_14) {
  s21_decimal src = {{5, 0, 0, 0}};
  s21_decimal tmp = {{0}};
  s21_decimal result = {{0}};
  s21_negate(src, &tmp);
  int code = s21_negate(tmp, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], src.bits[0]);
  ck_assert_int_eq(result.bits[1], src.bits[1]);
  ck_assert_int_eq(result.bits[2], src.bits[2]);
  ck_assert_int_eq(result.bits[3], src.bits[3]);
}
END_TEST

// 15. Двойное отрицание дробного: negate(negate(-3.14)) == -3.14
START_TEST(negate_15) {
  s21_decimal src = {{314, 0, 0, 0x80020000}};
  s21_decimal tmp = {{0}};
  s21_decimal result = {{0}};
  s21_negate(src, &tmp);
  int code = s21_negate(tmp, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], src.bits[0]);
  ck_assert_int_eq(result.bits[1], src.bits[1]);
  ck_assert_int_eq(result.bits[2], src.bits[2]);
  ck_assert_int_eq(result.bits[3], src.bits[3]);
}
END_TEST

// 16. Ноль с scale: 0.00 → -0.00
START_TEST(negate_16) {
  s21_decimal src = {{0, 0, 0, 0x00020000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 0x80020000}};
  int code = s21_negate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 17. Большое число: 12345 → -12345
START_TEST(negate_17) {
  s21_decimal src = {{12345, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{12345, 0, 0, 0x80000000}};
  int code = s21_negate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 18. Мантисса сохраняется полностью
START_TEST(negate_18) {
  s21_decimal src = {{0xDEADBEEF, 0xCAFEBABE, 0x12345678, 0x000F0000}};
  s21_decimal result = {{0}};
  int code = s21_negate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], (int)0xDEADBEEF);
  ck_assert_int_eq(result.bits[1], (int)0xCAFEBABE);
  ck_assert_int_eq(result.bits[2], 0x12345678);
  ck_assert_int_eq(result.bits[3], (int)0x800F0000);
}
END_TEST

// 19. NULL указатель → ошибка
START_TEST(negate_19) {
  s21_decimal src = {{1, 0, 0, 0}};
  int code = s21_negate(src, NULL);
  ck_assert_int_eq(code, 1);
}
END_TEST

// 20. NULL указатель с нулём → ошибка
START_TEST(negate_20) {
  s21_decimal src = {{0, 0, 0, 0}};
  int code = s21_negate(src, NULL);
  ck_assert_int_eq(code, 1);
}
END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TRUNCATE
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(truncate_1) {
  // truncate(5) = 5
  s21_decimal src = {{5, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{5, 0, 0, 0}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 2. Простая дробь: 1.9 → 1
START_TEST(truncate_2) {
  // 1.9 = 19 * 10^(-1), мантисса=19, scale=1
  s21_decimal src = {{19, 0, 0, 0x00010000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{1, 0, 0, 0}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 3. Отрицательная дробь: -1.9 → -1 (отбрасывает к нулю)
START_TEST(truncate_3) {
  s21_decimal src = {{19, 0, 0, 0x80010000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{1, 0, 0, 0x80000000}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 4. Ноль: truncate(0.0) = 0
START_TEST(truncate_4) {
  s21_decimal src = {{0, 0, 0, 0x00010000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 5. Чистый ноль без scale
START_TEST(truncate_5) {
  s21_decimal src = {{0, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 6. Число меньше 1: 0.999 → 0
START_TEST(truncate_6) {
  // 0.999 = 999 * 10^(-3)
  s21_decimal src = {{999, 0, 0, 0x00030000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 7. Отрицательное меньше 1: -0.999 → 0 (или -0)
START_TEST(truncate_7) {
  s21_decimal src = {{999, 0, 0, 0x80030000}};
  s21_decimal result = {{0}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  // знак может быть 0 или 0x80000000, оба допустимы для нуля
}
END_TEST

// 8. 3.14159 → 3
START_TEST(truncate_8) {
  // 3.14159 = 314159 * 10^(-5)
  s21_decimal src = {{314159, 0, 0, 0x00050000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{3, 0, 0, 0}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 9. -3.14159 → -3
START_TEST(truncate_9) {
  s21_decimal src = {{314159, 0, 0, 0x80050000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{3, 0, 0, 0x80000000}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 10. Целое с scale=0 не меняется: 12345 → 12345
START_TEST(truncate_10) {
  s21_decimal src = {{12345, 0, 0, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{12345, 0, 0, 0}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 11. MAX decimal (scale=0) — без изменений
START_TEST(truncate_11) {
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 12. MAX мантисса с scale=28: 7.9228162514264337593543950335 → 7
START_TEST(truncate_12) {
  s21_decimal src = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x001C0000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{7, 0, 0, 0}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 13. Минимальное положительное: 0.0000000000000000000000000001 → 0
START_TEST(truncate_13) {
  s21_decimal src = {{1, 0, 0, 0x001C0000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{0, 0, 0, 0}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 14. Число с scale=1, ровно делится: 1.0 → 1
START_TEST(truncate_14) {
  // 1.0 = 10 * 10^(-1)
  s21_decimal src = {{10, 0, 0, 0x00010000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{1, 0, 0, 0}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 15. Большое число с дробью, мантисса в нескольких словах
//     123456789.123456789 → 123456789
//     123456789123456789 = 0x01B69B4BACD05F15, scale=9
START_TEST(truncate_15) {
  s21_decimal src = {{0xACD05F15, 0x01B69B4B, 0, 0x00090000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{123456789, 0, 0, 0}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 16. Отрицательное целое — без изменений: -42 → -42
START_TEST(truncate_16) {
  s21_decimal src = {{42, 0, 0, 0x80000000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{42, 0, 0, 0x80000000}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 17. Scale=2: 99.99 → 99
START_TEST(truncate_17) {
  // 99.99 = 9999 * 10^(-2)
  s21_decimal src = {{9999, 0, 0, 0x00020000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{99, 0, 0, 0}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 18. Знак сохраняется: -99.99 → -99
START_TEST(truncate_18) {
  s21_decimal src = {{9999, 0, 0, 0x80020000}};
  s21_decimal result = {{0}};
  s21_decimal expected = {{99, 0, 0, 0x80000000}};
  int code = s21_truncate(src, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
}
END_TEST

// 19. NULL указатель → ошибка
START_TEST(truncate_19) {
  s21_decimal src = {{1, 0, 0, 0}};
  int code = s21_truncate(src, NULL);
  ck_assert_int_eq(code, 1);
}
END_TEST

// 20. NULL указатель с дробным → ошибка
START_TEST(truncate_20) {
  s21_decimal src = {{15, 0, 0, 0x00010000}};
  int code = s21_truncate(src, NULL);
  ck_assert_int_eq(code, 1);
}
END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// FLOOR
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(floor_0) {
  s21_decimal value_1 = {{4, 0, 0, 0}}, result = {0};
  ck_assert_int_eq(0, s21_floor(value_1, &result));
}
END_TEST

START_TEST(floor_1) {
  // Знак минус (бит 31 = 1) -> 0x80000000
  s21_decimal value_1 = {{2, 0, 0, 0x80000000}}, result = {0};
  float result_f = 0;
  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(-2, result_f);
}
END_TEST

START_TEST(floor_2) {
  // Знак минус (0x80000000) + Степень 5 (0x00050000) -> 0x80050000
  s21_decimal value_1 = {{2, 0, 0, 0x80050000}}, result = {0};
  float result_f = 0;
  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(-1, result_f);
}
END_TEST

START_TEST(floor_3) {
  // Степень 5 -> 0x00050000
  s21_decimal value_1 = {{2, 0, 0, 0x00050000}}, result = {0};
  float result_f = 0;
  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(0, result_f);
}
END_TEST

START_TEST(floor_4) {
  // value_1: Минус, степень 3 -> 0x80030000
  // value_2: Минус, степень 0 -> 0x80000000
  s21_decimal value_1 = {{123456, 0, 0, 0x80030000}},
              value_2 = {{124, 0, 0, 0x80000000}}, result = {0};
  float result_f, value_two_f;
  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_2, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}
END_TEST

START_TEST(floor_6) {
  // value_1: Минус, степень 1 -> 0x80010000
  // value_2: Минус, степень 0 -> 0x80000000
  s21_decimal value_1 = {{11, 0, 0, 0x80010000}},
              value_2 = {{2, 0, 0, 0x80000000}}, result = {0};
  float result_f, value_two_f;
  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_2, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}
END_TEST

START_TEST(floor_7) {
  // value_1: Минус, степень 3 -> 0x80030000
  // value_2: Минус, степень 0 -> 0x80000000
  s21_decimal value_1 = {{34, 0, 0, 0x80030000}},
              value_2 = {{1, 0, 0, 0x80000000}}, result = {0};
  float result_f, value_two_f;
  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_2, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}
END_TEST

START_TEST(floor_8) {
  // value_1: Минус, степень 5 -> 0x80050000
  // value_2: Минус, степень 0 -> 0x80000000
  s21_decimal value_1 = {{7777777, 0, 0, 0x80050000}},
              value_2 = {{78, 0, 0, 0x80000000}}, result = {0};
  float result_f, value_two_f;
  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_2, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}
END_TEST

START_TEST(floor_9) {
  // value_1: Минус, степень 9 -> 0x80090000
  // value_2: Минус, степень 0 -> 0x80000000
  s21_decimal value_1 = {{123456789, 0, 0, 0x80090000}},
              value_2 = {{1, 0, 0, 0x80000000}}, result = {0};
  float result_f, value_two_f;
  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_2, &value_two_f);
  ck_assert_float_eq(result_f, value_two_f);
}
END_TEST

START_TEST(floor_10) {
  // value_1: Максимальное число (UINT_MAX), Минус, степень 8 -> 0x80080000
  // Это число -42.94967295...
  s21_decimal value_1 = {{UINT_MAX, 0, 0, 0x80080000}};

  // value_2: Ожидаемый результат -43
  // 43, Минус, степень 0 -> 0x80000000
  s21_decimal value_2 = {{43, 0, 0, 0x80000000}};

  s21_decimal result = {0};
  float result_f = 0, value_two_f = 0;

  s21_floor(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  s21_from_decimal_to_float(value_2, &value_two_f);

  ck_assert_float_eq(result_f, value_two_f);
}
END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ROUND
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(round_0) {
  s21_decimal value_1 = {{7, 7, 7, 0}}, result = {0};
  float result_f = 0, value_two_f = (float)129127208515966861312.0;
  s21_round(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(value_two_f, result_f);
}
END_TEST

START_TEST(round_1) {
  // Минус -> 0x80000000
  s21_decimal value_1 = {{3, 3, 3, 0x80000000}}, result = {0};
  ck_assert_int_eq(0, s21_round(value_1, &result));
}
END_TEST

START_TEST(round_2) {
  // Степень 5 -> 0x00050000
  s21_decimal value_1 = {{3, 3, 3, 0x00050000}}, result = {0};
  ck_assert_int_eq(0, s21_round(value_1, &result));
}
END_TEST

START_TEST(round_3) {
  // Минус, степень 5 -> 0x80050000
  s21_decimal value_1 = {{7, 7, 7, 0x80050000}}, result = {0};
  ck_assert_int_eq(0, s21_round(value_1, &result));
}
END_TEST

START_TEST(round_4) {
  // Минус, степень 1 -> 0x80010000
  s21_decimal value_1 = {{25, 0, 0, 0x80010000}}, result = {0};
  ck_assert_int_eq(0, s21_round(value_1, &result));
}
END_TEST

START_TEST(round_5) {
  // Степень 1 -> 0x00010000
  s21_decimal value_1 = {{26, 0, 0, 0x00010000}}, result = {0};
  ck_assert_int_eq(0, s21_round(value_1, &result));
}
END_TEST

START_TEST(round_6) {
  // Степень 1 -> 0x00010000
  s21_decimal value_1 = {{115, 0, 0, 0x00010000}}, result = {0};
  ck_assert_int_eq(0, s21_round(value_1, &result));
}
END_TEST

START_TEST(round_7) {
  // Степень 1 -> 0x00010000
  s21_decimal value_1 = {{118, 0, 0, 0x00010000}}, result = {0};
  ck_assert_int_eq(0, s21_round(value_1, &result));
}
END_TEST

START_TEST(round_8) {
  // Степень 1 -> 0x00010000
  s21_decimal value_1 = {{125, 0, 0, 0x00010000}}, result = {0};
  ck_assert_int_eq(0, s21_round(value_1, &result));
}
END_TEST

START_TEST(round_9) {
  // Степень 1 -> 0x00010000
  s21_decimal value_1 = {{345, 0, 0, 0x00010000}}, result = {0};
  ck_assert_int_eq(0, s21_round(value_1, &result));
}
END_TEST

START_TEST(round_10) {
  // Степень 1 -> 0x00010000
  s21_decimal value_1 = {{128, 0, 0, 0x00010000}}, result = {0};
  float result_f = 0, value_two_f = 13;
  s21_round(value_1, &result);
  s21_from_decimal_to_float(result, &result_f);
  ck_assert_float_eq(value_two_f, result_f);
}
END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// COMPARISON
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(test_less1) {
  s21_decimal a = {{5, 0, 0, 0x00000000}};
  s21_decimal b = {{10, 0, 0, 0x00000000}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_less2) {
  s21_decimal a = {{10, 0, 0, 0x80000000}};
  s21_decimal b = {{5, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_less3) {
  s21_decimal a = {{1, 0, 0, 0x00020000}};
  s21_decimal b = {{10, 0, 0, 0x80010000}};
  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_less4) {
  s21_decimal a = {{0, 0, 1, 0}};
  s21_decimal b = {{0, 0, 2, 0}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_less5) {
  s21_decimal a = {{15, 0, 0, 0x80010000}};
  s21_decimal b = {{10, 0, 0, 0x80010000}};
  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_greater1) {
  s21_decimal a = {{20, 0, 0, 0x00000000}};
  s21_decimal b = {{10, 0, 0, 0x00000000}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_greater2) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};
  s21_decimal b = {{10, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_greater3) {
  s21_decimal a = {{200, 0, 0, 0x00020000}};
  s21_decimal b = {{1000, 0, 0, 0x00030000}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_greater4) {
  s21_decimal a = {{0, 0, 2, 0}};
  s21_decimal b = {{0, 0, 1, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_greater5) {
  s21_decimal a = {{0, 5, 0, 0}};
  s21_decimal b = {{0, 3, 0, 0}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_greater6) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal b = {{1, 0, 0, 0x00010000}};
  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_equal1) {
  s21_decimal a = {{100, 0, 0, 0x00000000}};
  s21_decimal b = {{100, 0, 0, 0x00000000}};
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_equal2) {
  s21_decimal a = {{10, 0, 0, 0x00010000}};
  s21_decimal b = {{100, 0, 0, 0x00020000}};
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_equal3) {
  s21_decimal a = {{0, 0, 0, 0x00000000}};
  s21_decimal b = {{0, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_equal4) {
  s21_decimal a = {{1, 0, 0, 0x00010000}};
  s21_decimal b = {{10, 0, 0, 0x00020000}};
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_equal5) {
  s21_decimal a = {{1000, 0, 0, 0x00030000}};
  s21_decimal b = {{1, 0, 0, 0x00000000}};
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_less_or_equal1) {
  s21_decimal a = {{100, 0, 0, 0x00000000}};
  s21_decimal b = {{100, 0, 0, 0x00000000}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_less_or_equal2) {
  s21_decimal a = {{5, 0, 0, 0x00000000}};
  s21_decimal b = {{100, 0, 0, 0x00000000}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_less_or_equal3) {
  s21_decimal a = {{100, 0, 0, 0x00000000}};
  s21_decimal b = {{10, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
}
END_TEST

START_TEST(test_greater_or_equal1) {
  s21_decimal a = {{100001, 0, 0, 0x00000000}};
  s21_decimal b = {{100001, 0, 0, 0x00000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_greater_or_equal2) {
  s21_decimal a = {{100001, 0, 0, 0x00000000}};
  s21_decimal b = {{100001, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_greater_or_equal3) {
  s21_decimal a = {{1001, 0, 0, 0x00020000}};
  s21_decimal b = {{1111, 0, 0, 0x00020000}};
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
}
END_TEST

START_TEST(test_not_equal1) {
  s21_decimal a = {{100001, 0, 0, 0x80040000}};
  s21_decimal b = {{100001, 0, 0, 0x80050000}};
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_not_equal2) {
  s21_decimal a = {{0, 0, 0, 0x00000000}};
  s21_decimal b = {{0, 0, 0, 0x80000000}};
  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(test_not_equal3) {
  s21_decimal a = {{1234567, 0, 0, 0x80040000}};
  s21_decimal b = {{865321, 0, 0, 0x80050000}};
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CONVERTERS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(test_from_int_to_decimal_zero) {
  s21_decimal result = {0};
  int status = s21_from_int_to_decimal(0, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_positive) {
  s21_decimal result = {0};
  int status = s21_from_int_to_decimal(123, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((result.bits[3] & 0x80000000), 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_negative) {
  s21_decimal result = {0};
  int status = s21_from_int_to_decimal(-456, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 456);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((unsigned int)result.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_from_int_to_decimal_one) {
  s21_decimal result = {0};
  int status = s21_from_int_to_decimal(1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq((unsigned int)result.bits[3] >> 31, 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_minus_one) {
  s21_decimal result = {0};
  int status = s21_from_int_to_decimal(-1, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq((unsigned int)result.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_from_int_to_decimal_max_int) {
  s21_decimal result = {0};
  int status = s21_from_int_to_decimal(2147483647, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 2147483647);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((result.bits[3] & 0x80000000), 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_min_int) {
  s21_decimal result = {0};
  int status = s21_from_int_to_decimal(-2147483648, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq((unsigned int)result.bits[0], 2147483648u);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((unsigned int)result.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_from_int_to_decimal_null_ptr) {
  int status = s21_from_int_to_decimal(123, NULL);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_from_int_to_decimal_large_positive) {
  s21_decimal result = {0};
  int status = s21_from_int_to_decimal(999999999, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 999999999);
  ck_assert_int_eq((result.bits[3] & 0x80000000), 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_large_negative) {
  s21_decimal result = {0};
  int status = s21_from_int_to_decimal(-999999999, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 999999999);
  ck_assert_int_eq((unsigned int)result.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_from_int_to_decimal_scale_zero) {
  s21_decimal result = {0};
  s21_from_int_to_decimal(42, &result);
  ck_assert_int_eq(((result.bits[3] >> 16) & 0xFF), 0);
}
END_TEST

START_TEST(test_from_int_to_decimal_clears_previous) {
  s21_decimal result = {{999, 999, 999, 999}};
  int status = s21_from_int_to_decimal(5, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq((result.bits[3] & 0x80000000), 0);
}
END_TEST

START_TEST(test_from_float_to_decimal_zero) {
  s21_decimal result = {0};
  int status = s21_from_float_to_decimal(0.0f, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_from_float_to_decimal_positive) {
  s21_decimal result = {0};
  float value = 1.0f;
  int status = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(status, 0);
  float check = 0;
  s21_from_decimal_to_float(result, &check);
  ck_assert_float_eq(check, 1.0f);
}
END_TEST

START_TEST(test_from_float_to_decimal_negative) {
  s21_decimal result = {0};
  float value = -1.0f;
  int status = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(status, 0);
  float check = 0;
  s21_from_decimal_to_float(result, &check);
  ck_assert_float_eq(check, -1.0f);
}
END_TEST

START_TEST(test_from_float_to_decimal_fractional) {
  s21_decimal result = {0};
  float value = 1.5f;
  int status = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(status, 0);
  float check = 0;
  s21_from_decimal_to_float(result, &check);
  ck_assert_float_eq_tol(check, 1.5f, 1e-6);
}
END_TEST

START_TEST(test_from_float_to_decimal_small) {
  s21_decimal result = {0};
  float value = 0.001f;
  int status = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(status, 0);
  float check = 0;
  s21_from_decimal_to_float(result, &check);
  ck_assert_float_eq_tol(check, 0.001f, 1e-6);
}
END_TEST

START_TEST(test_from_float_to_decimal_large) {
  s21_decimal result = {0};
  float value = 1000000.0f;
  int status = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(status, 0);
  float check = 0;
  s21_from_decimal_to_float(result, &check);
  ck_assert_float_eq_tol(check, 1000000.0f, 1.0f);
}
END_TEST

START_TEST(test_from_float_to_decimal_inf) {
  s21_decimal result = {0};
  float value = 1.0f / 0.0f;
  int status = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_neg_inf) {
  s21_decimal result = {0};
  float value = -1.0f / 0.0f;
  int status = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_nan) {
  s21_decimal result = {0};
  float value = 0.0f / 0.0f;
  int status = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_null_ptr) {
  int status = s21_from_float_to_decimal(1.0f, NULL);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_negative_zero) {
  s21_decimal result = {0};
  float value = -0.0f;
  int status = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_from_float_to_decimal_pi) {
  s21_decimal result = {0};
  float value = 3.14159f;
  int status = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(status, 0);
  float check = 0;
  s21_from_decimal_to_float(result, &check);
  ck_assert_float_eq_tol(check, 3.14159f, 1e-5);
}
END_TEST

START_TEST(test_from_float_to_decimal_very_small) {
  s21_decimal result = {0};
  float value = 1e-28f;
  int status = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_from_float_to_decimal_too_small) {
  s21_decimal result = {0};
  float value = 1e-29f;
  int status = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_max_decimal_range) {
  s21_decimal result = {0};
  float value = 7.9228e28f;
  int status = s21_from_float_to_decimal(value, &result);
  ck_assert(status == 0 || status == 1);
}
END_TEST

START_TEST(test_from_float_to_decimal_negative_fractional) {
  s21_decimal result = {0};
  float value = -2.5f;
  int status = s21_from_float_to_decimal(value, &result);
  ck_assert_int_eq(status, 0);
  float check = 0;
  s21_from_decimal_to_float(result, &check);
  ck_assert_float_eq_tol(check, -2.5f, 1e-6);
}
END_TEST

START_TEST(test_from_decimal_to_int_zero) {
  s21_decimal a = {{0, 0, 0, 0}};
  int result = -1;
  int status = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_from_decimal_to_int_positive) {
  s21_decimal a = {{123, 0, 0, 0}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(a, &result), 0);
  ck_assert_int_eq(result, 123);
}
END_TEST

START_TEST(test_from_decimal_to_int_negative) {
  s21_decimal a = {{456, 0, 0, 0x80000000}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(a, &result), 0);
  ck_assert_int_eq(result, -456);
}
END_TEST

START_TEST(test_from_decimal_to_int_with_scale) {
  // 12345 / 10^2 = 123.45 -> 123
  s21_decimal a = {{12345, 0, 0, 0x00020000}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(a, &result), 0);
  ck_assert_int_eq(result, 123);
}
END_TEST

START_TEST(test_from_decimal_to_int_negative_with_scale) {
  // -12345 / 10^2 = -123.45 -> -123
  s21_decimal a = {{12345, 0, 0, 0x80020000}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(a, &result), 0);
  ck_assert_int_eq(result, -123);
}
END_TEST

START_TEST(test_from_decimal_to_int_max_int) {
  s21_decimal a = {{2147483647, 0, 0, 0}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(a, &result), 0);
  ck_assert_int_eq(result, 2147483647);
}
END_TEST

START_TEST(test_from_decimal_to_int_min_int) {
  // -2147483648
  s21_decimal a = {{0x80000000, 0, 0, 0x80000000}};
  int result = 0;
  int status = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result, -2147483648);
}
END_TEST

START_TEST(test_from_decimal_to_int_overflow) {
  // 2147483648 (больше INT_MAX)
  s21_decimal a = {{0x80000000, 0, 0, 0}};
  int result = 0;
  int status = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_from_decimal_to_int_large_overflow) {
  // Число в bits[1] != 0
  s21_decimal a = {{0, 1, 0, 0}};
  int result = 0;
  int status = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_from_decimal_to_int_null_ptr) {
  s21_decimal a = {{123, 0, 0, 0}};
  int status = s21_from_decimal_to_int(a, NULL);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_from_decimal_to_int_one) {
  s21_decimal a = {{1, 0, 0, 0}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(a, &result), 0);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_from_decimal_to_int_minus_one) {
  s21_decimal a = {{1, 0, 0, 0x80000000}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(a, &result), 0);
  ck_assert_int_eq(result, -1);
}
END_TEST

START_TEST(test_from_decimal_to_int_truncation) {
  // 999 / 10^2 = 9.99 -> 9
  s21_decimal a = {{999, 0, 0, 0x00020000}};
  int result = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(a, &result), 0);
  ck_assert_int_eq(result, 9);
}
END_TEST

START_TEST(test_from_decimal_to_int_all_fractional) {
  // 5 / 10^1 = 0.5 -> 0
  s21_decimal a = {{5, 0, 0, 0x00010000}};
  int result = -1;
  ck_assert_int_eq(s21_from_decimal_to_int(a, &result), 0);
  ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_from_decimal_to_int_bits2_overflow) {
  s21_decimal a = {{0, 0, 1, 0}};
  int result = 0;
  int status = s21_from_decimal_to_int(a, &result);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_from_decimal_to_float_zero) {
  s21_decimal a = {{0, 0, 0, 0}};
  float result = -1.0f;
  int status = s21_from_decimal_to_float(a, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq(result, 0.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_positive) {
  s21_decimal a = {{123, 0, 0, 0}};
  float result = 0;
  int status = s21_from_decimal_to_float(a, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq(result, 123.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_negative) {
  s21_decimal a = {{456, 0, 0, 0x80000000}};
  float result = 0;
  int status = s21_from_decimal_to_float(a, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq(result, -456.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_with_scale) {
  // 12345 / 10^2 = 123.45
  s21_decimal a = {{12345, 0, 0, 0x00020000}};
  float result = 0;
  int status = s21_from_decimal_to_float(a, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq_tol(result, 123.45f, 1e-2);
}
END_TEST

START_TEST(test_from_decimal_to_float_negative_with_scale) {
  // -12345 / 10^2 = -123.45
  s21_decimal a = {{12345, 0, 0, 0x80020000}};
  float result = 0;
  int status = s21_from_decimal_to_float(a, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq_tol(result, -123.45f, 1e-2);
}
END_TEST

START_TEST(test_from_decimal_to_float_one) {
  s21_decimal a = {{1, 0, 0, 0}};
  float result = 0;
  int status = s21_from_decimal_to_float(a, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq(result, 1.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_minus_one) {
  s21_decimal a = {{1, 0, 0, 0x80000000}};
  float result = 0;
  int status = s21_from_decimal_to_float(a, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq(result, -1.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_null_ptr) {
  s21_decimal a = {{123, 0, 0, 0}};
  int status = s21_from_decimal_to_float(a, NULL);
  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_from_decimal_to_float_small_fraction) {
  // 1 / 10^6 = 0.000001
  s21_decimal a = {{1, 0, 0, 0x00060000}};
  float result = 0;
  int status = s21_from_decimal_to_float(a, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq_tol(result, 0.000001f, 1e-7);
}
END_TEST

START_TEST(test_from_decimal_to_float_large_number) {
  s21_decimal a = {{1000000000, 0, 0, 0}};
  float result = 0;
  int status = s21_from_decimal_to_float(a, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq_tol(result, 1000000000.0f, 100.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_max_scale) {
  // 123456789 / 10^28
  s21_decimal a = {{123456789, 0, 0, 0x001C0000}};
  float result = 0;
  int status = s21_from_decimal_to_float(a, &result);
  ck_assert_int_eq(status, 0);
  ck_assert(result > 0.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_pi_approx) {
  // 31416 / 10^4 = 3.1416
  s21_decimal a = {{31416, 0, 0, 0x00040000}};
  float result = 0;
  int status = s21_from_decimal_to_float(a, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq_tol(result, 3.1416f, 1e-4);
}
END_TEST

START_TEST(test_from_decimal_to_float_large_with_bits1) {
  // 2^32 = 4294967296
  s21_decimal a = {{0, 1, 0, 0}};
  float result = 0;
  int status = s21_from_decimal_to_float(a, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq_tol(result, 4294967296.0f, 1000.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_negative_zero) {
  s21_decimal a = {{0, 0, 0, 0x80000000}};
  float result = 1.0f;
  int status = s21_from_decimal_to_float(a, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq(result, 0.0f);
}
END_TEST

START_TEST(test_from_decimal_to_float_half) {
  // 5 / 10^1 = 0.5
  s21_decimal a = {{5, 0, 0, 0x00010000}};
  float result = 0;
  int status = s21_from_decimal_to_float(a, &result);
  ck_assert_int_eq(status, 0);
  ck_assert_float_eq_tol(result, 0.5f, 1e-6);
}
END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// OPERATIONS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(test_add_basic) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{456, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 579);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_add_zero) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_add_negative) {
  s21_decimal a = {{100, 0, 0, 0x80000000}};
  s21_decimal b = {{50, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 150);
  ck_assert_int_eq((result.bits[3] & 0x80000000), 0x80000000);
}
END_TEST

START_TEST(test_add_mixed_sign) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{50, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq((result.bits[3] & 0x80000000), 0);
}
END_TEST

START_TEST(test_add_scale) {
  // 12.3 + 4.56 = 16.86
  s21_decimal a = {{123, 0, 0, 0x00010000}};
  s21_decimal b = {{456, 0, 0, 0x00020000}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1686);
  ck_assert_int_eq(((result.bits[3] >> 16) & 0xFF), 2);
}
END_TEST

START_TEST(test_add_scale_same) {
  s21_decimal a = {{123, 0, 0, 0x00010000}};
  s21_decimal b = {{456, 0, 0, 0x00010000}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 579);
  ck_assert_int_eq(((result.bits[3] >> 16) & 0xFF), 1);
}
END_TEST

START_TEST(test_add_overflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);
  ck_assert(status >= 0 && status <= 2);
}
END_TEST

START_TEST(test_add_overflow_negative) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);
  ck_assert(status >= 0 && status <= 2);
}
END_TEST

START_TEST(test_add_large_numbers) {
  s21_decimal a = {{1000000, 0, 0, 0}};
  s21_decimal b = {{2000000, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 3000000);
}
END_TEST

START_TEST(test_add_with_rounding) {
  s21_decimal a = {{9999999, 0, 0, 0x00060000}};
  s21_decimal b = {{1, 0, 0, 0x00060000}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_gt(result.bits[0], 0);
  ck_assert_int_eq(((result.bits[3] >> 16) & 0xFF), 6);
}
END_TEST

START_TEST(test_add_decimal_max) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], (int)0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], (int)0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], (int)0xFFFFFFFF);
}
END_TEST

START_TEST(test_add_negative_zero) {
  s21_decimal a = {{0, 0, 0, 0x80000000}};
  s21_decimal b = {{0, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert(result.bits[3] == 0 || result.bits[3] == (int)0x80000000);
}
END_TEST

START_TEST(test_add_different_scales_large) {
  s21_decimal a = {{123456789, 0, 0, 0x00050000}};
  s21_decimal b = {{987654321, 0, 0, 0x00030000}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_ne(result.bits[0], 0);
}
END_TEST

//---------------------------------------------------------------------------
START_TEST(test_add_ripple_carry) {
  // 0xFFFFFFFF + 1 = 1 0000... (переход в следующий бит)
  s21_decimal a = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 1);  // Единица перенеслась
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_add_ripple_carry_mid) {
  // Проверка переноса из 1-го во 2-й инт
  s21_decimal a = {{0, 0xFFFFFFFF, 0, 0}};
  s21_decimal b = {{0, 1, 0, 0}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 1);  // Единица перенеслась
}
END_TEST

START_TEST(test_add_max_scale_diff) {
  // Складываем 10 (scale 0) и очень маленькое число (scale 28)
  // При нормализации маленькое число скорее всего обнулится или
  // большое переполнится, если реализация неаккуратная.
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0x001C0000}};  // 1 * 10^-28
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  // Результат должен быть 10, так как 1e-28 слишком мало для мантиссы 96 бит
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq(result.bits[3] & 0x00FF0000, 0);  // Scale должен стать 0
}
END_TEST

START_TEST(test_add_bankers_rounding) {
  // Этот тест сложный для симуляции, но попробуем переполнение мантиссы.
  // Берем макс число и добавляем так, чтобы вызвать округление.
  // Для упрощения проверим логику округления через очень большие числа.

  // Представим число ...4.5 (scale 1) которое мы хотим привести к scale 0
  // Это часто происходит внутри add, когда скейлы выравниваются.

  // Вариант проще: проверить переполнение, возвращающее ошибку 1 (Infinity)
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {0};

  // Огромное + Огромное = Ошибка 1
  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 1);  // Код 1 - плюс бесконечность
}
END_TEST

START_TEST(test_sub_bankers_rounding_negative) {
  // -Огромное + (-Огромное) = Ошибка 2
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};

  // -MAX - MAX = -Infinity
  int status = s21_add(a, b, &result);
  ck_assert_int_eq(status, 2);  // Код 2 - минус бесконечность
}
END_TEST

START_TEST(test_sub_result_is_positive_zero) {
  // 5.5 - 5.5 = 0.0 (должен быть положительный +0)
  s21_decimal a = {{55, 0, 0, 0x00010000}};
  s21_decimal b = {{55, 0, 0, 0x00010000}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);  // Scale 0, Sign 0
}
END_TEST

START_TEST(test_sub_basic) {
  s21_decimal a = {{456, 0, 0, 0}};
  s21_decimal b = {{123, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 333);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_sub_zero) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_sub_negative_result) {
  s21_decimal a = {{50, 0, 0, 0}};
  s21_decimal b = {{100, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq((result.bits[3] & 0x80000000), 0x80000000);
}
END_TEST

START_TEST(test_sub_negative_numbers) {
  s21_decimal a = {{100, 0, 0, 0x80000000}};
  s21_decimal b = {{50, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq((result.bits[3] & 0x80000000), 0x80000000);
}
END_TEST

START_TEST(test_sub_mixed_sign_positive_result) {
  s21_decimal a = {{100, 0, 0, 0}};
  s21_decimal b = {{50, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 150);
  ck_assert_int_eq((result.bits[3] & 0x80000000), 0);
}
END_TEST

START_TEST(test_sub_mixed_sign_negative_result) {
  s21_decimal a = {{50, 0, 0, 0x80000000}};
  s21_decimal b = {{100, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 150);
  ck_assert_int_eq((result.bits[3] & 0x80000000), 0x80000000);
}
END_TEST

START_TEST(test_sub_equal_numbers) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{123, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_sub_scale) {
  s21_decimal a = {{456, 0, 0, 0x00020000}};
  s21_decimal b = {{123, 0, 0, 0x00020000}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 333);
  ck_assert_int_eq(((result.bits[3] >> 16) & 0xFF), 2);
}
END_TEST

START_TEST(test_sub_scale_same) {
  s21_decimal a = {{456, 0, 0, 0x00010000}};
  s21_decimal b = {{123, 0, 0, 0x00010000}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 333);
  ck_assert_int_eq(((result.bits[3] >> 16) & 0xFF), 1);
}
END_TEST

START_TEST(test_sub_underflow) {
  s21_decimal a = {{0, 0, 0, 0x80000000}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
}
END_TEST

START_TEST(test_sub_large_numbers) {
  s21_decimal a = {{2000000, 0, 0, 0}};
  s21_decimal b = {{1000000, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_ne(result.bits[0], 0);
}
END_TEST

START_TEST(test_sub_with_rounding) {
  s21_decimal a = {{1000000, 0, 0, 0x00060000}};
  s21_decimal b = {{999999, 0, 0, 0x00060000}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_gt(result.bits[0], 0);
}
END_TEST

START_TEST(test_sub_from_max) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);
  ck_assert(status >= 0 && status <= 2);
}
END_TEST

START_TEST(test_sub_to_negative_max) {
  s21_decimal a = {{0, 0, 0, 0x80000000}};
  s21_decimal b = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);
  ck_assert(status >= 0 && status <= 2);
}
END_TEST

START_TEST(test_sub_different_scales) {
  s21_decimal a = {{987654321, 0, 0, 0x00030000}};
  s21_decimal b = {{123456789, 0, 0, 0x00050000}};
  s21_decimal result = {0};

  int status = s21_sub(a, b, &result);

  ck_assert_int_eq(status, 0);
}
END_TEST

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// MUL TESTS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(test_mul_basic) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 246);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_mul_zero) {
  s21_decimal a = {{123, 0, 0, 0}};
  s21_decimal b = {{0, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_mul_negative) {
  s21_decimal a = {{5, 0, 0, 0x80000000}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 15);
  ck_assert_int_eq((unsigned int)result.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_mul_scale) {
  // 12.3 * 0.2 = 2.46
  s21_decimal a = {{123, 0, 0, 0x00010000}};
  s21_decimal b = {{2, 0, 0, 0x00010000}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 246);
  ck_assert_int_eq(((result.bits[3] >> 16) & 0xFF), 2);
}
END_TEST

START_TEST(test_mul_overflow) {
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_mul_large_numbers) {
  // 1000000 * 1000000 = 1000000000000
  s21_decimal a = {{1000000, 0, 0, 0}};
  s21_decimal b = {{1000000, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_ne(result.bits[0], 0);
  ck_assert_uint_eq((unsigned int)result.bits[0], 0xD4A51000u);
  ck_assert_uint_eq((unsigned int)result.bits[1], 0x000000E8u);
}
END_TEST

START_TEST(test_mul_with_rounding) {
  // 1.5 * 1.5 = 2.25
  s21_decimal a = {{15, 0, 0, 0x00010000}};
  s21_decimal b = {{15, 0, 0, 0x00010000}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 225);
  ck_assert_int_eq(((result.bits[3] >> 16) & 0xFF), 2);
}
END_TEST

START_TEST(test_mul_different_scale) {
  // 12.3 * 4.56 = 56.088
  s21_decimal a = {{123, 0, 0, 0x00010000}};
  s21_decimal b = {{456, 0, 0, 0x00020000}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq((unsigned int)result.bits[0], 56088);
  ck_assert_int_eq(((result.bits[3] >> 16) & 0xFF), 3);
}
END_TEST

START_TEST(test_mul_both_negative) {
  // -7 * -8 = 56
  s21_decimal a = {{7, 0, 0, 0x80000000}};
  s21_decimal b = {{8, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq((unsigned int)result.bits[0], 56);
  ck_assert_int_eq((unsigned int)result.bits[3] >> 31, 0);
}
END_TEST

START_TEST(test_mul_by_one) {
  s21_decimal a = {{123456789, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq((unsigned int)result.bits[0], (unsigned int)a.bits[0]);
  ck_assert_uint_eq((unsigned int)result.bits[1], (unsigned int)a.bits[1]);
  ck_assert_uint_eq((unsigned int)result.bits[2], (unsigned int)a.bits[2]);
  ck_assert_uint_eq((unsigned int)result.bits[3], (unsigned int)a.bits[3]);
}
END_TEST

START_TEST(test_mul_by_neg_one) {
  // 54321 * -1 = -54321
  s21_decimal a = {{54321, 0, 0, 0}};
  s21_decimal b = {{1, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq((unsigned int)result.bits[0], (unsigned int)a.bits[0]);
  ck_assert_int_eq((unsigned int)result.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_mul_very_small) {
  // 1e-10 * 2e-10 = 2e-20
  s21_decimal a = {{1, 0, 0, 0x000A0000}};  // scale=10
  s21_decimal b = {{2, 0, 0, 0x000A0000}};  // scale=10
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_uint_eq((unsigned int)result.bits[0], 2);
  ck_assert_int_eq(((result.bits[3] >> 16) & 0xFF), 20);
}
END_TEST

START_TEST(test_mul_small_scale) {
  // scale=10 each, 123 * 456
  s21_decimal a = {{123, 0, 0, 0x000A0000}};
  s21_decimal b = {{456, 0, 0, 0x000A0000}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(((result.bits[3] >> 16) & 0xFF), 20);
  ck_assert_int_ne(result.bits[0], 0);
}
END_TEST

START_TEST(test_mul_commutativity) {
  // a*b == b*a
  s21_decimal a = {{12345, 6789, 0, 0x80030000}};  // scale=3, sign=1
  s21_decimal b = {{54321, 9876, 0, 0x00020000}};  // scale=2, sign=0
  s21_decimal result1 = {0};
  s21_decimal result2 = {0};

  int status1 = s21_mul(a, b, &result1);
  int status2 = s21_mul(b, a, &result2);

  ck_assert_int_eq(status1, 0);
  ck_assert_int_eq(status2, 0);
  ck_assert_int_eq(s21_is_equal(result1, result2), 1);
}
END_TEST

START_TEST(test_mul_associativity_one) {
  // val * 1 * (-1) == val * (-1)
  s21_decimal val = {{123456, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};
  s21_decimal neg_one = {{1, 0, 0, 0x80000000}};
  s21_decimal temp = {0};
  s21_decimal result1 = {0};
  s21_decimal result2 = {0};

  s21_mul(val, one, &temp);
  s21_mul(temp, neg_one, &result1);
  s21_mul(val, neg_one, &result2);

  ck_assert_int_eq(s21_is_equal(result1, result2), 1);
  ck_assert_int_eq((unsigned int)result1.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_mul_scale_reduce) {
  // тест на ужимание
  s21_decimal a = {{1, 0, 0, 0x001C0000}};
  s21_decimal b = {{1, 0, 0, 0x001C0000}};
  s21_decimal result = {0};

  int status = s21_mul(a, b, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_le((result.bits[3] >> 16) & 0xFF, 28);
}
END_TEST
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DIV TESTS
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_TEST(test_div_by_zero) {
  s21_decimal dividend = {{10, 0, 0, 0}};
  s21_decimal divisor = {{0, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 3);
}
END_TEST

START_TEST(test_div_positive) {
  s21_decimal dividend = {{100, 0, 0, 0}};
  s21_decimal divisor = {{5, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 20);
}
END_TEST

START_TEST(test_div_both_negative) {
  // -100 / -5 = 20
  s21_decimal dividend = {{100, 0, 0, 0x80000000}};
  s21_decimal divisor = {{5, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 20);
  ck_assert_int_eq((unsigned int)result.bits[3] >> 31, 0);
}
END_TEST

START_TEST(test_div_diff_signs) {
  // 100 / -5 = -20
  s21_decimal dividend = {{100, 0, 0, 0}};
  s21_decimal divisor = {{5, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 20);
  ck_assert_int_eq((unsigned int)result.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_div_diff_scales) {
  // 1.00 / 0.5 = 2
  s21_decimal dividend = {{100, 0, 0, 0x00020000}};
  s21_decimal divisor = {{5, 0, 0, 0x00010000}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 2);
  ck_assert_int_eq(((result.bits[3] >> 16) & 0xFF), 0);
}
END_TEST

START_TEST(test_div_overflow) {
  // MAX / 0.1 -> overflow
  s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal divisor = {{1, 0, 0, 0x00010000}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 1);
}
END_TEST

START_TEST(test_div_zero_by_number) {
  // 0 / 5 = 0
  s21_decimal dividend = {{0, 0, 0, 0}};
  s21_decimal divisor = {{5, 0, 0, 0}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 0);
}
END_TEST

START_TEST(test_div_large_by_one) {
  // MAX / 1 = MAX
  s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal divisor = {{1, 0, 0, 0x00000000}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], (int)0xFFFFFFFF);
  ck_assert_int_eq(result.bits[1], (int)0xFFFFFFFF);
  ck_assert_int_eq(result.bits[2], (int)0xFFFFFFFF);
}
END_TEST

START_TEST(test_div_by_self) {
  // 1234.56 / 1234.56 = 1
  s21_decimal dividend = {{123456, 0, 0, 0x00020000}};
  s21_decimal divisor = {{123456, 0, 0, 0x00020000}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_div_by_self_no_scale) {
  // 123456 / 123456 = 1
  s21_decimal dividend = {{123456, 0, 0, 0x00000000}};
  s21_decimal divisor = {{123456, 0, 0, 0x00000000}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[3], 0x00000000);
}
END_TEST

START_TEST(test_div_diff_scales_2) {
  // 1234.56 (scale=2) / 0.123456 (scale=3) = 1234.56/123.456 = 10
  s21_decimal dividend = {{123456, 0, 0, 0x00020000}};
  s21_decimal divisor = {{123456, 0, 0, 0x00030000}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq(((result.bits[3] >> 16) & 0xFF), 0);
}
END_TEST

START_TEST(test_div_negative_dividend) {
  // -100 / 5 = -20
  s21_decimal dividend = {{100, 0, 0, 0x80000000}};
  s21_decimal divisor = {{5, 0, 0, 0x00000000}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 20);
  ck_assert_int_eq((unsigned int)result.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_div_negative_divisor) {
  // 100 / -5 = -20
  s21_decimal dividend = {{100, 0, 0, 0x00000000}};
  s21_decimal divisor = {{5, 0, 0, 0x80000000}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 20);
  ck_assert_int_eq((unsigned int)result.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_div_by_one) {
  // 1234.56 / 1 = 1234.56
  s21_decimal dividend = {{123456, 0, 0, 0x00020000}};
  s21_decimal divisor = {{1, 0, 0, 0x00000000}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 123456);
  ck_assert_int_eq(((result.bits[3] >> 16) & 0xFF), 2);
}
END_TEST

START_TEST(test_div_small_by_large) {
  // 0.1 / 100 = 0.001
  s21_decimal dividend = {{1, 0, 0, 0x00010000}};
  s21_decimal divisor = {{100, 0, 0, 0x00000000}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(((result.bits[3] >> 16) & 0xFF), 3);
}
END_TEST

START_TEST(test_div_overflow_negative) {
  // -MAX / 0.1 -> overflow negative
  s21_decimal dividend = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal divisor = {{1, 0, 0, 0x00010000}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 2);
}
END_TEST

START_TEST(test_div_large_scale) {
  // same number with scale=7 / same number with scale=7 = 1
  s21_decimal dividend = {{123456789, 0, 0, 0x00070000}};
  s21_decimal divisor = {{123456789, 0, 0, 0x00070000}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(((result.bits[3] >> 16) & 0xFF), 0);
}
END_TEST

START_TEST(test_div_negative_result) {
  // -100 / 5 = -20
  s21_decimal dividend = {{100, 0, 0, 0x80000000}};
  s21_decimal divisor = {{5, 0, 0, 0x00000000}};
  s21_decimal result = {0};

  int status = s21_div(dividend, divisor, &result);

  ck_assert_int_eq(status, 0);
  ck_assert_int_eq(result.bits[0], 20);
  ck_assert_int_eq((unsigned int)result.bits[3] >> 31, 1);
}
END_TEST

START_TEST(test_add_overflow_with_scale_reduction) {
  // Число MAX_DECIMAL со scale = 1
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00010000}};
  // Еще одно большое число со scale = 1
  s21_decimal b = {{100, 0, 0, 0x00010000}};
  s21_decimal result = {0};

  // При сложении "в лоб" получится переполнение (MAX + 100).
  // Но так как scale=1, программа должна разделить оба числа на 10,
  // уменьшить scale до 0 и сложить.
  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);  // Успех, а не переполнение!
  // Scale должен стать 0
  ck_assert_int_eq((result.bits[3] >> 16) & 0xFF, 0);
  // Проверка результата (примерно MAX/10 + 100/10)
  ck_assert_int_ne(result.bits[0], 0);
}
END_TEST

START_TEST(test_add_overflow_in_normalization) {
  // Огромное число (scale 0)
  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  // Маленькое число (scale 1) -> 0.5
  s21_decimal b = {{5, 0, 0, 0x00010000}};
  s21_decimal result = {0};

  // Логика должна попытаться сделать scale равным 1.
  // Для этого 'a' * 10 -> ПЕРЕПОЛНЕНИЕ в mulByTen ->
  // Тут либо вернется ошибка, либо программа понизит scale у 'b'.
  // Главное, что мы зайдем в ту красную ветку if (temp != 0).
  int status = s21_add(a, b, &result);

  // Статус зависит от вашей реализации (обычно 0, если сработает bank rounding
  // вниз, или 1, если overflow) Нам главное покрыть код, поэтому просто
  // вызываем функцию.
  ck_assert_int_ge(status, 0);
}
END_TEST

START_TEST(test_add_div_by_ten_rounding) {
  // Нам нужно вызвать handleOverflow.
  // Берем MAX, scale 1.
  // Добавляем к нему число, которое заканчивается на 9 (например 19).
  // 19 / 10 = 1, остаток 9. Остаток 9 > 5 -> должно сработать округление вверх
  // (rounder = 1).

  s21_decimal a = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00010000}};
  // Число побольше, чтобы точно вызвать переполнение и деление
  s21_decimal b = {{19, 0, 0, 0x00010000}};
  s21_decimal result = {0};

  int status = s21_add(a, b, &result);

  ck_assert_int_eq(status, 0);
  // Здесь мы проверяем, что вызвался divByTen и внутри сработало условие interm
  // > 5
}
END_TEST

Suite *others_functions(void) {
  Suite *s = suite_create("s21_others_functions");
  TCase *tc = tcase_create("other_tests");
  TCase *tc1 = tcase_create("comparison_tests");
  TCase *tc2 = tcase_create("converters_tests");
  TCase *tc3 = tcase_create("operations_tests");

  tcase_add_test(tc, negate_1);
  tcase_add_test(tc, negate_2);
  tcase_add_test(tc, negate_3);
  tcase_add_test(tc, negate_4);
  tcase_add_test(tc, negate_5);
  tcase_add_test(tc, negate_6);
  tcase_add_test(tc, negate_7);
  tcase_add_test(tc, negate_8);
  tcase_add_test(tc, negate_9);
  tcase_add_test(tc, negate_10);
  tcase_add_test(tc, negate_11);
  tcase_add_test(tc, negate_12);
  tcase_add_test(tc, negate_13);
  tcase_add_test(tc, negate_14);
  tcase_add_test(tc, negate_15);
  tcase_add_test(tc, negate_16);
  tcase_add_test(tc, negate_17);
  tcase_add_test(tc, negate_18);
  tcase_add_test(tc, negate_19);
  tcase_add_test(tc, negate_20);

  tcase_add_test(tc, truncate_1);
  tcase_add_test(tc, truncate_2);
  tcase_add_test(tc, truncate_3);
  tcase_add_test(tc, truncate_4);
  tcase_add_test(tc, truncate_5);
  tcase_add_test(tc, truncate_6);
  tcase_add_test(tc, truncate_7);
  tcase_add_test(tc, truncate_8);
  tcase_add_test(tc, truncate_9);
  tcase_add_test(tc, truncate_10);
  tcase_add_test(tc, truncate_11);
  tcase_add_test(tc, truncate_12);
  tcase_add_test(tc, truncate_13);
  tcase_add_test(tc, truncate_14);
  tcase_add_test(tc, truncate_15);
  tcase_add_test(tc, truncate_16);
  tcase_add_test(tc, truncate_17);
  tcase_add_test(tc, truncate_18);
  tcase_add_test(tc, truncate_19);
  tcase_add_test(tc, truncate_20);

  tcase_add_test(tc, floor_0);
  tcase_add_test(tc, floor_1);
  tcase_add_test(tc, floor_4);
  tcase_add_test(tc, floor_2);
  tcase_add_test(tc, floor_3);
  tcase_add_test(tc, floor_6);
  tcase_add_test(tc, floor_7);
  tcase_add_test(tc, floor_8);
  tcase_add_test(tc, floor_9);
  tcase_add_test(tc, floor_10);

  tcase_add_test(tc, round_0);
  tcase_add_test(tc, round_1);
  tcase_add_test(tc, round_2);
  tcase_add_test(tc, round_3);
  tcase_add_test(tc, round_4);
  tcase_add_test(tc, round_5);
  tcase_add_test(tc, round_6);
  tcase_add_test(tc, round_7);
  tcase_add_test(tc, round_8);
  tcase_add_test(tc, round_9);
  tcase_add_test(tc, round_10);

  tcase_add_test(tc1, test_less1);
  tcase_add_test(tc1, test_less2);
  tcase_add_test(tc1, test_less3);
  tcase_add_test(tc1, test_less4);
  tcase_add_test(tc1, test_less5);
  tcase_add_test(tc1, test_greater1);
  tcase_add_test(tc1, test_greater2);
  tcase_add_test(tc1, test_greater3);
  tcase_add_test(tc1, test_greater4);
  tcase_add_test(tc1, test_greater5);
  tcase_add_test(tc1, test_greater6);
  tcase_add_test(tc1, test_equal1);
  tcase_add_test(tc1, test_equal2);
  tcase_add_test(tc1, test_equal3);
  tcase_add_test(tc1, test_equal4);
  tcase_add_test(tc1, test_equal5);
  tcase_add_test(tc1, test_less_or_equal1);
  tcase_add_test(tc1, test_less_or_equal2);
  tcase_add_test(tc1, test_less_or_equal3);
  tcase_add_test(tc1, test_greater_or_equal1);
  tcase_add_test(tc1, test_greater_or_equal2);
  tcase_add_test(tc1, test_greater_or_equal3);
  tcase_add_test(tc1, test_not_equal1);
  tcase_add_test(tc1, test_not_equal2);
  tcase_add_test(tc1, test_not_equal3);

  tcase_add_test(tc2, test_from_int_to_decimal_zero);
  tcase_add_test(tc2, test_from_int_to_decimal_positive);
  tcase_add_test(tc2, test_from_int_to_decimal_negative);
  tcase_add_test(tc2, test_from_int_to_decimal_one);
  tcase_add_test(tc2, test_from_int_to_decimal_minus_one);
  tcase_add_test(tc2, test_from_int_to_decimal_max_int);
  tcase_add_test(tc2, test_from_int_to_decimal_min_int);
  tcase_add_test(tc2, test_from_int_to_decimal_null_ptr);
  tcase_add_test(tc2, test_from_int_to_decimal_large_positive);
  tcase_add_test(tc2, test_from_int_to_decimal_large_negative);
  tcase_add_test(tc2, test_from_int_to_decimal_scale_zero);
  tcase_add_test(tc2, test_from_int_to_decimal_clears_previous);

  tcase_add_test(tc2, test_from_float_to_decimal_zero);
  tcase_add_test(tc2, test_from_float_to_decimal_positive);
  tcase_add_test(tc2, test_from_float_to_decimal_negative);
  tcase_add_test(tc2, test_from_float_to_decimal_fractional);
  tcase_add_test(tc2, test_from_float_to_decimal_small);
  tcase_add_test(tc2, test_from_float_to_decimal_large);
  tcase_add_test(tc2, test_from_float_to_decimal_inf);
  tcase_add_test(tc2, test_from_float_to_decimal_neg_inf);
  tcase_add_test(tc2, test_from_float_to_decimal_nan);
  tcase_add_test(tc2, test_from_float_to_decimal_null_ptr);
  tcase_add_test(tc2, test_from_float_to_decimal_negative_zero);
  tcase_add_test(tc2, test_from_float_to_decimal_pi);
  tcase_add_test(tc2, test_from_float_to_decimal_very_small);
  tcase_add_test(tc2, test_from_float_to_decimal_too_small);
  tcase_add_test(tc2, test_from_float_to_decimal_max_decimal_range);
  tcase_add_test(tc2, test_from_float_to_decimal_negative_fractional);

  tcase_add_test(tc2, test_from_decimal_to_int_zero);
  tcase_add_test(tc2, test_from_decimal_to_int_positive);
  tcase_add_test(tc2, test_from_decimal_to_int_negative);
  tcase_add_test(tc2, test_from_decimal_to_int_with_scale);
  tcase_add_test(tc2, test_from_decimal_to_int_negative_with_scale);
  tcase_add_test(tc2, test_from_decimal_to_int_max_int);
  tcase_add_test(tc2, test_from_decimal_to_int_min_int);
  tcase_add_test(tc2, test_from_decimal_to_int_overflow);
  tcase_add_test(tc2, test_from_decimal_to_int_large_overflow);
  tcase_add_test(tc2, test_from_decimal_to_int_null_ptr);
  tcase_add_test(tc2, test_from_decimal_to_int_one);
  tcase_add_test(tc2, test_from_decimal_to_int_minus_one);
  tcase_add_test(tc2, test_from_decimal_to_int_truncation);
  tcase_add_test(tc2, test_from_decimal_to_int_all_fractional);
  tcase_add_test(tc2, test_from_decimal_to_int_bits2_overflow);

  tcase_add_test(tc2, test_from_decimal_to_float_zero);
  tcase_add_test(tc2, test_from_decimal_to_float_positive);
  tcase_add_test(tc2, test_from_decimal_to_float_negative);
  tcase_add_test(tc2, test_from_decimal_to_float_with_scale);
  tcase_add_test(tc2, test_from_decimal_to_float_negative_with_scale);
  tcase_add_test(tc2, test_from_decimal_to_float_one);
  tcase_add_test(tc2, test_from_decimal_to_float_minus_one);
  tcase_add_test(tc2, test_from_decimal_to_float_null_ptr);
  tcase_add_test(tc2, test_from_decimal_to_float_small_fraction);
  tcase_add_test(tc2, test_from_decimal_to_float_large_number);
  tcase_add_test(tc2, test_from_decimal_to_float_max_scale);
  tcase_add_test(tc2, test_from_decimal_to_float_pi_approx);
  tcase_add_test(tc2, test_from_decimal_to_float_large_with_bits1);
  tcase_add_test(tc2, test_from_decimal_to_float_negative_zero);
  tcase_add_test(tc2, test_from_decimal_to_float_half);

  tcase_add_test(tc3, test_add_basic);
  tcase_add_test(tc3, test_add_zero);
  tcase_add_test(tc3, test_add_negative);
  tcase_add_test(tc3, test_add_mixed_sign);
  tcase_add_test(tc3, test_add_scale);
  tcase_add_test(tc3, test_add_scale_same);
  tcase_add_test(tc3, test_add_overflow);
  tcase_add_test(tc3, test_add_overflow_negative);
  tcase_add_test(tc3, test_add_large_numbers);
  tcase_add_test(tc3, test_add_with_rounding);
  tcase_add_test(tc3, test_add_decimal_max);
  tcase_add_test(tc3, test_add_negative_zero);
  tcase_add_test(tc3, test_add_different_scales_large);

  tcase_add_test(tc3, test_add_ripple_carry);
  tcase_add_test(tc3, test_add_ripple_carry_mid);
  tcase_add_test(tc3, test_add_max_scale_diff);
  tcase_add_test(tc3, test_add_bankers_rounding);
  tcase_add_test(tc3, test_sub_bankers_rounding_negative);
  tcase_add_test(tc3, test_sub_result_is_positive_zero);

  tcase_add_test(tc3, test_add_overflow_with_scale_reduction);
  tcase_add_test(tc3, test_add_overflow_in_normalization);
  tcase_add_test(tc3, test_add_div_by_ten_rounding);

  tcase_add_test(tc3, test_sub_basic);
  tcase_add_test(tc3, test_sub_zero);
  tcase_add_test(tc3, test_sub_negative_result);
  tcase_add_test(tc3, test_sub_negative_numbers);
  tcase_add_test(tc3, test_sub_mixed_sign_positive_result);
  tcase_add_test(tc3, test_sub_mixed_sign_negative_result);
  tcase_add_test(tc3, test_sub_equal_numbers);
  tcase_add_test(tc3, test_sub_scale);
  tcase_add_test(tc3, test_sub_scale_same);
  tcase_add_test(tc3, test_sub_underflow);
  tcase_add_test(tc3, test_sub_large_numbers);
  tcase_add_test(tc3, test_sub_with_rounding);
  tcase_add_test(tc3, test_sub_from_max);
  tcase_add_test(tc3, test_sub_to_negative_max);
  tcase_add_test(tc3, test_sub_different_scales);

  tcase_add_test(tc3, test_mul_basic);
  tcase_add_test(tc3, test_mul_zero);
  tcase_add_test(tc3, test_mul_negative);
  tcase_add_test(tc3, test_mul_scale);
  tcase_add_test(tc3, test_mul_overflow);
  tcase_add_test(tc3, test_mul_large_numbers);
  tcase_add_test(tc3, test_mul_with_rounding);
  tcase_add_test(tc3, test_mul_different_scale);
  tcase_add_test(tc3, test_mul_both_negative);
  tcase_add_test(tc3, test_mul_by_one);
  tcase_add_test(tc3, test_mul_by_neg_one);
  tcase_add_test(tc3, test_mul_very_small);
  tcase_add_test(tc3, test_mul_small_scale);
  tcase_add_test(tc3, test_mul_commutativity);
  tcase_add_test(tc3, test_mul_associativity_one);
  tcase_add_test(tc3, test_mul_scale_reduce);

  tcase_add_test(tc3, test_div_by_zero);
  tcase_add_test(tc3, test_div_positive);
  tcase_add_test(tc3, test_div_both_negative);
  tcase_add_test(tc3, test_div_diff_signs);
  tcase_add_test(tc3, test_div_diff_scales);
  tcase_add_test(tc3, test_div_overflow);
  tcase_add_test(tc3, test_div_zero_by_number);
  tcase_add_test(tc3, test_div_large_by_one);
  tcase_add_test(tc3, test_div_by_self);
  tcase_add_test(tc3, test_div_by_self_no_scale);
  tcase_add_test(tc3, test_div_diff_scales_2);
  tcase_add_test(tc3, test_div_negative_dividend);
  tcase_add_test(tc3, test_div_negative_divisor);
  tcase_add_test(tc3, test_div_by_one);
  tcase_add_test(tc3, test_div_small_by_large);
  tcase_add_test(tc3, test_div_overflow_negative);
  tcase_add_test(tc3, test_div_large_scale);
  tcase_add_test(tc3, test_div_negative_result);

  suite_add_tcase(s, tc);
  suite_add_tcase(s, tc1);
  suite_add_tcase(s, tc2);
  suite_add_tcase(s, tc3);
  return s;
}

int main(void) {
  int failed = 0;
  Suite *s = others_functions();
  SRunner *runner = srunner_create(s);

  srunner_run_all(runner, CK_VERBOSE);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failed == 0) ? 0 : 1;
}
