#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
//#include "phone_forward.h"

typedef struct PhoneNumbers PhoneNumbers;
typedef struct PhoneForward PhoneForward;

struct PhoneNumbers{
    int a;
};

#define NUMBER_OF_CHILDS 10

struct PhoneForward{
    PhoneForward *child[NUMBER_OF_CHILDS];
    char* przkierowanie;
    bool isEnd;
    bool isForward;
};

PhoneForward* newNode(void){
    PhoneForward *ans = malloc(sizeof (PhoneForward));
    //TODO obsługa błędu pamięci
    ans->isEnd = false;
    ans->isForward = false;
    ans->przkierowanie = NULL;
    for(int i = 0; i < NUMBER_OF_CHILDS; ++i){
        ans->child[i] = NULL;
    }
    return ans;
}



int numberLen(char const *number){
    int ans = 0;
    while(isdigit(*number)){
        ++ans;
        ++number;
    }
    return ans;
}

char* makeCopy(char const *number){
    size_t number_length = numberLen(number);
    char* ans = malloc(number_length * sizeof(char)+1);
    if(ans == NULL) exit(1);
	for(int i = 0; i < number_length; ++i){
        ans[i] = number[i];
    }
	ans[numberLen(number)] = '\0';
    return ans;
}

PhoneForward * phfwdNew(void){
    return newNode();
}

void insert(PhoneForward *pf, char const *num1, char const *num2){
    size_t number_length = numberLen(num1);
    for(int level = 0; level < number_length; ++level){
        int index = num1[level] - '0';
        if(pf->child[index] == NULL){
            pf->child[index] = newNode();
        }
        pf = pf->child[index];

        if(level == (int) number_length - 1){
            pf->isForward = true;
            pf->przkierowanie = makeCopy(num2);
        }
    }

}


void phfwdDelete(PhoneForward *pf){
    for(int i = 0; i < NUMBER_OF_CHILDS; ++i){
        if(pf->child[i] != NULL){
            phfwdDelete(pf->child[i]);
        }
    }
    if(pf->isForward){
        free(pf->przkierowanie);
    }
    free(pf);
}

void printNumber(char *number){
    for(int i = 0; i < numberLen(number); ++i){
        printf("%c",number[i]);
    }
    printf("\n");
}

void printTrie(PhoneForward *pf){
    for(int i = 0; i < NUMBER_OF_CHILDS; ++i){
        if(pf->child[i] != NULL){

            printf("%c ", i + '0');

            if(pf->child[i]->isForward){
                printf("Przkierowanie ostani = %c\n",i + '0');
                if(pf->child[i]->przkierowanie != NULL) printNumber(pf->child[i]->przkierowanie);
            }
            printTrie(pf->child[i]);
        }

    }
}

bool phfwdAdd(PhoneForward *pf, char const *num1, char const *num2){
    insert(pf,num1,num2);
    printTrie(pf);
    return true;
}

void phfwdRemove(PhoneForward *pf, char const *num){
    ;
}

PhoneNumbers * phfwdGet(PhoneForward const *pf, char const *num){
    return phfwdNew();
}

PhoneNumbers * phfwdReverse(PhoneForward const *pf, char const *num){
    return phfwdNew();
}

void phnumDelete(PhoneNumbers *pnum){
    if(pnum != NULL){
        free(pnum);
    }
}

char const * phnumGet(PhoneNumbers const *pnum, size_t idx){
    char const* a = malloc(sizeof(char));
    return a;
}



