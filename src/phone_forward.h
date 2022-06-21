/** @file
 * Interfejs klasy przechowującej przekierowania numerów telefonicznych
 *
 * @author Marcin Peczarski <marpe@mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 2022
 */

#ifndef __PHONE_FORWARD_H__
#define __PHONE_FORWARD_H__

#include <stdbool.h>
#include <stddef.h>

/**
 * To jest struktura przechowująca przekierowania numerów telefonów.
 */
struct PhoneForward;

/**
 * To jest definicja struktury PhoneForward.
 */
typedef struct PhoneForward PhoneForward;

/**
 * To jest struktura przechowująca ciąg numerów telefonów.
 */
struct PhoneNumbers;
/**
 * To jest definicja struktury PhoneNumbers.
 */
typedef struct PhoneNumbers PhoneNumbers;

/** @brief Tworzy nową strukturę.
 * Tworzy nową strukturę niezawierającą żadnych przekierowań.
 * @return Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *         alokować pamięci.
 */
PhoneForward * phfwdNew(void);

/** @brief Usuwa strukturę.
 * Usuwa strukturę wskazywaną przez @p pf. Nic nie robi, jeśli wskaźnik ten ma
 * wartość NULL.
 * @param[in] pf – wskaźnik na usuwaną strukturę.
 */
void phfwdDelete(PhoneForward *pf);

/** @brief Dodaje przekierowanie.
 * Dodaje przekierowanie wszystkich numerów mających prefiks @p num1, na numery,
 * w których ten prefiks zamieniono odpowiednio na prefiks @p num2. Każdy numer
 * jest swoim własnym prefiksem. Jeśli wcześniej zostało dodane przekierowanie
 * z takim samym parametrem @p num1, to jest ono zastępowane.
 * Relacja przekierowania numerów nie jest przechodnia.
 * @param[in,out] pf – wskaźnik na strukturę przechowującą przekierowania
 *                     numerów;
 * @param[in] num1   – wskaźnik na napis reprezentujący prefiks numerów
 *                     przekierowywanych;
 * @param[in] num2   – wskaźnik na napis reprezentujący prefiks numerów,
 *                     na które jest wykonywane przekierowanie.
 * @return Wartość @p true, jeśli przekierowanie zostało dodane.
 *         Wartość @p false, jeśli wystąpił błąd, np. podany napis nie
 *         reprezentuje numeru, oba podane numery są identyczne lub nie udało
 *         się alokować pamięci.
 */
bool phfwdAdd(PhoneForward *pf, char const *num1, char const *num2);

/** @brief Usuwa przekierowania.
 * Usuwa wszystkie przekierowania, w których parametr @p num jest prefiksem
 * parametru @p num1 użytego przy dodawaniu. Jeśli nie ma takich przekierowań
 * lub napis nie reprezentuje numeru, nic nie robi.
 * @param[in,out] pf – wskaźnik na strukturę przechowującą przekierowania
 *                     numerów;
 * @param[in] num    – wskaźnik na napis reprezentujący prefiks numerów.
 */
void phfwdRemove(PhoneForward *pf, char const *num);

/** @brief Wyznacza przekierowanie numeru.
 * Wyznacza przekierowanie podanego numeru. Szuka najdłuższego pasującego
 * prefiksu. Wynikiem jest ciąg zawierający co najwyżej jeden numer. Jeśli dany
 * numer nie został przekierowany, to wynikiem jest ciąg zawierający ten numer.
 * Jeśli podany napis nie reprezentuje numeru, wynikiem jest pusty ciąg.
 * Alokuje strukturę @p PhoneNumbers, która musi być zwolniona za pomocą
 * funkcji @ref phnumDelete.
 * @param[in] pf  – wskaźnik na strukturę przechowującą przekierowania numerów;
 * @param[in] num – wskaźnik na napis reprezentujący numer.
 * @return Wskaźnik na strukturę przechowującą ciąg numerów lub NULL, gdy nie
 *         udało się alokować pamięci.
 */
PhoneNumbers * phfwdGet(PhoneForward const *pf, char const *num);

/** @brief Wyznacza przekierowania na dany numer.
 * Wyznacza następujący ciąg numerów: jeśli istnieje numer @p x, taki że istnieje
 * przekierowanie dające w wyniku numer @p num, to numer @p x
 * należy do wyniku wywołania @ref phfwdReverse z numerem @p num. Dodatkowo ciąg
 * wynikowy zawsze zawiera też numer @p num. Wynikowe numery są posortowane
 * leksykograficznie i nie mogą się powtarzać. Jeśli podany napis nie
 * reprezentuje numeru, wynikiem jest pusty ciąg. Alokuje strukturę
 * @p PhoneNumbers, która musi być zwolniona za pomocą funkcji @ref phnumDelete.
 * @param[in] pf  – wskaźnik na strukturę przechowującą przekierowania numerów;
 * @param[in] num – wskaźnik na napis reprezentujący numer.
 * @return Wskaźnik na strukturę przechowującą ciąg numerów lub NULL, gdy nie
 *         udało się alokować pamięci.
 */
PhoneNumbers * phfwdReverse(PhoneForward const *pf, char const *num);

