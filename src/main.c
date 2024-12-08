#include <stdio.h>
#include "include/file.h"
#include "include/word.h"

#define PROJECT_NAME "C-search"

int main(int argc, char const *argv[])
{
    struct LinkedList* wordList = NULL;
    char* safe_file[10] = listSafeFile(argv);
    readFile("./samples/test.txt",&wordList);
    printWords(wordList);
    searchWord(wordList,"Bonjour");
    freeStructs(wordList);
    return 0;
}
