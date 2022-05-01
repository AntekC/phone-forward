#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

#define NUMBER_OF_CHILDS 10

typedef struct PhoneNumbers PhoneNumbers;
typedef struct PhoneForward PhoneForward;

struct PhoneNumbers {
    PhoneNumbers *next;
    char *number;
};

struct PhoneForward {
    PhoneForward *child[NUMBER_OF_CHILDS];
    char *forward;
    bool isForward;
};

static int numberLength(char const *number) {
    int ans = 0;
    if (number == NULL) {
        return 0;
    }

    while (isdigit(*number)) {
        ++ans;
        ++number;
    }

    if (*number != '\0') {
        return 0;
    } else {
        return ans;
    }
}

static char *combineNumbers(char const *num1, char const *num2) {
    size_t num1_length = numberLength(num1);
    size_t num2_length = numberLength(num2);
    char *ans = malloc((num1_length + num2_length + 1) * sizeof(char));
    //TODO obluga bledu pamieci

    for (size_t i = 0; i < num1_length; ++i) {
        ans[i] = num1[i];
    }
    for (size_t i = num1_length; i < num1_length + num2_length; ++i) {
        ans[i] = num2[i - num1_length];
    }
    ans[num1_length + num2_length] = '\0';

    return ans;
}

static bool compareNumbers(char const *num1, char const *num2) {
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

static char *makeCopy(char const *number) {
    size_t number_length = numberLength(number);
    char *ans = malloc(number_length * sizeof(char) + 1);
    if (ans == NULL) exit(1); //TODO obsluga bledu

    for (size_t i = 0; i < number_length; ++i) {
        ans[i] = number[i];
    }
    ans[number_length] = '\0';

    return ans;
}

static PhoneForward *newEmptyNode(void) {
    PhoneForward *ans = malloc(sizeof(PhoneForward));
    if (ans == NULL) {
        return NULL;
    }

    ans->isForward = false;
    ans->forward = NULL;
    for (int i = 0; i < NUMBER_OF_CHILDS; ++i) {
        ans->child[i] = NULL;
    }

    return ans;
}

static PhoneNumbers *newPhoneNumber(char *number) {
    PhoneNumbers *ans = malloc(sizeof(PhoneNumbers));
    if (ans == NULL) {
        return NULL;
    }

    ans->number = number;
    ans->next = NULL;

    return ans;
}

static bool insert(PhoneForward *pf, char const *num1, char const *num2) {
    size_t number1_length = numberLength(num1);
    size_t number2_length = numberLength(num2);
    if (pf == NULL || number1_length == 0
        || number2_length == 0 || compareNumbers(num1, num2)) {

        return false;
    }

    for (size_t level = 0; level < number1_length; ++level) {
        int index = num1[level] - '0';

        if (pf->child[index] == NULL) {
            pf->child[index] = newEmptyNode();
            //TODO obludga bledy pamieci
        }

        pf = pf->child[index];

        if (level == number1_length - 1) {
            pf->isForward = true;
            pf->forward = makeCopy(num2);
            //TODO obsługa błędu pamięci
        }
    }
    return true;
}

PhoneForward *phfwdNew(void) {
    return newEmptyNode();
    //TODO obsluga bledu
}

void phfwdDelete(PhoneForward *pf) {
    if (pf != NULL) {
        for (size_t i = 0; i < NUMBER_OF_CHILDS; ++i) {
            phfwdDelete(pf->child[i]);
        }
        if (pf->isForward) {
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
    if (pf == NULL || numberLength(num) == 0) {
        return NULL;
    }

    size_t number_length = numberLength(num);
    PhoneNumbers *ans = newPhoneNumber(makeCopy(num));

    for (size_t level = 0; level < number_length; ++level) {
        int index = num[level] - '0';

        if (pf->child[index] == NULL) {
            return ans;
        } else if (pf->child[index]->isForward) {
            phnumDelete(ans);
            ans = newPhoneNumber(combineNumbers(pf->child[index]->forward, num + level + 1));
        }

        pf = pf->child[index];
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
    return newPhoneNumber(NULL);
}
