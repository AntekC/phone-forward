//
// Created by Antoni Bryk on 30/05/2022.
//

#ifndef PHONE_NUMBERS_TRIE_H
#define PHONE_NUMBERS_TRIE_H

#define NUMBER_OF_CHILDREN 10

typedef struct Trie Trie;
struct Trie {
    Trie *child[NUMBER_OF_CHILDREN];
    PhoneNumbers *numbers;
};


Trie *newNode();

void deleteTrie(Trie *trie);

void deleteForwardTrie(Trie *trie, Trie *reverse_trie, char const *num);

void deleteNumberFromReverse(Trie *reverse, char const *number_reverse, char const *number_to_delete);

bool insert(Trie *trie, Trie *reverse_trie, char const *num1, char const *num2, bool reverse);


#endif //PHONE_NUMBERS_TRIE_H
