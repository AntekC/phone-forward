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
#include "phone_numbers_operations.h"
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

PhoneForward *phfwdNew(void) {
    PhoneForward *ans = malloc(sizeof(PhoneForward));
    if(ans == NULL){
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

    // Sprwadzamy poprawność danych a następnie usuwamy przekierowanie.
    if (pf != NULL && number_length != 0) {

        Trie *forward = pf->forward;
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
    if (pf == NULL) {
        return NULL;
    }

    Trie *forward_save = NULL;
    size_t level_save = 0;
    size_t number_length = numberLength(num);
    Trie *forward = pf->forward;

    if (number_length == 0) {
        return newPhoneNumber(NULL);
    }

    // Szukamy najdłuższego pasującego prefiksu i
    // zapisujamy jego koniecna wskaźnik forward_save.
    for (size_t level = 0; level < number_length; ++level) {
        int index = num[level] - '0'; // TODO wywalić indeksy

        if (forward->child[index] == NULL) {
            break;
        } else if (forward->child[index]->numbers != NULL) {
            forward_save = forward->child[index];
            level_save = level;
        }

        forward = forward->child[index];
    }

    // Zwracamy przekierowany numer lub otrzymany numer,
    // jeżeli nie znaleźliśmy przekierowania.
    if (forward_save == NULL) {
        char *number_to_make = makeCopy(num);
        if(number_to_make == NULL){
            return  NULL;
        }

        PhoneNumbers *ans = newPhoneNumber((number_to_make));
        if(ans == NULL){
            free(number_to_make);
            return NULL;
        } else {
            return ans;
        }

    } else {
        char *number_to_make = combineNumbers(forward_save->numbers->number, num + level_save + 1);
        if(number_to_make == NULL){
            return NULL;
        }

        PhoneNumbers *ans = newPhoneNumber(number_to_make);
        if(ans == NULL){
            free(number_to_make);
            return NULL;
        } else {
            return ans;
        }

    }
}

void phnumDeleteFirstNumber(PhoneNumbers **pnum){
    if((*pnum) != NULL){
        if((*pnum)->next == NULL){
            PhoneNumbers *save = *pnum;
            (*pnum) = NULL;
            free(save->number);
            free(save);

        } else {
            PhoneNumbers *save = *pnum;
            *pnum = (*pnum)->next;
            free(save->number);
            free(save);
        }
    }
}

void phnumDeleteNumber(PhoneNumbers *pnum, char const *number){
    if(pnum != NULL) {
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

bool insertNotFirstNumber(PhoneNumbers *ans, char const *number, size_t level,char const *num){
    char *number_to_insert = combineNumbers(number,num+level+1);
    if(number_to_insert == NULL){
        return false;
    }
    PhoneNumbers *insert = newPhoneNumber(number_to_insert);
    if(insert == NULL){
        free(number_to_insert);
        return false;
    }

    PhoneNumbers *prev = ans;
    ans = ans->next;

    while(ans != NULL){
        if(areNumbersIndentical(ans->number,number_to_insert)){
            phnumDelete(insert);
            return true;
        } else if(isHigher(ans->number,number_to_insert)){
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

bool insertFirstNumber(PhoneNumbers **ans, char const *number, size_t level, char const *num){
    char *number_to_insert = combineNumbers(number,num+level+1);
    if(number_to_insert == NULL){
        return false;
    }
    // Już jest taki numer
    if(areNumbersIndentical(number_to_insert,(*ans)->number)){
        free(number_to_insert);
        return true;
    }

    if((*ans) != NULL){
        PhoneNumbers *new = newPhoneNumber(number_to_insert);
        if(new == NULL){
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

bool addNumbers(PhoneNumbers *numbers, PhoneNumbers **ans, size_t level, char const *num){
    while(numbers != NULL){
        if(isHigher((*ans)->number,numbers->number)){
            insertFirstNumber(ans,numbers->number, level, num); //TODO MOZE WYWALIC BLAD
        } else {
            insertNotFirstNumber(*ans,numbers->number, level, num);
        }
        numbers = numbers->next;
    }
    return true;
}

PhoneNumbers *phfwdReverse( PhoneForward const *pf,char const *num) {

    PhoneNumbers *ans;

    if (pf != NULL){
       giveReverse(pf->reverse,num,&ans);
       return ans;
    } else {
        return NULL; //TODO to zmienic zeby dawalo num
    }
}
