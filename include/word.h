#ifndef CREATE_WORD_H
#define CREATE_WORD_H

struct LinkedList;

struct Word {
    char* word;
    const char* fileName;
    struct LinkedList* lineNumbers;
    int count;
};

struct LinkedList* create_word(const char* word, int lineNumber,const char* fileName);
int check_if_word_exist(struct LinkedList* wordList, const char* word);
void add_word(struct LinkedList** wordList, const char* word, int lineNumber,const char* fileName);
void print_words(struct LinkedList* linkedList);


#endif
