#ifdef NDEBUG
#undef NDEBUG
#endif

#include "phone_forward.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 23


int main() {
    char num1[MAX_LEN + 1], num2[MAX_LEN + 1];

    PhoneForward *pf;
    PhoneNumbers *pnum;
    printf("lala\n");

    pf = phfwdNew();

    strcpy(num1, "123");
    strcpy(num2, "9");

    phfwdAdd(pf, num1, num2);

    printf("added 123\n");

    strcpy(num1, "124");
    strcpy(num2, "8");

    phfwdAdd(pf, num1, num2);
    

    return 0;

}

