#ifdef NDEBUG
#undef NDEBUG
#endif

#include "phone_forward.h"
#include "phone_numbers_operations.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAX_LEN 23

void printTestSuccess(int n){
    printf("test succes %d\n",n);
}

int main() {

    if(compareNumbers("1934","1238934")){
        printf("first\n");
    }
    PhoneNumbers *pnum;
    PhoneForward *pf = phfwdNew();
    pf = phfwdNew();

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
    printTestSuccess(800);

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
    printTestSuccess(801);

    phfwdDelete(pf);

    pf = phfwdNew();

    // No forwards exist
    pnum = phfwdGetReverse(pf, "123");
    assert(strcmp(phnumGet(pnum, 0), "123") == 0);
    assert(phnumGet(pnum, 1) == NULL);
    phnumDelete(pnum);
    printTestSuccess(802);

    // Wrong forward only
    assert(phfwdAdd(pf, "123", "5") == true);

    pnum = phfwdGetReverse(pf, "123");
    assert(pnum != NULL);
    assert(phnumGet(pnum, 0) == NULL);
    phnumDelete(pnum);
    printTestSuccess(803);

    // Test 1
    assert(phfwdAdd(pf, "2", "34") == true);
    assert(phfwdAdd(pf, "6", "3") == true);
    assert(phfwdAdd(pf, "64", "3") == true);

    pnum = phfwdReverse(pf, "342");
    assert(strcmp(phnumGet(pnum, 0), "22") == 0);
    assert(strcmp(phnumGet(pnum, 1), "342") == 0);
    assert(strcmp(phnumGet(pnum, 2), "642") == 0);
    assert(strcmp(phnumGet(pnum, 3), "6442") == 0);
    assert(phnumGet(pnum, 4) == NULL);
    phnumDelete(pnum);

    pnum = phfwdGetReverse(pf, "342");
    assert(strcmp(phnumGet(pnum, 0), "22") == 0);
    assert(strcmp(phnumGet(pnum, 1), "342") == 0);
    assert(strcmp(phnumGet(pnum, 2), "6442") == 0);
    assert(phnumGet(pnum, 3) == NULL);
    phnumDelete(pnum);

    assert(phfwdAdd(pf, "342", "5") == true);

    pnum = phfwdReverse(pf, "342");
    assert(strcmp(phnumGet(pnum, 0), "22") == 0);
    assert(strcmp(phnumGet(pnum, 1), "342") == 0);
    assert(strcmp(phnumGet(pnum, 2), "642") == 0);
    assert(strcmp(phnumGet(pnum, 3), "6442") == 0);
    assert(phnumGet(pnum, 4) == NULL);
    phnumDelete(pnum);

    pnum = phfwdGetReverse(pf, "342");
    assert(strcmp(phnumGet(pnum, 0), "22") == 0);
    assert(strcmp(phnumGet(pnum, 1), "6442") == 0);
    assert(phnumGet(pnum, 2) == NULL);
    phnumDelete(pnum);

    phfwdRemove(pf, "64");

    pnum = phfwdReverse(pf, "342");
    assert(strcmp(phnumGet(pnum, 0), "22") == 0);
    assert(strcmp(phnumGet(pnum, 1), "342") == 0);
    assert(strcmp(phnumGet(pnum, 2), "642") == 0);
    assert(phnumGet(pnum, 4) == NULL);
    phnumDelete(pnum);

    pnum = phfwdGetReverse(pf, "342");
    assert(strcmp(phnumGet(pnum, 0), "22") == 0);
    assert(strcmp(phnumGet(pnum, 1), "642") == 0);
    assert(phnumGet(pnum, 3) == NULL);
    phnumDelete(pnum);

    phfwdDelete(pf);
    printTestSuccess(804);

    // Test 2
    pf = phfwdNew();

    assert(phfwdAdd(pf, "64", "31") == true);
    assert(phfwdAdd(pf, "645", "3") == true);

    pnum = phfwdReverse(pf, "315");
    assert(strcmp(phnumGet(pnum, 0), "315") == 0);
    assert(strcmp(phnumGet(pnum, 1), "645") == 0);
    assert(strcmp(phnumGet(pnum, 2), "64515") == 0);
    assert(phnumGet(pnum, 3) == NULL);
    phnumDelete(pnum);

    pnum = phfwdGetReverse(pf, "315");
    assert(strcmp(phnumGet(pnum, 0), "315") == 0);
    assert(strcmp(phnumGet(pnum, 1), "64515") == 0);
    assert(phnumGet(pnum, 2) == NULL);
    phnumDelete(pnum);

    assert(phfwdAdd(pf, "315", "5") == true);

    pnum = phfwdReverse(pf, "315");
    assert(strcmp(phnumGet(pnum, 0), "315") == 0);
    assert(strcmp(phnumGet(pnum, 1), "645") == 0);
    assert(strcmp(phnumGet(pnum, 2), "64515") == 0);
    assert(phnumGet(pnum, 3) == NULL);
    phnumDelete(pnum);

    pnum = phfwdGetReverse(pf, "315");
    assert(strcmp(phnumGet(pnum, 0), "64515") == 0);
    assert(phnumGet(pnum, 1) == NULL);
    phnumDelete(pnum);

    phfwdRemove(pf, "645");

    pnum = phfwdReverse(pf, "315");
    assert(strcmp(phnumGet(pnum, 0), "315") == 0);
    assert(strcmp(phnumGet(pnum, 1), "645") == 0);
    assert(phnumGet(pnum, 2) == NULL);
    phnumDelete(pnum);

    pnum = phfwdGetReverse(pf, "315");
    assert(strcmp(phnumGet(pnum, 0), "645") == 0);
    assert(phnumGet(pnum, 1) == NULL);
    phnumDelete(pnum);

    phfwdDelete(pf);
    printTestSuccess(805);

    // Test 3
    pf = phfwdNew();

    assert(phfwdAdd(pf, "1", "78") == true);
    assert(phfwdAdd(pf, "12", "789") == true);
    assert(phfwdAdd(pf, "123", "7") == true);
    assert(phfwdAdd(pf, "1234", "789*") == true);

    pnum = phfwdReverse(pf, "78934");
    assert(strcmp(phnumGet(pnum, 0), "1234") == 0);
    assert(strcmp(phnumGet(pnum, 1), "1238934") == 0);
    assert(strcmp(phnumGet(pnum, 2), "1934") == 0);
    assert(strcmp(phnumGet(pnum, 3), "78934") == 0);
    assert(phnumGet(pnum, 4) == NULL);
    phnumDelete(pnum);

    pnum = phfwdGetReverse(pf, "78934");
    assert(strcmp(phnumGet(pnum, 0), "1238934") == 0);
    assert(strcmp(phnumGet(pnum, 1), "1934") == 0);
    assert(strcmp(phnumGet(pnum, 2), "78934") == 0);
    assert(phnumGet(pnum, 3) == NULL);
    phnumDelete(pnum);

    assert(phfwdAdd(pf, "78934", "2") == true);

    pnum = phfwdReverse(pf, "78934");
    assert(strcmp(phnumGet(pnum, 0), "1234") == 0);
    assert(strcmp(phnumGet(pnum, 1), "1238934") == 0);
    assert(strcmp(phnumGet(pnum, 2), "1934") == 0);
    assert(strcmp(phnumGet(pnum, 3), "78934") == 0);
    assert(phnumGet(pnum, 4) == NULL);
    phnumDelete(pnum);

    pnum = phfwdGetReverse(pf, "78934");
    assert(strcmp(phnumGet(pnum, 0), "1238934") == 0);
    assert(strcmp(phnumGet(pnum, 1), "1934") == 0);
    assert(phnumGet(pnum, 2) == NULL);
    phnumDelete(pnum);

    assert(phfwdAdd(pf, "1238", "4") == true);
    phfwdRemove(pf, "1234");

    pnum = phfwdReverse(pf, "78934");
    assert(strcmp(phnumGet(pnum, 0), "1234") == 0);
    assert(strcmp(phnumGet(pnum, 1), "1238934") == 0);
    assert(strcmp(phnumGet(pnum, 2), "1934") == 0);
    assert(strcmp(phnumGet(pnum, 3), "78934") == 0);
    assert(phnumGet(pnum, 4) == NULL);
    phnumDelete(pnum);

    pnum = phfwdGetReverse(pf, "78934");
    assert(strcmp(phnumGet(pnum, 0), "1934") == 0);
    assert(phnumGet(pnum, 1) == NULL);
    phnumDelete(pnum);

    phfwdDelete(pf);
    printTestSuccess(806);

    // Repeating numbers in result
    pf = phfwdNew();
    assert(phfwdAdd(pf, "1", "5") == true);
    assert(phfwdAdd(pf, "11", "51") == true);
    assert(phfwdAdd(pf, "111", "511") == true);

    pnum = phfwdReverse(pf, "111");
    assert(strcmp(phnumGet(pnum, 0), "111") == 0);
    assert(phnumGet(pnum, 1) == NULL);
    phnumDelete(pnum);
    printTestSuccess(807);

    phfwdDelete(pf);

    printf("Testing incorrect input in phfwdGetReverse\n");
    pf = phfwdNew();

    assert(phfwdGetReverse(NULL, "123") == NULL);
    printTestSuccess(900);
    pnum = phfwdGetReverse(pf, NULL);
    assert(pnum != NULL);
    assert(phnumGet(pnum, 0) == NULL);
    phnumDelete(pnum);
    printTestSuccess(901);
    pnum = phfwdGetReverse(pf, "");
    assert(pnum != NULL);
    assert(phnumGet(pnum, 0) == NULL);
    phnumDelete(pnum);
    printTestSuccess(902);
    pnum = phfwdGetReverse(pf, "94bs");
    assert(pnum != NULL);
    assert(phnumGet(pnum, 0) == NULL);
    phnumDelete(pnum);
    printTestSuccess(903);
    pnum = phfwdGetReverse(pf, "abc");
    assert(pnum != NULL);
    assert(phnumGet(pnum, 0) == NULL);
    phnumDelete(pnum);
    printTestSuccess(904);
    pnum = phfwdGetReverse(pf, ";");
    assert(pnum != NULL);
    assert(phnumGet(pnum, 0) == NULL);
    phnumDelete(pnum);
    printTestSuccess(905);
    pnum = phfwdGetReverse(pf, "<>");
    assert(pnum != NULL);
    assert(phnumGet(pnum, 0) == NULL);
    phnumDelete(pnum);
    printTestSuccess(906);
    pnum = phfwdGetReverse(pf, "?!");
    assert(pnum != NULL);
    assert(phnumGet(pnum, 0) == NULL);
    phnumDelete(pnum);
    printTestSuccess(907);

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
