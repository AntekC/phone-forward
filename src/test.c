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

    strcpy(num1, "123");
    strcpy(num2, "9");

    phfwdAdd(pf, num1, num2);

    strcpy(num1, "123456");
    strcpy(num2, "777777");

    phfwdAdd(pf, num1, num2);

    strcpy(num1, "123456");

    pnum = phfwdGet(pf,num1);

    puts(phnumGet(pnum,0));

    phfwdDelete(pf);

    return 0;

}

