#include "include/linkedlist.h"

void searchExactWord(struct LinkedList* wordList, const char* word){
    struct Word* result = (struct Word*)LinkedListSearch(wordList, int (*)(wordList, word), (void *)word);
    if (result != NULL){

    }
}
void searchCaseInsensitive(struct LinkedList* wordlist, const char* word){

}