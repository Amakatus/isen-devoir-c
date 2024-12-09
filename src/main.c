#include <stdio.h>
#include "include/file.h"
#include "include/word.h"
#include "include/search.h"

#define MAX_FILES 40
#define PROJECT_NAME "C-search"

int main(int argc, char const *argv[])
{
    char* safe_files[MAX_FILES];
    int safe_file_count = 0;
    sendSafeFile(argv, safe_files, &safe_file_count);
    for (int i = 0; i < safe_file_count; i++) {
        printf("\n------------NOUVEAU FICHIER-----------\n\n");
        struct LinkedList* wordList = NULL;
        if (readFile(safe_files[i], &wordList) == 0) {
            //printWords(wordList);
            searchExactWord(wordList, "Bonjour");
        }
        freeStructs(wordList);
    }
    return 0;
}
