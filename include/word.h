#ifndef CREATE_WORD_H
#define CREATE_WORD_H

struct LinkedList;

struct Word {
    char* word;
    struct File* file;
    struct LinkedList* line_numbers;
    int count;
};

struct LinkedList* createWord(const char* word, int line_number);
int checkIfWordExist(struct LinkedList* wordList, const char* word);
void addWord(struct LinkedList** wordList, const char* word, int line_number);
void searchWord(struct LinkedList* linkedList, const char* word, int casesensitive);
void printWords(struct LinkedList* linkedList);

#endif