/** @brief Wyznacza przekierowania na dany numer.
* Wyznacza następujący ciąg numerów: jeśli istnieje numer @p x, taki że wynik
* wywołania @p phfwdGet z numerem @p x zawiera numer @p num, to numer @p x
* należy do wyniku wywołania @ref phfwdGetReverse z numerem @p num. Dodatkowo ciąg
* wynikowy zawsze zawiera też numer @p num. Wynikowe numery są posortowane
* leksykograficznie i nie mogą się powtarzać. Jeśli podany napis nie
* reprezentuje numeru, wynikiem jest pusty ciąg. Alokuje strukturę
* @p PhoneNumbers, która musi być zwolniona za pomocą funkcji @ref phnumDelete.
* @param[in] pf  – wskaźnik na strukturę przechowującą przekierowania numerów;
* @param[in] num – wskaźnik na napis reprezentujący numer.
* @return Wskaźnik na strukturę przechowującą ciąg numerów lub NULL, gdy nie
*         udało się alokować pamięci.
*/
PhoneNumbers * phfwdGetReverse(PhoneForward const *pf, char const *num);

/** @brief Usuwa strukturę.
 * Usuwa strukturę wskazywaną przez @p pnum. Nic nie robi, jeśli wskaźnik ten ma
 * wartość NULL.
 * @param[in] pnum – wskaźnik na usuwaną strukturę.
 */
void phnumDelete(PhoneNumbers *pnum);

/** @brief Udostępnia numer.
 * Udostępnia wskaźnik na napis reprezentujący numer. Napisy są indeksowane
 * kolejno od zera.
 * @param[in] pnum – wskaźnik na strukturę przechowującą ciąg numerów telefonów;
 * @param[in] idx  – indeks numeru telefonu.
 * @return Wskaźnik na napis reprezentujący numer telefonu. Wartość NULL, jeśli
 *         wskaźnik @p pnum ma wartość NULL lub indeks ma za dużą wartość.
 */
char const * phnumGet(PhoneNumbers const *pnum, size_t idx);

/** @brief Tworzy nową strukturę.
 * Tworzy nową strukturę PhoneNumbers zawierającą jeden numer telefonu @p number.
 * @param[in] number - wskaźnik na napis reprezentujący numer.
 * @return Wskaźnik na strukturę przechowującą numer telefonu @p number lub NULL, gdy nie
 *         udało się alokować pamięci.
 */
PhoneNumbers *newPhoneNumber(char *number);

/** @brief Usuwa pierwszy numer ze struktury.
 * Usuwa pierwszy numer ze struktury @p pnum.
 * @param[in] pnum – wskaźnik na strukturę przechowującą ciąg numerów telefonów;
 */
void phnumDeleteFirstNumber(PhoneNumbers **pnum);

/** @brief Usuwa numer ze struktury.
 * Usuwa numer @p number ze struktury @p pnum.
 * @param[in] pnum – wskaźnik na strukturę przechowującą ciąg numerów telefonów;
 * @param[in] number - wskaźnik na napis reprezentujący numer do usunięcia.
 */
void phnumDeleteLaterNumber(PhoneNumbers *pnum, char const *number);

/** @brief Usuwa wszystkie numery z danym prefixem z struktury.
 * Usuwa wszystkie numery ze struktury @p pnum zaczynające się od prefixu @p prefix.
 * @param[in] pnum – wskaźnik na strukturę przechowującą ciąg numerów telefonów;
 * @param[in] prefix - wskaźnik na napis reprezentujący prefix
 *                     numerów do usunięcia.
 */
void phnumDeleteAllLaterNumbersStarting(PhoneNumbers *pnum, char const *prefix);

/** @brief Zmienia pierwszy numer telefonu.
 * Zmienia pierwszy numer telefonu z struktury @p pnum na numer @p num.
 * @param[in] pnum – wskaźnik na strukturę przechowującą ciąg numerów telefonów;
 * @param[in] num - wskaźnik na napis reprezentujący numer do zamienienia.
 */
void changeFirstNumber(PhoneNumbers *pnum, char *num);

/** @brief Dodaje numery do struktury.
 * Dodaje wszystkie numery z struktury @p source do struktury @p target.
 * Scala napotkane numery z numerem @p num w zależności od tego na jakim poziomie @p level
 * w drzewie reverse się znajdujemy.
 * @param[in] source – wskaźnik na strukturę przechowującą ciąg numerów telefonów do dodania;
 * @param[in, out] target – wskaźnik na strukturę przechowującą ciąg numerów telefonów które dodajmy;
 * @param[in] level - głebokość w jakiej jesteśmy w drzewie reverse.
 * @param[in] num - wskaźnik na napis reprezentujący numer do scalenia.
 * @return Wartość @p true, jeśli dodano wszystkie numery.
 *         Wartość @p false, jeśli nie udało się alokować pamięci.
 */
bool addNumbers(PhoneNumbers *source, PhoneNumbers **target, size_t level, char const *num);

/** @brief Dodaje numer do struktury.
 * Dodaje numer @p num do struktury @p pnum.
 * Nic nie robi, jeśli wskaźnik @p pnum ma wartość NULL.
 * @param[in] pnum – wskaźnik na strukturę przechowującą ciąg numerów telefonów;
 * @param[in] num - wskaźnik na napis reprezentujący numer do dodania.
 * @return Wartość @p true, jeśli dodano numer.
 *         Wartość @p false, jeśli nie udało się alokować pamięci
 *         lub wskaźnik @p pnum miał wartość NULL.
 */
bool addNextNumber(PhoneNumbers *pnum, char *num);


#endif /* __PHONE_FORWARD_H__ */
