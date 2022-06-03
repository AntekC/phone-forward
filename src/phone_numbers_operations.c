/** @file
 * Implementacja pomocniczych funkcje do działań na numerach telefonów.
 *
 * @author Antoni Bryk <ab438254@mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 2022
 */

#include "phone_numbers_operations.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>

/** @brief Wyznacza minimum z dwóch liczb.
 * Wyznacza minimum z dwóch liczb @p a i @p b.
 * @param[in] a – pierwsza liczba.
 * @param[in] b – druga liczba.
 * @return Wartość będącą minimum z dwóch liczb.
 */
static size_t min(size_t a, size_t b) {
    if (a > b) {
        return b;
    } else {
        return a;
    }
}

/** @brief Porównuje dwie cyfry.
 * Porównuje ze sobą dwa znaki @p digit1 i @p digit2, reprezentujące cyfrę numeru telefonu.
 * @param[in] digit1 – pierwsza cyfra.
 * @param[in] digit2 – druga cyfra.
 * @return Wartość dodatnią, jeśli @p digit1 > @p digit2.
 *         Wartość ujemną, jeśli @p digit1 < @p digit2.
 *         Zero, jeśli @p digit1 = @p digit2.
 */
static int compareDigit(char digit1, char digit2) {
    return (digitToOrder(digit1) - digitToOrder(digit2));
}

int digitToOrder(char digit) {
    if (isdigit(digit)) {
        return digit - '0';
    } else if (digit == '*') {
        return 10;
    } else {
        return 11;
    }
}

size_t numberLength(char const *number) {
    size_t answer = 0;
    if (number == NULL) {
        return 0;
    }

    while (isdigit(*number) || *number == '*' || *number == '#') {
        ++answer;
        ++number;
    }

    if (*number != '\0') {
        return 0;
    } else {
        return answer;
    }
}

char *combineNumbers(char const *num1, char const *num2) {
    size_t number1_length = numberLength(num1);
    size_t number2_length = numberLength(num2);
    char *ans = malloc((number1_length + number2_length + 1) * sizeof(char));
    if (ans == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < number1_length; ++i) {
        ans[i] = num1[i];
    }
    for (size_t i = number1_length; i < number1_length + number2_length; ++i) {
        ans[i] = num2[i - number1_length];
    }
    ans[number1_length + number2_length] = '\0';

    return ans;
}

bool areNumbersIndentical(char const *num1, char const *num2) {
    size_t number1_length = numberLength(num1);
    size_t number2_length = numberLength(num2);

    if (number1_length == number2_length && number1_length != 0) {
        while (*num1 != '\0') {
            if (*num1 != *num2) {
                return false;
            } else {
                ++num1;
                ++num2;
            }
        }
        return true;
    } else {
        return false;
    }
}

char *makeCopy(char const *number) {
    size_t number_length = numberLength(number);
    char *ans = malloc(number_length * sizeof(char) + 1);
    if (ans == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < number_length; ++i) {
        ans[i] = number[i];
    }
    ans[number_length] = '\0';

    return ans;
}

bool startsWith(char const *number, char const *prefix) {
    size_t prefix_length = numberLength(prefix);
    size_t number_length = numberLength(number);
    if (prefix_length > number_length) {
        return false;
    }

    for (size_t i = 0; i < prefix_length; ++i) {
        if (*prefix != *number) {
            return false;
        } else {
            ++prefix;
            ++number;
        }
    }

    return true;
}

bool compareNumbers(char const *num1, char const *num2) {
    size_t number1_length = numberLength(num1);
    size_t number2_length = numberLength(num2);

    for (size_t i = 0; i < min(number1_length, number2_length); ++i) {
        if (compareDigit(*num1, *num2) > 0) {
            return true;
        } else if (compareDigit(*num1, *num2) < 0) {
            return false;
        } else {
            ++num1;
            ++num2;
        }
    }

    return (number1_length > number2_length);
}