/** @file
 * Interfejs klasy drzew trie.
 *
 * @author Antoni Bryk <ab438254@mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 2022
 */

#ifndef PHONE_NUMBERS_TRIE_H
#define PHONE_NUMBERS_TRIE_H

#define NUMBER_OF_CHILDREN 12


/**
 * To jest definicja struktury Trie.
 */
typedef struct Trie Trie;

/**
 * To jest struktura przechowująca drzewo trie.
 */
struct Trie;

/** @brief Tworzy nową węzeł.
 * Tworzy nową węzeł drzewa trie z wszystkimi polami ustawionymi na NULL.
 * @return Wskaźnik na utworzoną strukturę lub NULL, gdy nie udało się
 *         alokować pamięci.
 */
Trie *newNode();

/** @brief Usuwa strukturę.
 * Usuwa strukturę wskazywaną przez @p trie. Nic nie robi, jeśli wskaźnik ten ma
 * wartość NULL.
 * @param[in] trie – wskaźnik na usuwaną strukturę.
 */
void deleteTrie(Trie *trie);

/** @brief Usuwa podrzewo drzewa forward.
 * Usuwa podrzewo zawierające wszystkie przekierowania z prefixem @p num z drzewa forward,
 * wskazywanego przez wskaźnik @p forward_trie.
 * Usuwa odpowiednie przkierowania z drzewa reverse wskazywanego przez wskaźnik @p reverse_trie.
 * Nic nie robi, jeśli wskaźnik @p forward_trie lub @p reverse_trie ma wartość NULL.
 * @param[in] forward_trie – wskaźnik na drzewo forward.
 * @param[in] reverse_trie – wskaźnik na drzewo reverse.
 * @param[in] num  – wskaźnik na napis reprezentujący prefiks numerów
 *                   do usunięcia;
 */
void deleteForwardSubtrie(Trie *forward_trie, Trie *reverse_trie, char const *num);

/** @brief Usuwa numer z drzewa reverse.
 * Usuwa numer @p number_to_delete będący przekierowaniem na numer @p number_reverse z drzewa reverse.
 * Nic nie robi, jeśli wskaźnik @p reverse_trie ma wartość NULL.
 * @param[in] trie – wskaźnik na drzewo reverse;
 * @param[in] number_reverse  – wskaźnik na napis reprezentujący numer
 *                                którego przekierowanie usuwamy;
 * @param[in] number_to_delete  – wskaźnik na napis reprezentujący numer
 *                                do usunięcia;
 */
void deleteNumberFromReverse(Trie *reverse, char const *number_reverse, char const *number_to_delete);

/** @brief Usuwa przekierowanie z drzewa reverse.
 * Usuwa podrzewo zawierające wszystkie przekierowania z prefixem @p num z drzewa forward,
 * wskazywanego przez wskaźnik @p forward_trie.
 * Usuwa odpowiednie przkierowania z drzewa reverse wskazywanego przez wskaźnik @p reverse_trie.
 * Nic nie robi, jeśli wskaźnik @p forward_trie lub @p reverse_trie ma wartość NULL.
 * @param[in] forward – wskaźnik na drzewo forward.
 * @param[in] reverse – wskaźnik na drzewo reverse.
 * @param[in] num  – wskaźnik na napis reprezentujący prefiks numerów
 *                   do usunięcia;
 */
void removeFromForward(Trie *forward, Trie *reverse, char const *num);

/** @brief Wstawia nowe przekierowanie.
 * Wstawia nowe przekierowanie do drzewa @p trie. Jeżeli wartość @p reverse jest false,
 * to przekierowanie zostanie wstawione do drzewa forward. W przeciwnym przypadku,
 * przekierowanie zostanie wstawione do rzewa reverse.
 * Jeśli w drzewie forward nadpisujemy istniejące przekierowanie,
 * to usuwamy je z drzewa @p reverse_trie.
 * @param[in] trie – wskaźnik na drzewo forward.
 * @param[in] reverse_trie – wskaźnik na drzewo reverse.
 * @param[in] num1   – wskaźnik na napis reprezentujący prefiks numerów
 *                     przekierowywanych;
 * @param[in] num2   – wskaźnik na napis reprezentujący prefiks numerów,
 *                     na które jest wykonywane przekierowanie.
 * @param[in] reverse - wskaźnik czy wstawiamy do drzewa reverse czy do drzewa forward.
 * @return Wartość @p true, jeśli przekierowanie zostało dodane.
 *         Wartość @p false, jeśli wystąpił błąd, np. podany napis nie
 *         reprezentuje numeru, oba podane numery są identyczne lub nie udało
 *         się alokować pamięci.
 */
bool insert(Trie *trie, Trie *reverse_trie, char const *num1, char const *num2, bool reverse);

/** @brief Zapisuje wszystkie przekierowania na dany numer.
 * Zapisuje wszystkie numery przekierowywujące na numer @p num do struktury @p result.
 * @param[in] reverse – wskaźnik na drzewo reverse z odwróconymi przekierowywaniami;
 * @param[in] num – wskaźnik na napis reprezentujący numer telefonu
 *                  którego przekierowania rządamy;
 * @param[in,out] result  – wskaźnik na strukturę PhoneNumbers na którą zapisujemy
 *                          wynikowe numery telefonów;
 * @return Wartość @p true, jeśli udało się zapisać numery.
 *         Wartość @p false, jeśli nie udało się alokować pamięci.
 */
bool getFromReverse(Trie *reverse, char const *num, PhoneNumbers **result);

/** @brief Zapisuje na jaki numer zostanie przekierowany dany numer.
 * Zapisuje do struktury @p result na jaki numer zostanie przekierowany numer @p num.
 * @param[in] trie – wskaźnik na drzewo forward z przekierowaniami.
 * @param[in] num – wskaźnik na napis reprezentujący numer telefonu
 *                  którego przekierowanie rządamy;
 * @param[in,out] result  – wskaźnik na strukturę PhoneNumbers na którą zapisujemy
 *                          wynikowy numer telefonu;
 * @return Wartość @p true, jeśli udało się zapisać numery.
 *         Wartość @p false, jeśli nie udało się alokować pamięci.
 */
bool getFromForward(Trie *forward, char const *num, PhoneNumbers **result);

#endif //PHONE_NUMBERS_TRIE_H
