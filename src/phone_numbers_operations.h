//
// Created by Antoni Bryk on 01/06/2022.
//

#ifndef PHONE_NUMBERS_PHONE_NUMBERS_OPERATIONS_H
#define PHONE_NUMBERS_PHONE_NUMBERS_OPERATIONS_H

#include <stdbool.h>
#include <stdlib.h>

size_t numberLength(char const *number);
char *combineNumbers(char const *num1, char const *num2);
bool areNumbersIndentical(char const *num1, char const *num2);
char *makeCopy(char const *number);
bool startsWith(char const *number, char const *prefix);



#endif //PHONE_NUMBERS_PHONE_NUMBERS_OPERATIONS_H
