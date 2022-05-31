/** @file
 * Implementacja klasy przechowującej przekierowania numerów telefonicznych
 *
 * @author Antoni Bryk <ab438254@mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 2022
 */
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include "phone_forward.h"
#include "trie.h"

#define NUMBER_OF_CHILDREN 10 ///< Liczba synów węzła struktury PhoneForward

/**
 * To jest struktura przechowująca przekierowania numerów telefonów.
 * Ma ona postać drzewa trie.
 */
struct PhoneForward {
    Trie *forward;
    Trie *reverse;
};


/** @brief Wyznacza długość numeru.
 * Wyznacza długość numeru @p number.
 * @param[in] number - wskaźnik na napis reprezentujący numer.
 * @return Długość numeru lub 0 jeśli wskaźnik @p number jest pusty lub,
 *         nie reprezentuje on poprawnego numeru.
 */
static size_t numberLength(char const *number) {
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
static char *combineNumbers(char const *num1, char const *num2) {
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
static bool areNumbersIndentical(char const *num1, char const *num2) {
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
static char *makeCopy(char const *number) {
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
        printf("lalala");
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

/** @brief Tworzy nowy węzeł.
 * Tworzy nowy pusty węzeł struktury PhoneForward z wszytkimi polami zainicjalizowanymi na NULL.
 * @return Wskaźnik na węzeł. Wartość NULL, jeśli nie udało się alokować pamięci.
 */
//static PhoneForward *newPhoneForward() {
//    PhoneForward *ans = malloc(sizeof(PhoneForward));
//    ans->forward = newNode();
//    ans->reverse = newNode();
//    return ans;
//}

/** @brief Tworzy nową strukturę.
 * Tworzy nową strukturę PhoneNumbers zawierającą jeden numer telefonu @p number.
 * @param[in] number - wskaźnik na napis reprezentujący numer.
 * @return Wskaźnik na strukturę przechowującą numer telefonu @p number lub NULL, gdy nie
 *         udało się alokować pamięci.
 */
static PhoneNumbers *newPhoneNumber(char *number) {
    PhoneNumbers *ans = malloc(sizeof(PhoneNumbers));
    if (ans == NULL) {
        return NULL;
    }

    ans->number = number;
    ans->next = NULL;

    return ans;
}

/** @brief Wstawia przekierowanie.
 * Wstawia do struktury @p pf przekierowanie numerów z prefiksem @p num1, na numer @p num2.
 * @param[in,out] pf – wskaźnik na strukturę przechowującą przekierowania
 *                     numerów;
 * @param[in] num1   – wskaźnik na napis reprezentujący prefiks numerów
 *                     przekierowywanych;
 * @param[in] num2   – wskaźnik na napis reprezentujący prefiks numerów,
 *                     na które jest wykonywane przekierowanie.
 * @return Wartość @p true, jeśli udało się wstawić przekierowanie.
 *         Wartość @p false, jeśli wystąpił błąd, np. podany napis nie
 *         reprezentuje numeru, oba podane numery są identyczne lub nie udało
 *         się alokować pamięci.
 */
//static bool insert(PhoneForward *pf, char const *num1, char const *num2) {
//    size_t number1_length = numberLength(num1);
//    size_t number2_length = numberLength(num2);
//
//    // Sprawdzamy czy dane są poprawne.
//    if (pf == NULL || number1_length == 0
//        || number2_length == 0 || areNumbersIndentical(num1, num2)) {
//
//        return false;
//    }
//
//    // Przechodzimy po drzewie trie pf dodając kolejne cyfry z prefiksu num1 jako węzły.
//    for (size_t level = 0; level < number1_length; ++level) {
//        int index = num1[level] - '0';
//
//        if (pf->child[index] == NULL) {
//            pf->child[index] = newPhoneForward();
//            if (pf->child[index] == NULL) {
//                return false;
//            }
//        }
//
//        pf = pf->child[index];
//    }
//
//    // Jeżeli było już przekierowanie o prefiksie num1 to je usuwamy.
//    if (pf->forward != NULL) {
//        free(pf->forward);
//    }
//
//    // Wstawiamy nowe przekierowanie.
//    pf->is_forward = true;
//    pf->forward = makeCopy(num2);
//    if (pf->forward == NULL) {
//        return false;
//    }
//
//    return true;
//}

PhoneForward *phfwdNew(void) {
    PhoneForward *ans = malloc(sizeof(PhoneForward));
    ans->forward = newNode();
    if (ans->forward == NULL) {
        return NULL;
    }

    ans->reverse = newNode();
    if (ans->reverse == NULL) {
        free(ans->forward);
        return NULL;
    }

    return ans;
}

void phfwdDelete(PhoneForward *pf) {
    if (pf != NULL) {
        if(pf->forward != NULL){
            deleteTrie(pf->forward);
        }
        if(pf->reverse != NULL){
            deleteTrie(pf->reverse);
        }
        free(pf);
    }
}

bool phfwdAdd(PhoneForward *pf, char const *num1, char const *num2) {
    if(pf == NULL){
        return false;
    } else {
        return(insert(pf->forward,pf->reverse,num1,num2,false) && insert(pf->reverse,pf->reverse,num2,num1,true));
    }
}

void phfwdRemove(PhoneForward *pf, char const *num) {
    size_t number_length = numberLength(num);
    Trie *forward = pf->forward;

    // Sprwadzamy poprawność danych a następnie usuwamy przekierowanie.
    if (pf != NULL && number_length != 0) {
        for (size_t level = 0; level < number_length; ++level) {
            int index = num[level] - '0';

            if (level == number_length - 1) {
                deleteForwardTrie(forward->child[index],pf->reverse,num);
                forward->child[index] = NULL;
                break;
            } else if (forward->child[index] == NULL) {
                break;
            }

            forward = forward->child[index];
        }
    }
}

void phnumDelete(PhoneNumbers *pnum) {
    while (pnum != NULL) {
        PhoneNumbers *pom = pnum;
        pnum = pnum->next;
        free(pom->number);
        free(pom);
    }
}

PhoneNumbers *phfwdGet(PhoneForward const *pf, char const *num) {
    Trie *forward_save = NULL;
    size_t level_save = 0;
    size_t number_length = numberLength(num);
    Trie *forward = pf->forward;

    // Sprawdzamy poprawność danych.
    if (pf == NULL) {
        return NULL;
    }
    if (number_length == 0) {
        return newPhoneNumber(NULL);
    }

    // Szukamy najdłuższego pasującego prefiksu i
    // zapisujamy jego koniecna wskaźnik forward_save.
    for (size_t level = 0; level < number_length; ++level) {
        int index = num[level] - '0'; // TODO wywalić indeksy

        if (forward->child[index] == NULL) {
            break;
        } else if (forward->child[index]->numbers != NULL) { //TODO zmienic
            forward_save = forward->child[index];
            level_save = level;
        }

        forward = forward->child[index];
    }

    // Zwracamy przekierowany numer lub otrzymany numer,
    // jeżeli nie znaleźliśmy przekierowania.
    if (forward_save == NULL) {
        return newPhoneNumber(makeCopy(num));
    } else {
        return newPhoneNumber(combineNumbers(forward_save->numbers->number, num + level_save + 1));
    }
}

void phnumDeleteFirstNumber(PhoneNumbers **pnum){
    if((*pnum)->next == NULL){
        free((*pnum)->number);
        free((*pnum));
        (*pnum) = NULL;
    } else {
        PhoneNumbers *save = *pnum;
        *pnum = (*pnum)->next;
        free(save->number);
        free(save);
    }
}

void phnumDeleteNumber(PhoneNumbers *pnum, char const *number){
    //TODO check czy nie jest null
    PhoneNumbers *prev = pnum;
    pnum = pnum->next;
    while(pnum != NULL){
        if(areNumbersIndentical(pnum->number,number)){
            prev->next = pnum->next;
            free(pnum->number);
            free(pnum);
            break;
        } else {
            prev = pnum;
            pnum = pnum->next;
        }
    }
}

void phnumDeleteAllNumbersStarting(PhoneNumbers *pnum, char const *prefix){
    PhoneNumbers *prev = pnum;
    pnum = pnum->next;
    while(pnum != NULL){
        if(startsWith(pnum->number,prefix)){
            prev->next = pnum->next;
            PhoneNumbers *save = pnum;
            pnum = pnum->next;
            free(save->number);
            free(save);
        } else {
            prev = pnum;
            pnum = pnum->next;
        }
    }
}

char const *phnumGet(PhoneNumbers const *pnum, size_t idx) {
    for (size_t i = 0; i < idx; ++i) {
        if (pnum != NULL) {
            pnum = pnum->next;
        } else {
            break;
        }
    }

    if (pnum == NULL) {
        return NULL;
    } else {
        return pnum->number;
    }
}



/** @brief Aktualnie niezaimplmentowana funkcja.
 * @param[in] pf  – wskaźnik na strukturę przechowującą przekierowania numerów;
 * @param[in] num – wskaźnik na napis reprezentujący numer.
 * @return NULL.
 */
PhoneNumbers *phfwdReverse(
        __attribute__((unused)) PhoneForward const *pf,
        __attribute__((unused)) char const *num) {
    return NULL;
}
