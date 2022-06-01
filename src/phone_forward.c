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
#include "phone_numbers_operations.h"
#include "trie.h"


/**
 * To jest struktura przechowująca przekierowania numerów telefonów.
 * Składa się ona z dwóch dzrzew trie.
 */
struct PhoneForward {
    Trie *forward; ///< Wskaźnik na drzewo trie przekierowań.
    Trie *reverse; ///< Wskaźnik na drzewo trie odwróconych przekierowań.
};

struct PhoneNumbers {
    struct PhoneNumbers *next; ///< Wskaźnik na następny element w liście.
    char *number; // Wskaźnik na numer telefonu.
};

/** @brief Tworzy nową strukturę.
 * Tworzy nową strukturę PhoneNumbers zawierającą jeden numer telefonu @p number.
 * @param[in] number - wskaźnik na napis reprezentujący numer.
 * @return Wskaźnik na strukturę przechowującą numer telefonu @p number lub NULL, gdy nie
 *         udało się alokować pamięci.
 */
PhoneNumbers *newPhoneNumber(char *number) {
    PhoneNumbers *ans = malloc(sizeof(PhoneNumbers));
    if (ans == NULL) {
        return NULL;
    }

    ans->number = number;
    ans->next = NULL;

    return ans;
}

void changeFirstNumber(PhoneNumbers *numbers, char *num) {
    free(numbers->number);
    numbers->number = num;
}

bool addNextNumber(PhoneNumbers *numbers, char *num) {
    while (numbers->next != NULL) {
        numbers = numbers->next;
    }
    numbers->next = newPhoneNumber(num);
    if (numbers->next == NULL) {
        return false;
    } else {
        return true;
    }
}

void phnumDeleteFirstNumber(PhoneNumbers **pnum) {
    if ((*pnum) != NULL) {
        PhoneNumbers *save = *pnum;
        (*pnum) = (*pnum)->next;
//        if ((*pnum)->next == NULL) {
//            (*pnum) = NULL;
//        } else {
//            *pnum = (*pnum)->next;
//        }

        free(save->number);
        free(save);
    }
}

void phnumDeleteNumber(PhoneNumbers *pnum, char const *number) {
    if (pnum != NULL) {
        PhoneNumbers *prev = pnum;
        pnum = pnum->next;
        while (pnum != NULL) {
            if (areNumbersIndentical(pnum->number, number)) {
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
}

void phnumDeleteAllNumbersStarting(PhoneNumbers *pnum, char const *prefix) {
    PhoneNumbers *prev = pnum;
    pnum = pnum->next;
    while (pnum != NULL) {
        if (startsWith(pnum->number, prefix)) {
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

bool insertNotFirstNumber(PhoneNumbers *ans, char const *number, size_t level, char const *num) {
    char *number_to_insert = combineNumbers(number, num + level + 1);
    if (number_to_insert == NULL) {
        return false;
    }
    PhoneNumbers *insert = newPhoneNumber(number_to_insert);
    if (insert == NULL) {
        free(number_to_insert);
        return false;
    }

    PhoneNumbers *prev = ans;
    ans = ans->next;

    while (ans != NULL) {
        if (areNumbersIndentical(ans->number, number_to_insert)) {
            phnumDelete(insert);
            return true;
        } else if (compareNumbers(ans->number, number_to_insert)) {
            prev->next = insert;
            insert->next = ans;
            return true;
        } else {
            prev = ans;
            ans = ans->next;
        }
    }
    prev->next = insert;
    return true;
}

bool insertFirstNumber(PhoneNumbers **ans, char const *number, size_t level, char const *num) {
    char *number_to_insert = combineNumbers(number, num + level + 1);
    if (number_to_insert == NULL) {
        return false;
    }

    // Już jest taki numer w wyniku zatem nie trzeba go dodawać.
    if (areNumbersIndentical(number_to_insert, (*ans)->number)) {
        free(number_to_insert);
        return true;
    }

    if ((*ans) != NULL) {
        PhoneNumbers *new = newPhoneNumber(number_to_insert);
        if (new == NULL) {
            free(number_to_insert);
            return false;
        }
        new->next = (*ans);
        (*ans) = new;
        return true;
    } else {
        return false;
    }
}

bool addNumbers(PhoneNumbers *numbers, PhoneNumbers **ans, size_t level, char const *num) {
    while (numbers != NULL) {
        if (compareNumbers((*ans)->number, numbers->number)) {
            if (!insertFirstNumber(ans, numbers->number, level, num)) {
                return false;
            }
        } else {
            if (!insertNotFirstNumber(*ans, numbers->number, level, num)) {
                return false;
            }
        }
        numbers = numbers->next;
    }
    return true;
}

PhoneForward *phfwdNew(void) {
    PhoneForward *ans = malloc(sizeof(PhoneForward));
    if (ans == NULL) {
        return NULL;
    }

    ans->forward = newNode();
    if (ans->forward == NULL) {
        free(ans);
        return NULL;
    }

    ans->reverse = newNode();
    if (ans->reverse == NULL) {
        free(ans->forward);
        free(ans);
        return NULL;
    }

    return ans;
}

void phfwdDelete(PhoneForward *pf) {
    if (pf != NULL) {
        if (pf->forward != NULL) {
            deleteTrie(pf->forward);
        }
        if (pf->reverse != NULL) {
            deleteTrie(pf->reverse);
        }
        free(pf);
    }
}

bool phfwdAdd(PhoneForward *pf, char const *num1, char const *num2) {
    if (pf == NULL) {
        return false;
    } else {
        return (insert(pf->forward, pf->reverse, num1, num2, false) &&
                insert(pf->reverse, pf->reverse, num2, num1, true));
    }
}

void phfwdRemove(PhoneForward *pf, char const *num) {
    if (pf != NULL) {
        removeFromForward(pf->forward, pf->reverse, num);
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
    PhoneNumbers *ans = NULL;

    if (pf != NULL && pf->forward != NULL) {
        getFromForward(pf->forward, num, &ans);
    }

    return ans;
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

    PhoneNumbers *ans = NULL;

    if (pf != NULL) {
        getFromReverse(pf->reverse, num, &ans);
        return ans;
    } else {
        char *number_to_give = makeCopy(num);
        if (number_to_give == NULL) {
            return NULL;
        }
        ans = newPhoneNumber(number_to_give);
        if (ans == NULL) {
            free(number_to_give);
            return NULL;
        }

        return ans;
    }
}
