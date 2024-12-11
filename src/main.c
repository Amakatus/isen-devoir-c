#include <stdio.h>
#include "file.h"
#include "word.h"
#include "search.h"
#include "linkedlist.h"

#define MAX_FILES 40
#define PROJECT_NAME "C-search"

int main(int argc, char const *argv[])
{
    char* safeFiles[MAX_FILES];
    int safeFileCount = 0;
    send_safe_file(argv, safeFiles, &safeFileCount);
    for (int i = 0; i < safeFileCount; i++) {
        printf("\n------------NOUVEAU FICHIER-----------\n\n");
        struct LinkedList* wordList = NULL;
        if (read_file(safeFiles[i], &wordList) == 0) {
            //printWords(wordList);
            search_case_insensitive(wordList, "Bonjour");
            search_case_insensitive(wordList, "bonjour");
        }
        free_structs(wordList);
    }
    return 0;
}
