#ifndef CREATE_WORD_H
#define CREATE_WORD_H

struct LinkedList;

struct Word {
    char* word;
    const char* fileName;
    struct LinkedList* files;
    struct LinkedList* line_numbers;
    int count;
};

struct LinkedList* createWord(const char* word, int line_number,const char* fileName);
int checkIfWordExist(struct LinkedList* wordList, const char* word);
void addWord(struct LinkedList** wordList, const char* word, int line_number,const char* fileName);
void searchWord(struct LinkedList* linkedList, const char* word, int casesensitive);
void printWords(struct LinkedList* linkedList);


#endif
