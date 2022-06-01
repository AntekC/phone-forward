//
// Created by Antoni Bryk on 30/05/2022.
//

#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include "phone_forward.h"
#include "trie.h"

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

//bool startsWith(char const *number, char const *prefix){
//    size_t prefix_length = numberLength(prefix);
//    size_t number_length = numberLength(number);
//    if(prefix_length > number_length){
//        printf("lalala");
//    }
//
//    for(size_t i = 0; i < prefix_length; ++i){
//        if(*prefix != *number){
//            return false;
//        } else {
//            ++prefix;
//            ++number;
//        }
//    }
//    return true;
//}

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

void add_next(PhoneNumbers *numbers, char *num) {
    while (numbers->next != NULL) {
        numbers = numbers->next;
    }
    numbers->next = newPhoneNumber(num);
}

void deleteNumberFromReverse(Trie *reverse, char const *number_reverse, char const *number_to_delete){
    size_t number_length = numberLength(number_reverse);

    for (size_t level = 0; level < number_length; ++level) {
        int index = number_reverse[level] - '0'; // TODO wywalić indeksy
        reverse = reverse->child[index];
    }

    if(areNumbersIndentical(phnumGet(reverse->numbers,0),number_to_delete)){
        phnumDeleteFirstNumber(&reverse->numbers);
    } else {
        phnumDeleteNumber(reverse->numbers,number_to_delete);
    }

}

void deleteAllNumberStartingWith(Trie *reverse, char const *number_reverse, char const *prefix){
    size_t number_length = numberLength(number_reverse);

    for (size_t level = 0; level < number_length; ++level) {
        int index = number_reverse[level] - '0'; // TODO wywalić indeksy
        reverse = reverse->child[index];
    }

    if(phnumGet(reverse->numbers,1) != NULL){
        phnumDeleteAllNumbersStarting(reverse->numbers,prefix);
    }

    if(startsWith(phnumGet(reverse->numbers,0),prefix)){
        phnumDeleteFirstNumber(&reverse->numbers);
        //free(reverse->numbers);
        //reverse->numbers = NULL;
    }

}

bool insert(Trie *trie, Trie *reverse_trie, char const *num1, char const *num2, bool reverse) {
    size_t number1_length = numberLength(num1);
    size_t number2_length = numberLength(num2);

    // Sprawdzamy czy dane są poprawne.
    if (trie == NULL || number1_length == 0
        || number2_length == 0 || areNumbersIndentical(num1, num2)) {

        return false;
    }

    // Przechodzimy po drzewie trie trie dodając kolejne cyfry z prefiksu num1 jako węzły.
    for (size_t level = 0; level < number1_length; ++level) {
        int index = num1[level] - '0';

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
            add_next(trie->numbers, number_to_insert);//TODO TO MOZE WYWALIC BLAD
        } else {
            trie->numbers = newPhoneNumber(number_to_insert);
            if (trie->numbers == NULL) {
                free(number_to_insert);
                return false;
            }
        }
    } else {
        if (trie->numbers != NULL) {
            if(phnumGet(trie->numbers,0) == NULL){
                printf("lulu\n");
            }
            deleteNumberFromReverse(reverse_trie,phnumGet(trie->numbers,0),num1);
            changeFirstNumber(trie->numbers, number_to_insert);
        } else {
            trie->numbers = newPhoneNumber(number_to_insert);
            if (trie->numbers == NULL) {
                free(number_to_insert);
                return false;
            }
        }
    }

    return true;
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
            //trie->child[i] = NULL;
        }
        if (trie->numbers != NULL) {
            deleteAllNumberStartingWith(reverse_trie, phnumGet(trie->numbers,0), num);
            phnumDelete(trie->numbers);
            //free(trie->numbers);
        }
        free(trie);
    }
}

