//
// Created by Antoni Bryk on 30/05/2022.
//

#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "phone_numbers_operations.h"
#include "phone_forward.h"
#include "trie.h"

struct Trie {
    Trie *children[NUMBER_OF_CHILDREN]; ///< Wskaźnik na dzieci danego węzła.
    PhoneNumbers *numbers; ///< Wskaźnik strukturę PhoneNumbers zawierającej przkierowane prefixy.
};

static void deleteAllNumbersStartingWith(Trie *reverse, char const *number_reverse, char const *prefix) {
    size_t number_length = numberLength(number_reverse);

    for (size_t level = 0; level < number_length; ++level) {
        int index = digitToOrder(number_reverse[level]);
        reverse = reverse->children[index];
    }

    if (reverse != NULL) {
        if (phnumGet(reverse->numbers, 1) != NULL) {
            phnumDeleteAllLaterNumbersStarting(reverse->numbers, prefix);
        }

        if (startsWith(phnumGet(reverse->numbers, 0), prefix)) {
            phnumDeleteFirstNumber(&reverse->numbers);
        }
    }
}

Trie *newNode() {
    Trie *ans = malloc(sizeof(Trie));
    if (ans == NULL) {
        return NULL;
    }

    ans->numbers = NULL;
    for (int i = 0; i < NUMBER_OF_CHILDREN; ++i) {
        ans->children[i] = NULL;
    }

    return ans;
}

void deleteTrie(Trie *trie) {
    if (trie != NULL) {
        for (size_t i = 0; i < NUMBER_OF_CHILDREN; ++i) {
            deleteTrie(trie->children[i]);
        }
        if (trie->numbers != NULL) {
            phnumDelete(trie->numbers);
        }
        free(trie);
    }
}

void deleteForwardSubtrie(Trie *forward_trie, Trie *reverse_trie, char const *num) {
    if (forward_trie != NULL) {
        for (size_t i = 0; i < NUMBER_OF_CHILDREN; ++i) {
            deleteForwardSubtrie(forward_trie->children[i], reverse_trie, num);
        }
        if (forward_trie->numbers != NULL) {
            deleteAllNumbersStartingWith(reverse_trie, phnumGet(forward_trie->numbers, 0), num);
            phnumDelete(forward_trie->numbers);
        }
        free(forward_trie);
    }
}

void deleteNumberFromReverse(Trie *reverse, char const *number_reverse, char const *number_to_delete) {
    size_t number_length = numberLength(number_reverse);

    for (size_t level = 0; level < number_length; ++level) {
        int index = digitToOrder(number_reverse[level]);
        reverse = reverse->children[index];
    }

    if (reverse != NULL) {
        if (areNumbersIndentical(phnumGet(reverse->numbers, 0), number_to_delete)) {
            phnumDeleteFirstNumber(&reverse->numbers);
        } else {
            phnumDeleteLaterNumber(reverse->numbers, number_to_delete);
        }
    }
}

void removeFromForward(Trie *forward, Trie *reverse, char const *num) {
    size_t number_length = numberLength(num);

    if (forward != NULL && reverse != NULL) {
        for (size_t level = 0; level < number_length; ++level) {
            int index = digitToOrder(num[level]);

            if (level == number_length - 1) {
                deleteForwardSubtrie(forward->children[index], reverse, num);
                forward->children[index] = NULL;
                break;
            } else if (forward->children[index] == NULL) {
                break;
            }

            forward = forward->children[index];
        }
    }
}

