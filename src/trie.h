//
// Created by Antoni Bryk on 30/05/2022.
//

#ifndef PHONE_NUMBERS_TRIE_H
#define PHONE_NUMBERS_TRIE_H

#define NUMBER_OF_CHILDREN 12

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

bool getFromReverse(Trie *reverse, char const *num, PhoneNumbers **ans);

void removeFromForward(Trie *forward, Trie *reverse, char const *num);

bool getFromForward(Trie *forward, char const *num, PhoneNumbers **ans);

#endif //PHONE_NUMBERS_TRIE_H
