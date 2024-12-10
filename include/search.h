#ifndef SEARCH_H
#define SEARCH_H
#include "include/linkedlist.h"
#include "word.h"

void print_search_match(struct LinkedList* linkedList);
void search_exact_word(struct LinkedList* wordList, const char* word);
void search_case_insensitive(struct LinkedList* wordlist, const char* word);

#endif
