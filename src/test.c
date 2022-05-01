#ifdef NDEBUG
#undef NDEBUG
#endif

#include "phone_forward.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 23

//int main() {
//    char num1[MAX_LEN + 1], num2[MAX_LEN + 1];
//    PhoneForward *pf;
//    PhoneNumbers *pnum;
//
//    pf = phfwdNew();
//
//    strcpy(num1, "123");
//    strcpy(num2, "9");
//    assert(phfwdAdd(pf, num1, num2) == true);
//    memset(num1, 0, sizeof num1);
//    memset(num2, 0, sizeof num2);
//
//    pnum = phfwdGet(pf, "1234");
//    assert(strcmp(phnumGet(pnum, 0), "94") == 0);
//    assert(phnumGet(pnum, 1) == NULL);
//    phnumDelete(pnum);
//
//    pnum = phfwdGet(pf, "12");
//    assert(strcmp(phnumGet(pnum, 0), "12") == 0);
//    phnumDelete(pnum);
//
//    strcpy(num1, "123456");
//    strcpy(num2, "777777");
//    assert(phfwdAdd(pf, num1, num2) == true);
//
//    pnum = phfwdGet(pf, "12345");
//    assert(strcmp(phnumGet(pnum, 0), "945") == 0);
//    phnumDelete(pnum);
//
//    pnum = phfwdGet(pf, "123456");
//    assert(strcmp(phnumGet(pnum, 0), "777777") == 0);
//    phnumDelete(pnum);
//
//    pnum = phfwdGet(pf, "997");
//    assert(strcmp(phnumGet(pnum, 0), "997") == 0);
//    phnumDelete(pnum);
//
//    assert(phfwdAdd(pf, "431", "432") == true);
//    assert(phfwdAdd(pf, "432", "433") == true);
//    pnum = phfwdGet(pf, "431");
//    assert(strcmp(phnumGet(pnum, 0), "432") == 0);
//    phnumDelete(pnum);
//    pnum = phfwdGet(pf, "432");
//    assert(strcmp(phnumGet(pnum, 0), "433") == 0);
//    phnumDelete(pnum);
//
//
//    phfwdRemove(pf, "12");
//
//    pnum = phfwdGet(pf, "123456");
//    assert(strcmp(phnumGet(pnum, 0), "123456") == 0);
//    phnumDelete(pnum);
//
//    assert(phfwdAdd(pf, "567", "0") == true);
//    assert(phfwdAdd(pf, "5678", "08") == true);
//
//
//    assert(phfwdAdd(pf, "A", "1") == false);
//    assert(phfwdAdd(pf, "1", "A") == false);
//
//    phfwdRemove(pf, "");
//    phfwdRemove(pf, NULL);
//
//    pnum = phfwdGet(pf, "A");
//    assert(phnumGet(pnum, 0) == NULL);
//    phnumDelete(pnum);
//
//
//    phfwdAdd(pf, "12", "123");
//    pnum = phfwdGet(pf, "123");
//    assert(strcmp(phnumGet(pnum, 0), "1233") == 0);
//    phnumDelete(pnum);
//
//    phfwdAdd(pf, "2", "4");
//    phfwdAdd(pf, "23", "4");
//
//
//    phfwdDelete(pf);
//    pnum = NULL;
//    phnumDelete(pnum);
//    pf = NULL;
//    phfwdDelete(pf);
//
//    pf = phfwdNew();
//    phfwdAdd(pf, "1234", "76");
//    pnum = phfwdGet(pf, "1234581");
//    assert(strcmp(phnumGet(pnum, 0), "76581") == 0);
//    phnumDelete(pnum);
//    pnum = phfwdGet(pf, "7581");
//    assert(strcmp(phnumGet(pnum, 0), "7581") == 0);
//
//    assert(phfwdAdd(pf,"999","999") == false);
//
//    phnumDelete(pnum);
//    phfwdDelete(pf);
//
//
//    printf("All test passed\n");
//    return 0;
//}

//void printNumber(char *number) {
//    for (size_t i = 0; i < numberLength(number); ++i) {
//        printf("%c", number[i]);
//    }
//    printf("\n");
//}

//void printTrie(PhoneForward *pf) {
//    if (pf != NULL) {
//        for (int i = 0; i < NUMBER_OF_CHILDS; ++i) {
//            if (pf->child[i] != NULL) {
//
//                printf("%c ", i + '0');
//
//                if (pf->child[i]->isForward) {
//                    printf("Przkierowanie ostani = %c numer przekierowania = ", i + '0');
//                    if (pf->child[i]->przkierowanie != NULL) printNumber(pf->child[i]->przkierowanie);
//                }
//                printTrie(pf->child[i]);
//            }
//
//        }
//    }
//}