//
// Created by Antoni Bryk on 01/06/2022.
//

#include "phone_numbers_operations.h"
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

/** @brief Wyznacza długość numeru.
 * Wyznacza długość numeru @p number.
 * @param[in] number - wskaźnik na napis reprezentujący numer.
 * @return Długość numeru lub 0 jeśli wskaźnik @p number jest pusty lub,
 *         nie reprezentuje on poprawnego numeru.
 */
size_t numberLength(char const *number) {
    size_t answer = 0;
    if (number == NULL) {
        return 0;
    }

    while (isdigit(*number)) {
        ++answer;
        ++number;
    }

    if (*number != '\0') {
        return 0;
    } else {
        return answer;
    }
}

/** @brief Tworzy scalenie dwóch numerów.
 * Tworzy napis będący scaleniem dwóch numerów @p num1 i @p num2.
 * @param[in] num1 - wskaźnik na napis reprezentujący pierwszy numer do scalenia;
 * @param[in] num2 - wskaźnik na napis reprezentujący drugi numer do scalenia;
 * @return Wskaźnik na napis reprezentujący scalenie dwóch numerów. Wartość NULL, jeśli
 *         nie udało się alokować pamięci.
 */
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

/** @brief Sprawdza czy dwa numery są identyczne.
 * Sprawdza czy @p num1 jest taki sam jak @p num2.
 * @param[in] num1 - wskaźnik na napis reprezentujący pierwszy numer;
 * @param[in] num2 - wskaźnik na napis reprezentujący drugi numer;
 * @return Wartość @p true, jeśli numery są identyczne.
 *         Wartość @p false, jeśli numery nie są identyczne.
 */
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

/** @brief Tworzy kopię numeru.
 * Tworzy kopię numeru @p number.
 * @param[in] number - wskaźnik na napis reprezentujący numer do skopiowania;
 * @return Wskaźnik na napis będący kopią numberu @p number lub NULL, gdy nie
 *         udało się alkować pamięci.
 */
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

bool startsWith(char const *number, char const *prefix){
    size_t prefix_length = numberLength(prefix);
    size_t number_length = numberLength(number);
    if(prefix_length > number_length){
        return true;
    }

    for(size_t i = 0; i < prefix_length; ++i){
        if(*prefix != *number){
            return false;
        } else {
            ++prefix;
            ++number;
        }
    }
    return true;
}