bool insert(Trie *trie, Trie *reverse_trie, char const *num1, char const *num2, bool reverse) {
    size_t number1_length = numberLength(num1);
    size_t number2_length = numberLength(num2);

    // Sprawdzamy czy dane są poprawne.
    if (trie == NULL || reverse_trie == NULL || number1_length == 0
        || number2_length == 0 || areNumbersIndentical(num1, num2)) {

        return false;
    }

    char *number_to_insert = makeCopy(num2);
    if (number_to_insert == NULL) {
        return false;
    }

    // Przechodzimy po drzewie trie dodając kolejne cyfry z prefiksu num1 jako węzły.
    for (size_t level = 0; level < number1_length; ++level) {
        int index = digitToOrder(num1[level]);

        if (trie->children[index] == NULL) {
            trie->children[index] = newNode();
            if (trie->children[index] == NULL) {
                free(number_to_insert);
                return false;
            }
        }

        trie = trie->children[index];
    }

    if (trie->numbers != NULL) {
        // Dodajemy przkierowanie do aktulanych w drzewie reverse.
        if (reverse) {
            if (!addNextNumber(trie->numbers, number_to_insert)) {
                free(number_to_insert);
                return false;
            } else {
                return true;
            }
            // Usuwamy stare przekierowanie z drzewa reverse i dodajemy je do drzewa forward.
        } else {
            deleteNumberFromReverse(reverse_trie, phnumGet(trie->numbers, 0), num1);
            changeFirstNumber(trie->numbers, number_to_insert);
            return true;
        }
    } else {
        // Wstawiamy nowe przekierowanie.
        trie->numbers = newPhoneNumber(number_to_insert);
        if (trie->numbers == NULL) {
            free(number_to_insert);
            return false;
        } else {
            return true;
        }
    }
}

bool getFromReverse(Trie *reverse, char const *num, PhoneNumbers **result) {
    size_t number_length = numberLength(num);
    char *original_number = makeCopy(num);
    PhoneNumbers *temp_result = NULL;

    // Sprawdzamy poprawność danych i czy nie wystąpił problem z pamięcią.
    if (reverse == NULL || original_number == NULL) {
        (*result) = temp_result;
        return false;
    }
    if (number_length == 0) {
        free(original_number);
        temp_result = newPhoneNumber(NULL);
        (*result) = temp_result;
        return false;
    }
    temp_result = newPhoneNumber(original_number);
    if (temp_result == NULL) {
        free(original_number);
        return false;
    }

    // Przechodzimy po drzewie reverse dodając wszystkie numery które przkierowywują na numer num.
    for (size_t level = 0; level < number_length; ++level) {
        int index = digitToOrder(num[level]);

        if (reverse->children[index] == NULL) {
            break;
        } else {
            if (reverse->children[index]->numbers != NULL) {
                if (!addNumbers(reverse->children[index]->numbers, &temp_result, level, num)) {
                    phnumDelete(temp_result);
                    return false;
                }
            }
        }

        reverse = reverse->children[index];
    }

    (*result) = temp_result;
    return true;
}

bool getFromForward(Trie *forward, char const *num, PhoneNumbers **result) {
    PhoneNumbers *temp_result = NULL;
    size_t level_save = 0;
    size_t number_length = numberLength(num);
    Trie *forward_save = NULL;

    if (forward == NULL) {
        (*result) = temp_result;
        return false;
    }
    if (number_length == 0) {
        temp_result = newPhoneNumber(NULL);
        (*result) = temp_result;
        return false;
    }

    // Przechodzimy po drzewie trie szukając czy istnieje przekierowanie z num.
    for (size_t level = 0; level < number_length; ++level) {
        int index = digitToOrder(num[level]);

        if (forward->children[index] == NULL) {
            break;
        } else if (forward->children[index]->numbers != NULL) {
            forward_save = forward->children[index];
            level_save = level;
        }

        forward = forward->children[index];
    }

    // Nie ma takiego przekierownia na numer num, więc go zwracamy.
    if (forward_save == NULL) {
        char *number_to_give = makeCopy(num);
        if (number_to_give == NULL) {
            (*result) = temp_result;
            return false;
        }

        temp_result = newPhoneNumber(number_to_give);

        if (temp_result == NULL) {
            free(number_to_give);
            (*result) = temp_result;
            return false;
        } else {
            (*result) = temp_result;
            return true;
        }

        // Istnieje przkierowania z numeru num, więc je zwracamy.
    } else {
        char *number_to_give = combineNumbers(phnumGet(forward_save->numbers, 0), num + level_save + 1);
        if (number_to_give == NULL) {
            (*result) = temp_result;
            return false;
        }

        temp_result = newPhoneNumber(number_to_give);

        if (temp_result == NULL) {
            free(number_to_give);
            return false;
        } else {
            (*result) = temp_result;
            return true;
        }
    }
}
