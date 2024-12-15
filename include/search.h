#ifndef SEARCH_H
#define SEARCH_H
#include "linkedlist.h"
#include "word.h"

void print_search_match(struct Word* wordList);
void search_exact_word(struct LinkedList* wordList, char* word);
void search_case_insensitive(struct LinkedList* wordlist, char* word);
void search_wildcard(struct LinkedList* wordList, char* word);

#endif
