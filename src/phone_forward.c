/** @file
 * Implementacja klasy przechowującej przekierowania numerów telefonicznych
 *
 * @author Antoni Bryk <ab438254@mimuw.edu.pl>
 * @copyright Uniwersytet Warszawski
 * @date 2022
 */
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "phone_forward.h"

#define NUMBER_OF_CHILDREN 10

/**
 * To jest struktura przechowująca przekierowania numerów telefonów.
 */
struct PhoneForward {
    struct PhoneForward *child[NUMBER_OF_CHILDREN]; // Tablica wskaźników na dzieci węzła.
    //struct PhoneForward *father;
    bool is_forward; // Pole oznaczająca czy dany węzeł jest przekierowaniem.
    char *forward; // Wskaźnik na numer będący przekierowaniem.
};

/**
 * To jest struktura przechowująca ciąg numerów telefonów.
 */
struct PhoneNumbers {
    struct PhoneNumbers *next; // Wskaźnik na następny element w liście.
    char *number; // Wskaźnik na numer telefonu.
};

/** @brief Wyznacza długość numeru.
 * Wyznacza długość numeru @p number.
 * @param[in] number - wskaźnik na napis reprezentujący numer.
 * @return Długość numeru lub 0 jeśli wskaźnik @p number jest pusty lub,
 *         nie reprezentuje on poprawnego numeru.
 */
static int numberLength(char const *number) {
    int answer = 0;
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

/** @brief Tworzy scalenie dwóch numerów
 * Tworzy napis będący scaleniem dwóch numerów @p num1 i @p num2.
 * @param[in] num1 - wskaźnik na napis reprezentujący pierwszy numer do scalenia;
 * @param[in] num2 - wskaźnik na napis reprezentujący drugi numer do scalenia;
 * @return Wskaźnik na napis reprezentujący scalenie dwóch numerów. Wartość NULL, jeśli
 *         nie udało się alokować pamięci.
 */
static char *combineNumbers(char const *num1, char const *num2) {
    size_t num1_length = numberLength(num1);
    size_t num2_length = numberLength(num2);
    char *ans = malloc((num1_length + num2_length + 1) * sizeof(char));
    if (ans == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < num1_length; ++i) {
        ans[i] = num1[i];
    }
    for (size_t i = num1_length; i < num1_length + num2_length; ++i) {
        ans[i] = num2[i - num1_length];
    }
    ans[num1_length + num2_length] = '\0';

    return ans;
}

/** @brief Sprawdza czy dwa numery są identyczne
 * Sprawdza czy @p num1 jest identyczny jak @p num2.
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

/** @brief Tworzy nowy węzeł.
 * Tworzy nowy pusty węzeł struktury PhoneForward z wszytkimi polami zainicjalizowanymi na NULL.
 * @return Wskaźnik na węzeł. Wartość NULL, jeśli nie udało się alokować pamięci.
 */
static PhoneForward *newNode() {
    PhoneForward *ans = malloc(sizeof(PhoneForward));
    if (ans == NULL) {
        return NULL;
    }

    ans->is_forward = false;
    //ans->father = father;
    ans->forward = NULL;
    for (int i = 0; i < NUMBER_OF_CHILDREN; ++i) {
        ans->child[i] = NULL;
    }

    return ans;
}

/** @brief Tworzy nową strukturę.
 *  Tworzy nową strukturę PhoneNumbers zawierającą jeden numer telefonu @p number.
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
 * Wstawia do struktury pf przekierowanie numerów z prefiksem @p num1, na numer @p num2.
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
static bool insert(PhoneForward *pf, char const *num1, char const *num2) {
    size_t number1_length = numberLength(num1);
    size_t number2_length = numberLength(num2);

    if (pf == NULL || number1_length == 0
        || number2_length == 0 || areNumbersIndentical(num1, num2)) {

        return false;
    }

    for (size_t level = 0; level < number1_length; ++level) {
        int index = num1[level] - '0';

        if (pf->child[index] == NULL) {
            pf->child[index] = newNode();
            if (pf->child[index] == NULL) {
                return false;
            }
        }

        pf = pf->child[index];
    }

    pf->is_forward = true;
    if (pf->forward != NULL) {
        free(pf->forward);
    }

    pf->forward = makeCopy(num2);
    if (pf->forward == NULL) {
        return false;
    }

    return true;
}

PhoneForward *phfwdNew(void) {
    return newNode();
}

void phfwdDelete(PhoneForward *pf) {
    if (pf != NULL) {
        for (size_t i = 0; i < NUMBER_OF_CHILDREN; ++i) {
            phfwdDelete(pf->child[i]);
        }
        if (pf->is_forward) {
            free(pf->forward);
        }
        free(pf);
    }
}

bool phfwdAdd(PhoneForward *pf, char const *num1, char const *num2) {
    return insert(pf, num1, num2);
}

void phfwdRemove(PhoneForward *pf, char const *num) {
    size_t number_length = numberLength(num);

    if (pf != NULL && number_length != 0) {
        for (size_t level = 0; level < number_length; ++level) {
            int index = num[level] - '0';

            if (level == number_length - 1) {
                phfwdDelete(pf->child[index]);
                pf->child[index] = NULL;
                break;
            } else if (pf->child[index] == NULL) {
                break;
            }

            pf = pf->child[index];
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
    PhoneForward *forward_save = NULL;
    size_t level_save = 0;
    size_t number_length = numberLength(num);

    if (pf == NULL) {
        return NULL;
    }
    if (number_length == 0) {
        return newPhoneNumber(NULL);
    }

    for (size_t level = 0; level < number_length; ++level) {
        int index = num[level] - '0';

        if (pf->child[index] == NULL) {
            break;
        } else if (pf->child[index]->is_forward) {
            forward_save = pf->child[index];
            level_save = level;
        }

        pf = pf->child[index];
    }
    if (forward_save == NULL) {
        return newPhoneNumber(makeCopy(num));
    } else {
        return newPhoneNumber(combineNumbers(forward_save->forward, num + level_save + 1));
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

PhoneNumbers *phfwdReverse(PhoneForward const *pf, char const *num) {
    return newPhoneNumber(NULL);
}
