/** @file
 * Interfejs pomocniczych funkcje do działań na numerach telefonów.
 *
 * @author Antoni Bryk <ab438254@mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 2022
 */

#ifndef PHONE_NUMBERS_PHONE_NUMBERS_OPERATIONS_H
#define PHONE_NUMBERS_PHONE_NUMBERS_OPERATIONS_H

#include <stdbool.h>
#include <stdlib.h>

/** @brief Zwraca wartość liczbową cyfry.
 * Zwraca wartość liczbową znaku @p digit reprezentującego cyfrę numeru telefonu.
 * @param[in] digit - znak reprezentujący cyfrę numeru.
 * @return Liczba będąca wartością cyfry numeru telefonu.
 */
int digitToOrder(char digit);

/** @brief Wyznacza długość numeru.
 * Wyznacza długość numeru @p number.
 * @param[in] number - wskaźnik na napis reprezentujący numer.
 * @return Długość numeru lub 0 jeśli wskaźnik @p number jest pusty lub,
 *         nie reprezentuje on poprawnego numeru.
 */
size_t numberLength(char const *number); //TODO skomentowac

/** @brief Tworzy scalenie dwóch numerów.
 * Tworzy napis będący scaleniem dwóch numerów @p num1 i @p num2.
 * @param[in] num1 - wskaźnik na napis reprezentujący pierwszy numer do scalenia;
 * @param[in] num2 - wskaźnik na napis reprezentujący drugi numer do scalenia;
 * @return Wskaźnik na napis reprezentujący scalenie dwóch numerów. Wartość NULL, jeśli
 *         nie udało się alokować pamięci.
 */
char *combineNumbers(char const *num1, char const *num2);

/** @brief Sprawdza czy dwa numery są identyczne.
 * Sprawdza czy @p num1 jest taki sam jak @p num2.
 * @param[in] num1 - wskaźnik na napis reprezentujący pierwszy numer;
 * @param[in] num2 - wskaźnik na napis reprezentujący drugi numer;
 * @return Wartość @p true, jeśli numery są identyczne.
 *         Wartość @p false, jeśli numery nie są identyczne.
 */
bool areNumbersIndentical(char const *num1, char const *num2);

/** @brief Tworzy kopię numeru.
 * Tworzy kopię numeru @p number.
 * @param[in] number - wskaźnik na napis reprezentujący numer do skopiowania;
 * @return Wskaźnik na napis będący kopią numberu @p number lub NULL, gdy nie
 *         udało się alkować pamięci.
 */
char *makeCopy(char const *number);

/** @brief Sprawdza czy numer zaczyna się od danego prefixu.
 * Sprawdza czy @p number zaczyna się od prefixu @p prefix.
 * @param[in] number - wskaźnik na napis reprezentujący numer telefonu;
 * @param[in] prefix - wskaźnik na napis reprezentujący prefix;
 * @return Wartość @p true, jeśli numer zaczyna się od prefixu.
 *         Wartość @p false, jeśli numery nie zaczyna się od prefixu.
 */
bool startsWith(char const *number, char const *prefix);

/** @brief Porównuje dwa numery telefonu.
 * Porównuje czy numer @p num1 jest dalej leksykograficznie od numeru @p num2.
 * @param[in] num1 - wskaźnik na napis reprezentujący pierwszy numer;
 * @param[in] num2 - wskaźnik na napis reprezentujący drugi numer;
 * @return Wartość @p true, jeśli numer @p num1 jest leksykograficznie po numerze @p num2.
 *         Wartość @p false, w przeciwnym przypadku.
 */
bool compareNumbers(char const *num1, char const *num2);

#endif //PHONE_NUMBERS_PHONE_NUMBERS_OPERATIONS_H
