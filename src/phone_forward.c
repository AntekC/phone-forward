#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

#define NUMBER_OF_CHILDS 10

typedef struct PhoneNumbers PhoneNumbers;
typedef struct PhoneForward PhoneForward;

struct PhoneNumbers {
    char *number;
    PhoneNumbers *next;
};

struct PhoneForward {
    PhoneForward *child[NUMBER_OF_CHILDS];
    char *przkierowanie;
    bool isForward;
};

static PhoneForward *newNode(void) {
    PhoneForward *ans = malloc(sizeof(PhoneForward));
    //TODO obsługa błędu pamięci
    ans->isForward = false;
    ans->przkierowanie = NULL;
    for (int i = 0; i < NUMBER_OF_CHILDS; ++i) {
        ans->child[i] = NULL;
    }
    return ans;
}

PhoneNumbers *newPhoneNumber(char const *number, PhoneNumbers *next) {
    PhoneNumbers *ans = malloc(sizeof(PhoneNumbers));
    ans->number = number;
    ans->next = next;
    return ans;
}

int numberLen(char const *number) {
    int ans = 0;
    while (isdigit(*number)) {
        ++ans;
        ++number;
    }
    return ans;
}

char *makeCopy(char const *number) {
    size_t number_length = numberLen(number);
    char *ans = malloc(number_length * sizeof(char) + 1);
    if (ans == NULL) exit(1); //TODO obsluga bledu

    for (size_t i = 0; i < number_length; ++i) {
        ans[i] = number[i];
    }
    ans[numberLen(number)] = '\0';

    return ans;
}

PhoneForward *phfwdNew(void) {
    return newNode();
}

void insert(PhoneForward *pf, char const *num1, char const *num2) {
    size_t number_length = numberLen(num1);

    for (size_t level = 0; level < number_length; ++level) {
        int index = num1[level] - '0';

        if (pf->child[index] == NULL) {
            pf->child[index] = newNode();
        }

        pf = pf->child[index];

        if (level == number_length - 1) {
            pf->isForward = true;
            pf->przkierowanie = makeCopy(num2);
        }
    }
}

void phfwdDelete(PhoneForward *pf) {
    for (int i = 0; i < NUMBER_OF_CHILDS; ++i) {
        if (pf->child[i] != NULL) {
            phfwdDelete(pf->child[i]);
        }
    }
    if (pf->isForward) {
        free(pf->przkierowanie);
    }
    free(pf);
}

void printNumber(char *number) {
    for (int i = 0; i < numberLen(number); ++i) {
        printf("%c", number[i]);
    }
    printf("\n");
}

void printTrie(PhoneForward *pf) {
    if (pf != NULL) {
        for (int i = 0; i < NUMBER_OF_CHILDS; ++i) {
            if (pf->child[i] != NULL) {

                printf("%c ", i + '0');

                if (pf->child[i]->isForward) {
                    printf("Przkierowanie ostani = %c numer przekierowania = ", i + '0');
                    if (pf->child[i]->przkierowanie != NULL) printNumber(pf->child[i]->przkierowanie);
                }
                printTrie(pf->child[i]);
            }

        }
    }
}

bool phfwdAdd(PhoneForward *pf, char const *num1, char const *num2) {
    insert(pf, num1, num2);
    printTrie(pf);
    return true;
}

void phfwdRemove(PhoneForward *pf, char const *num) {
    size_t number_length = numberLen(num);

    for (size_t level = 0; level < number_length; ++level) {
        int index = num[level] - '0';

        if (level == number_length - 1) {
            phfwdDelete(pf->child[index]);
            pf->child[index] = NULL;
        } else if (pf->child[index] == NULL) {
            break;
        }

        pf = pf->child[index];
    }
}

char *combineNumbers(char const *num1, char const *num2) {
    size_t num1_length = numberLen(num1);
    size_t num2_length = numberLen(num2);
    char *ans = malloc((num1_length + num2_length + 1) * sizeof(char));
    for (size_t i = 0; i < num1_length; ++i) {
        ans[i] = num1[i];
    }
    for (size_t i = num1_length; i < num1_length + num2_length; ++i) {
        ans[i] = num2[i - num1_length];
    }
    ans[num1_length + num2_length] = '\0';

    return ans;
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
    size_t number_length = numberLen(num);
    PhoneNumbers *ans = newPhoneNumber(makeCopy(num), NULL);

    for (size_t level = 0; level < number_length; ++level) {
        int index = num[level] - '0';

        if (pf->child[index] == NULL) {
            return ans;
        } else if (pf->child[index]->isForward) {
            phnumDelete(ans);
            ans = newPhoneNumber(combineNumbers(pf->child[index]->przkierowanie, num + level + 1), NULL);
        }

        pf = pf->child[index];
    }

    return ans;
}

PhoneNumbers *phfwdReverse(PhoneForward const *pf, char const *num) {
    ;
}


char const *phnumGet(PhoneNumbers const *pnum, size_t idx) {
    for (size_t i = 0; i < idx; ++i) {
        if (pnum != NULL) {
            pnum = pnum->next;
        } else {
            break;
        }
    }
    return pnum->number;
}



