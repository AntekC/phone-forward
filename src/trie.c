//
// Created by Antoni Bryk on 30/05/2022.
//

#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include "phone_numbers_operations.h"
#include "phone_forward.h"
#include "trie.h"

struct Trie {
    Trie *child[NUMBER_OF_CHILDREN];
    PhoneNumbers *numbers;
};

Trie *newNode() {
    Trie *ans = malloc(sizeof(Trie));
    if (ans == NULL) {
        return NULL;
    }

    ans->numbers = NULL;
    for (int i = 0; i < NUMBER_OF_CHILDREN; ++i) {
        ans->child[i] = NULL;
    }

    return ans;
}

void deleteNumberFromReverse(Trie *reverse, char const *number_reverse, char const *number_to_delete){
    size_t number_length = numberLength(number_reverse);

    for (size_t level = 0; level < number_length; ++level) {
        int index = digitToIndex(number_reverse[level]);
        reverse = reverse->child[index];
    }

    if(reverse != NULL){
        if(areNumbersIndentical(phnumGet(reverse->numbers,0),number_to_delete)){
            phnumDeleteFirstNumber(&reverse->numbers);
        } else {
            phnumDeleteNumber(reverse->numbers,number_to_delete);
        }
    }
}

void deleteAllNumberStartingWith(Trie *reverse, char const *number_reverse, char const *prefix){
    size_t number_length = numberLength(number_reverse);

    for (size_t level = 0; level < number_length; ++level) {
        int index = digitToIndex(number_reverse[level]);
        reverse = reverse->child[index];
    }

    if(reverse != NULL) {
        if (phnumGet(reverse->numbers, 1) != NULL) {
            phnumDeleteAllNumbersStarting(reverse->numbers, prefix);
        }

        if (startsWith(phnumGet(reverse->numbers, 0), prefix)) {
            phnumDeleteFirstNumber(&reverse->numbers);
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

    // Przechodzimy po drzewie trie dodając kolejne cyfry z prefiksu num1 jako węzły.
    for (size_t level = 0; level < number1_length; ++level) {
        int index = digitToIndex(num1[level]);

        if (trie->child[index] == NULL) {
            trie->child[index] = newNode();
            if (trie->child[index] == NULL) {
                return false;
            }
        }

        trie = trie->child[index];
    }

    char *number_to_insert = makeCopy(num2);
    if (number_to_insert == NULL) {
        return false;
    }

    if (reverse) {
        if (trie->numbers != NULL) {
            if(!add_next(trie->numbers, number_to_insert)){
                free(number_to_insert);
                return false;
            } else {
                return true;
            }
        } else {
            trie->numbers = newPhoneNumber(number_to_insert);
            if (trie->numbers == NULL) {
                free(number_to_insert);
                return false;
            } else {
                return true;
            }
        }
    } else {
        if (trie->numbers != NULL) {
            deleteNumberFromReverse(reverse_trie,phnumGet(trie->numbers,0),num1);
            changeFirstNumber(trie->numbers, number_to_insert);
            return true;
        } else {
            trie->numbers = newPhoneNumber(number_to_insert);
            if (trie->numbers == NULL) {
                free(number_to_insert);
                return false;
            } else {
                return true;
            }
        }
    }
}


void deleteTrie(Trie *trie){
    if(trie != NULL){
        for (size_t i = 0; i < NUMBER_OF_CHILDREN; ++i) {
            deleteTrie(trie->child[i]);
        }
        if (trie->numbers != NULL) {
            phnumDelete(trie->numbers);
        }
        free(trie);
    }
}

void deleteForwardTrie(Trie *trie, Trie *reverse_trie, char const *num){
    if(trie != NULL){
        for (size_t i = 0; i < NUMBER_OF_CHILDREN; ++i) {
            deleteForwardTrie(trie->child[i],reverse_trie, num);
        }
        if (trie->numbers != NULL) {
            deleteAllNumberStartingWith(reverse_trie, phnumGet(trie->numbers,0), num);
            phnumDelete(trie->numbers);
        }
        free(trie);
    }
}

bool getFromReverse(Trie *reverse, char const *num, PhoneNumbers **ans){
    size_t number_lentgh = numberLength(num);
    char *original_number = makeCopy(num);
    PhoneNumbers *wynik = NULL;

    if(number_lentgh == 0){
        free(original_number);
        wynik = newPhoneNumber(NULL);
        (*ans) = wynik;
        return false;
    }
    if(original_number == NULL){
        (*ans) = wynik;
        return false;
    }

    wynik = newPhoneNumber(original_number);
    if(wynik == NULL){
        free(original_number);
        return false;
    }

    for (size_t level = 0; level < number_lentgh; ++level) {
        int index = digitToIndex(num[level]);

        if (reverse->child[index] == NULL) {
            break;

        } else {

            if(reverse->child[index]->numbers != NULL){
                if(!addNumbers(reverse->child[index]->numbers, &wynik, level, num)){
                    phnumDelete(wynik);
                    return false;
                }
            }
        }
        reverse = reverse->child[index];
    }

    (*ans) = wynik;
    return true;
}

void removeFromForward(Trie *forward, Trie *reverse, char const *num){
    size_t number_length = numberLength(num);

    if(forward != NULL && reverse != NULL){
        for (size_t level = 0; level < number_length; ++level) {
            int index = digitToIndex(num[level]);

            if (level == number_length - 1) {
                deleteForwardTrie(forward->child[index],reverse,num);
                forward->child[index] = NULL;
                break;
            } else if (forward->child[index] == NULL) {
                break;
            }

            forward = forward->child[index];
        }
    }
}

bool getFromForward(Trie *forward, char const *num, PhoneNumbers **ans){
    PhoneNumbers *ans_buff = NULL; //TODO Zmienić nazwę
    size_t level_save = 0;
    size_t number_length = numberLength(num);
    Trie *forward_save = NULL;

    if(forward == NULL){
        (*ans) = ans_buff;
        return false;
    }

    if(number_length == 0){
        ans_buff = newPhoneNumber(NULL);
        (*ans) = ans_buff;
        return false;
    }

    for (size_t level = 0; level < number_length; ++level) {
        int index = digitToIndex(num[level]);

        if (forward->child[index] == NULL) {
            break;
        } else if (forward->child[index]->numbers != NULL) {
            forward_save = forward->child[index];
            level_save = level;
        }

        forward = forward->child[index];
    }

    if (forward_save == NULL){
        char *number_to_give = makeCopy(num);

        if(number_to_give == NULL){
            (*ans) = ans_buff;
            return false;
        }

        ans_buff = newPhoneNumber(number_to_give);

        if(ans_buff == NULL){
            free(number_to_give);
            (*ans) = ans_buff;
            return false;
        } else {
            (*ans) = ans_buff;
            return true;
        }
    } else {
        char *number_to_give = combineNumbers(phnumGet(forward_save->numbers,0),num+level_save+1);

        if(number_to_give == NULL){
            (*ans) = ans_buff;
            return false;
        }

        ans_buff = newPhoneNumber(number_to_give);

        if(ans == NULL){
            free(number_to_give);
            return false;
        } else {
            (*ans) = ans_buff;
            return true;
        }
    }
}

