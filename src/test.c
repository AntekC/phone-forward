#ifdef NDEBUG
#undef NDEBUG
#endif

#include "phone_forward.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 23


int main() {
    char num1[MAX_LEN + 1], num2[MAX_LEN + 1], num3[MAX_LEN + 1];

    PhoneForward *pf;
    PhoneNumbers *pnum;

    pf = phfwdNew();
    for(int i = 0; i < MAX_LEN; ++i){

    }
    strcpy(num1, "123");
    strcpy(num2, "9");

    phfwdAdd(pf, num1, num2);

    printf("added 123\n");

    strcpy(num1, "124");
    strcpy(num2, "8");

    phfwdAdd(pf, num1, num2);

    strcpy(num1, "9234554454");
    strcpy(num2, "9");

    phfwdAdd(pf, num1, num2);

    strcpy(num1, "824314123");
    strcpy(num2, "9");

    phfwdAdd(pf, num1, num2);

    strcpy(num1, "7699123");
    strcpy(num2, "9");

    phfwdAdd(pf, num1, num2);

    strcpy(num1, "68969123");
    strcpy(num2, "9");

    phfwdAdd(pf, num1, num2);

    strcpy(num1, "579123");
    strcpy(num2, "9");

    phfwdAdd(pf, num1, num2);

    strcpy(num1, "4878123");
    strcpy(num2, "9");

    phfwdAdd(pf, num1, num2);

    phfwdDelete(pf);

    return 0;

}

