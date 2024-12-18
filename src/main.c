#include <stdio.h>
#include "file.h"
#include "word.h"
#include "search.h"
#include "linkedlist.h"
#include "stdlib.h"
#include <string.h>

#define READ_LIMIT 300
#define MAX_FILES 40
#define PROJECT_NAME "C-search"

int main(int argc, char* argv[]) {
    char* safeFiles[MAX_FILES];
    int safeFileCount = 0;
    send_safe_file(argv, safeFiles, &safeFileCount);    
    while (1) {
        printf("\n------------ NOUVEAU TRAITEMENT ------------\n");
        printf("Fichier(s) à analyser :\n");
        for (int i = 0; i < safeFileCount; i++) {
            printf("%d. %s\n", i + 1, safeFiles[i]);
        }
        printf("Choisissez le fichier à analyser (1-%d) ou 0 pour quitter: ", safeFileCount);
        int fileChoice;
        scanf("%d", &fileChoice);
        if (fileChoice == 0) {
            break;
        } else if (fileChoice < 1 || fileChoice > safeFileCount) {
            printf("Choix invalide, veuillez réessayer.\n");
            continue;
        }
        struct LinkedList* wordList = NULL;
        if (read_file(safeFiles[fileChoice - 1], &wordList) == 0) {
            while (1) {
                printf("\n------------------------ MENU ------------------------\n");
                printf("1. Recherche exacte\n");
                printf("2. Recherche insensible à la casse\n");
                printf("3. Recherche avec joker\n");
                printf("4. Revenir à la sélection des fichiers\n");
                printf("5. Quitter\n");
                printf("------------------------------------------------------\n");
                printf("Veuillez choisir une option (1-5): ");
                int option;
                scanf("%d", &option);
                char* word = malloc(sizeof(char) * 300);
                switch (option) {
                    case 1:
                        printf("Veuillez entrer le mot cherché :\n");
                        scanf("%s", word);
                        search_exact_word(wordList, word);
                        free(word);
                        break;
                    case 2:
                        printf("Veuillez entrer le mot cherché :\n");
                        scanf("%s", word);    
                        search_case_insensitive(wordList, word);
                        free(word);
                        break;
                    case 3:
                        printf("Veuillez entrer le mot cherché :\n");
                        scanf("%s", word);                        
                        search_wildcard(wordList, word);
                        free(word);
                        break;
                    case 4:
                        printf("Retour à la sélection des fichiers...\n");
                        free_structs(wordList);
                        wordList = NULL;
                        break;
                    case 5:
                        printf("Au revoir !\n");
                        free_structs(wordList);
                        free(word);
                        return 0;
                    default:
                        printf("Option invalide. Essayez à nouveau.\n");
                        free(word);
                        break;
                }
                if (wordList == NULL) {
                    break;
                }
            }
        } else {
            printf("Erreur lors de la lecture du fichier %s\n", safeFiles[fileChoice - 1]);
        }
        free_structs(wordList);
    }
    return 0;
}
