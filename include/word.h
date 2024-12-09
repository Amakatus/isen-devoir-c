#ifndef CREATE_WORD_H
#include <stdio.h>

struct LinkedList;

struct Word {
    char* word;
    FILE file;
    struct LinkedList* line_numbers;
    int count;
};

struct LinkedList* createWord(const char* word, int line_number);
int checkifWordExist(struct LinkedList* wordList, const char* word);
void addWord(struct LinkedList** wordList, const char* word, int line_number);
void searchWord(struct LinkedList* linkedList, const char* word, int casesensitive);
void printWords(struct LinkedList* linkedList);

#endif
