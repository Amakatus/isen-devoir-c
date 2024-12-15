#ifndef SEARCH_H
#define SEARCH_H
#include "linkedlist.h"
#include "word.h"

void print_search_match(struct LinkedList* linkedList);
void search_exact_word(struct LinkedList* wordList, char* word);
void search_case_insensitive(struct LinkedList* wordlist, const char* word);
void search_wildcard(struct LinkedList* wordList, const char* word);

#endif
