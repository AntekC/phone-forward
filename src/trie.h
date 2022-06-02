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

/** @brief Usuwa drzewo podrzewo drzewa forward.
 * Usuwa podrzewo zawierające wszystkie przekierowania z prefixem @p num z drzewa forward,
 * wskazywanego przez wskaźnik @p forward_trie.
 * Usuwa odpowiednie przkierowania z drzewa reverse wskazywanego przez wskaźnik @p reverse_trie.
 * Nic nie robi, jeśli wskaźnik @p forward_trie lub @p reverse_trie ma wartość NULL.
 * @param[in] trie – wskaźnik na drzewo forward.
 * @param[in] trie – wskaźnik na drzewo reverse.
 * @param[in] num  – wskaźnik na napis reprezentujący prefiks numerów
 *                   do usunięcia;
 */
void deleteForwardSubtrie(Trie *forward_trie, Trie *reverse_trie, char const *num);

/** @brief Usuwa przekierowanie z drzewa reverse.
 * Usuwa podrzewo zawierające wszystkie przekierowania z prefixem @p num z drzewa forward,
 * wskazywanego przez wskaźnik @p forward_trie.
 * Usuwa odpowiednie przkierowania z drzewa reverse wskazywanego przez wskaźnik @p reverse_trie.
 * Nic nie robi, jeśli wskaźnik @p forward_trie lub @p reverse_trie ma wartość NULL.
 * @param[in] trie – wskaźnik na drzewo forward.
 * @param[in] trie – wskaźnik na drzewo reverse.
 * @param[in] num  – wskaźnik na napis reprezentujący prefiks numerów
 *                   do usunięcia;
 */
void deleteNumberFromReverse(Trie *reverse, char const *number_reverse, char const *number_to_delete);


bool insert(Trie *trie, Trie *reverse_trie, char const *num1, char const *num2, bool reverse);

bool getFromReverse(Trie *reverse, char const *num, PhoneNumbers **result);

void removeFromForward(Trie *forward, Trie *reverse, char const *num);

bool getFromForward(Trie *forward, char const *num, PhoneNumbers **result);

#endif //PHONE_NUMBERS_TRIE_H
