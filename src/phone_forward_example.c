#ifdef NDEBUG
#undef NDEBUG
#endif

#include "phone_forward.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAX_LEN 23

int main() {
    PhoneNumbers *pnum;
    PhoneForward *pf = phfwdNew();
    assert(phfwdAdd(pf, "0", "51") == true);
    assert(phfwdAdd(pf, "1", "51") == true);
    assert(phfwdAdd(pf, "2", "51") == true);
    assert(phfwdAdd(pf, "3", "51") == true);
    assert(phfwdAdd(pf, "4", "51") == true);
    assert(phfwdAdd(pf, "5", "51") == true);
    assert(phfwdAdd(pf, "6", "51") == true);
    assert(phfwdAdd(pf, "7", "51") == true);
    assert(phfwdAdd(pf, "8", "51") == true);
    assert(phfwdAdd(pf, "9", "51") == true);
    assert(phfwdAdd(pf, "*", "51") == true);
    assert(phfwdAdd(pf, "#", "51") == true);

    pnum = phfwdGetReverse(pf, "51");
    assert(strcmp(phnumGet(pnum, 0), "0") == 0);
    assert(strcmp(phnumGet(pnum, 1), "1") == 0);
    assert(strcmp(phnumGet(pnum, 2), "2") == 0);
    assert(strcmp(phnumGet(pnum, 3), "3") == 0);
    assert(strcmp(phnumGet(pnum, 4), "4") == 0);
    assert(strcmp(phnumGet(pnum, 5), "5") == 0);
    assert(strcmp(phnumGet(pnum, 6), "6") == 0);
    assert(strcmp(phnumGet(pnum, 7), "7") == 0);
    assert(strcmp(phnumGet(pnum, 8), "8") == 0);
    assert(strcmp(phnumGet(pnum, 9), "9") == 0);
    assert(strcmp(phnumGet(pnum, 10), "*") == 0);
    assert(strcmp(phnumGet(pnum, 11), "#") == 0);
    assert(phnumGet(pnum, 12) == NULL);
    phnumDelete(pnum);
    printf("800\n");

    phfwdRemove(pf, "0");
    phfwdRemove(pf, "5");
    phfwdRemove(pf, "#");

    pnum = phfwdGetReverse(pf, "51");
    assert(strcmp(phnumGet(pnum, 0), "1") == 0);
    assert(strcmp(phnumGet(pnum, 1), "2") == 0);
    assert(strcmp(phnumGet(pnum, 2), "3") == 0);
    assert(strcmp(phnumGet(pnum, 3), "4") == 0);
    assert(strcmp(phnumGet(pnum, 4), "51") == 0);
    assert(strcmp(phnumGet(pnum, 5), "6") == 0);
    assert(strcmp(phnumGet(pnum, 6), "7") == 0);
    assert(strcmp(phnumGet(pnum, 7), "8") == 0);
    assert(strcmp(phnumGet(pnum, 8), "9") == 0);
    assert(strcmp(phnumGet(pnum, 9), "*") == 0);
    assert(phnumGet(pnum, 10) == NULL);
    phnumDelete(pnum);
    printf("801\n");

    phfwdDelete(pf);
//  char num1[MAX_LEN + 1], num2[MAX_LEN + 1];
//  PhoneForward *pf;
//  PhoneNumbers *pnum;
//
//  pf = phfwdNew();
//
//
//  strcpy(num1, "123");
//  strcpy(num2, "9");
//  assert(phfwdAdd(pf, num1, num2) == true);
//  memset(num1, 0, sizeof num1);
//  memset(num2, 0, sizeof num2);
//
//  pnum = phfwdGet(pf, "1234");
//  assert(strcmp(phnumGet(pnum, 0), "94") == 0);
//  assert(phnumGet(pnum, 1) == NULL);
//  phnumDelete(pnum);
//
//
//  pnum = phfwdGet(pf, "12");
//  assert(strcmp(phnumGet(pnum, 0), "12") == 0);
//  phnumDelete(pnum);
//
//  strcpy(num1, "123456");
//  strcpy(num2, "777777");
//  assert(phfwdAdd(pf, num1, num2) == true);
//
//  pnum = phfwdGet(pf, "12345");
//  assert(strcmp(phnumGet(pnum, 0), "945") == 0);
//  phnumDelete(pnum);
//
//  pnum = phfwdGet(pf, "123456");
//  assert(strcmp(phnumGet(pnum, 0), "777777") == 0);
//  phnumDelete(pnum);
//
//  pnum = phfwdGet(pf, "997");
//  assert(strcmp(phnumGet(pnum, 0), "997") == 0);
//  phnumDelete(pnum);
//
//  assert(phfwdAdd(pf, "431", "432") == true);
//  assert(phfwdAdd(pf, "432", "433") == true);
//  pnum = phfwdGet(pf, "431");
//  assert(strcmp(phnumGet(pnum, 0), "432") == 0);
//  phnumDelete(pnum);
//  pnum = phfwdGet(pf, "432");
//  assert(strcmp(phnumGet(pnum, 0), "433") == 0);
//  phnumDelete(pnum);
//
//   pnum = phfwdReverse(pf, "432");
//   assert(strcmp(phnumGet(pnum, 0), "431") == 0);
//   assert(strcmp(phnumGet(pnum, 1), "432") == 0);
//   assert(phnumGet(pnum, 2) == NULL);
//   phnumDelete(pnum);
//
//   pnum = phfwdReverse(pf, "433");
//   assert(strcmp(phnumGet(pnum, 0), "432") == 0);
//   assert(strcmp(phnumGet(pnum, 1), "433") == 0);
//   assert(phnumGet(pnum, 2) == NULL);
//   phnumDelete(pnum);
//
//   pnum = phfwdReverse(pf, "987654321");
//   assert(strcmp(phnumGet(pnum, 0), "12387654321") == 0);
//   assert(strcmp(phnumGet(pnum, 1), "987654321") == 0);
//   assert(phnumGet(pnum, 2) == NULL);
//   phnumDelete(pnum);
//
//  phfwdRemove(pf, "12");
//
//  pnum = phfwdGet(pf, "123456");
//  assert(strcmp(phnumGet(pnum, 0), "123456") == 0);
//  phnumDelete(pnum);
//
//   pnum = phfwdReverse(pf, "987654321");
//   assert(strcmp(phnumGet(pnum, 0), "987654321") == 0);
//   assert(phnumGet(pnum, 1) == NULL);
//   phnumDelete(pnum);
//
//  assert(phfwdAdd(pf, "567", "0") == true);
//  assert(phfwdAdd(pf, "5678", "08") == true);
//
//   pnum = phfwdReverse(pf, "08");
//   assert(strcmp(phnumGet(pnum, 0), "08") == 0);
//   assert(strcmp(phnumGet(pnum, 1), "5678") == 0);
//   assert(phnumGet(pnum, 2) == NULL);
//   phnumDelete(pnum);
//
//  assert(phfwdAdd(pf, "A", "1") == false);
//  assert(phfwdAdd(pf, "1", "A") == false);
//
//  phfwdRemove(pf, "");
//  phfwdRemove(pf, NULL);
//
//  pnum = phfwdGet(pf, "A");
//  assert(phnumGet(pnum, 0) == NULL);
//  phnumDelete(pnum);
//
//   pnum = phfwdReverse(pf, "A");
//   assert(phnumGet(pnum, 0) == NULL);
//   phnumDelete(pnum);
//
//  phfwdAdd(pf, "12", "123");
//  pnum = phfwdGet(pf, "123");
//  assert(strcmp(phnumGet(pnum, 0), "1233") == 0);
//  phnumDelete(pnum);
//
//  phfwdAdd(pf, "2", "4");
//  phfwdAdd(pf, "23", "4");
//  // pnum = phfwdReverse(pf, "434");
//  // assert(strcmp(phnumGet(pnum, 0), "2334") == 0);
//  // assert(strcmp(phnumGet(pnum, 1), "234") == 0);
//  // assert(strcmp(phnumGet(pnum, 2), "434") == 0);
//  // assert(phnumGet(pnum, 3) == NULL);
//  // phnumDelete(pnum);
//
//  phfwdDelete(pf);
//  pnum = NULL;
//  phnumDelete(pnum);
//  pf = NULL;
//  phfwdDelete(pf);
//
//  pf = phfwdNew();
//  phfwdAdd(pf, "1234", "76");
//  pnum = phfwdGet(pf, "1234581");
//  assert(strcmp(phnumGet(pnum, 0), "76581") == 0);
//  phnumDelete(pnum);
//  pnum = phfwdGet(pf, "7581");
//  assert(strcmp(phnumGet(pnum, 0), "7581") == 0);
//  phnumDelete(pnum);
////   pnum = phfwdReverse(pf, "7581");
////   assert(strcmp(phnumGet(pnum, 0), "7581") == 0);
////   assert(phnumGet(pnum, 1) == NULL);
////   phnumDelete(pnum);
//  phfwdDelete(pf);
}
