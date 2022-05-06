#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define NUMBER_OF_CHILDREN 10

typedef struct PhoneNumbers PhoneNumbers;
typedef struct PhoneForward PhoneForward;

struct PhoneNumbers {
    PhoneNumbers *next;
    char *number;
};

struct PhoneForward {
    PhoneForward *child[NUMBER_OF_CHILDREN];
    char *forward;
    bool is_forward;
};

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

    ans->is_forward = false;
    ans->forward = NULL;
    for (int i = 0; i < NUMBER_OF_CHILDREN; ++i) {
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
    //TODO rozbic na zmienne bool
    if (pf == NULL || number1_length == 0
        || number2_length == 0 || areNumbersIndentical(num1, num2)) {

        return false;
    }

    for (size_t level = 0; level < number1_length; ++level) {
        int index = num1[level] - '0';//TODO zrobic funkcje charToInt()

        if (pf->child[index] == NULL) {
            pf->child[index] = newEmptyNode();
            //TODO obludga bledy pamieci
        }

        pf = pf->child[index];

        if (level == number1_length - 1) {
            pf->is_forward = true;
            pf->forward = makeCopy(num2);
            //TODO obsługa błędu pamięci
        } //TODO wyrzucic to poza fora
    }

    return true;
}

PhoneForward *phfwdNew(void) {
    return newEmptyNode();
    //TODO obsluga bledu
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
    if (pf == NULL || numberLength(num) == 0) {
        return NULL;
    }
    PhoneForward *save = NULL;//TODO zmienic nazwy
    size_t level_save = 0;

    size_t number_length = numberLength(num);

    for (size_t level = 0; level < number_length; ++level) {
        int index = num[level] - '0';

        if (pf->child[index] == NULL) {
            break;
        } else if (pf->child[index]->is_forward) {
            save = pf->child[index];
            level_save = level;
        }

        pf = pf->child[index];
    }
    if (save == NULL) {
        return newPhoneNumber(makeCopy(num));
    } else {
        return newPhoneNumber(combineNumbers(save->forward, num + level_save + 1));
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


//int main(){
//
//    char num1[MAX + 1], num2[MAX + 1];
//    PhoneForward *pf;
//    PhoneNumbers *pnum;
//
//    pf = phfwdNew();
//
//    strcpy(num1, "123");
//    strcpy(num2, "9");
//
//    assert(strcmp(combineNumbers(num1,num2),"1239") == 0);
//
//    strcpy(num1, "123");
//    strcpy(num2, "");
//
//    assert(strcmp(combineNumbers(num1,num2),"123") == 0);
//
//    strcpy(num1, "");
//    strcpy(num2, "1239");
//
//    assert(strcmp(combineNumbers(num1,num2),"1239") == 0);
//
//    strcpy(num1, "");
//    strcpy(num2, "");
//
//    assert(strcmp(combineNumbers(num1,num2),"") == 0);
//
//    strcpy(num1, "131");
//    strcpy(num2, "131");
//
//    assert(strcmp(combineNumbers(num1,num2),"131131") == 0);
//
//    return 0;
//}