#include "filters.h"
#include "linkedlist.h"
#include "search.h"
#include "word.h"
#include "linenumbers.h"
#include <stdio.h>

/**
 * @brief Fonction d'affichage de la recherche , qui affiche le mot ses occurences et le nombre de ligne où il apparait.
 * 
 * @param linkedList 
 */
void print_search_match(struct Word* wordList) {
    if (wordList == NULL || wordList->word == NULL || wordList->fileName == NULL) {
        printf("Erreur : mot non trouvé ou invalid.\n");
        return;
    }

    printf("Mot trouvé : %s \n", wordList->word ? wordList->word : "NULL");
    printf("Dans le fichier : %s\n", wordList->fileName ? wordList->fileName : "NULL");
    printf("Occurence %d\n", wordList->count);
    printf("Lignes : \n");

    struct LinkedList* lines = wordList->lineNumbers;
    while (lines != NULL) {
        struct LineNumbers* currentLine = (struct LineNumbers*) lines->data;
        if (currentLine) {
            printf("L%d (%d fois)\n", currentLine->index, currentLine->countPerLign);
        }
        lines = lines->next;
    }
}

/**
 * @brief Effectue une recherche exacte pour un mot donné dans une liste chaînée de mots
 * 
 * @param wordList 
 * @param word 
 */
void search_exact_word(struct LinkedList* wordList, char* word) {
    struct Word* result = (struct Word*)linked_list_search(wordList, exact_match, (void *)word);
    if (result != NULL) {
        print_search_match(result);
    } else {
        printf("Mot non trouvé: %s\n", word);
    }
}


/**
 * @brief Effectue une recherche insensible à la casse pour un mot donné dans une liste chaînée de mots.
 * 
 * @param wordList 
 * @param word 
 */
void search_case_insensitive(struct LinkedList* wordList, char* word){
    struct Word* result = (struct Word*)linked_list_search(wordList, case_insensitive_match,(void*) word);
    if (result != NULL){
        print_search_match(result);
    } else {
        printf("Mot non trouve: %s\n", word);
    }
}

/**
 * @brief Effectue une recherche à l'aide de la wildcard *, ne marche pas encore très bien. Surtout pour le cas où la wildcard est à la fin.
 * 
 * @param wordList 
 * @param word 
 */
void search_wildcard(struct LinkedList* wordList, char* word) {
    struct LinkedList* results = NULL;
    struct LinkedList* currentNode = wordList;
    while (currentNode != NULL) {
        struct Word* wordItem = (struct Word*) currentNode->data;
        if (wildcard_match(wordItem, word)) {
            struct LinkedList* newNode = new_linked_list(wordItem);
            if (results == NULL) {
                results = newNode;
            } else {
                struct LinkedList* temp = results;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
        }
        currentNode = currentNode->next;
    }

    if (results != NULL) {
        struct LinkedList* resultNode = results;
        while (resultNode != NULL) {
            struct Word* wordResult = (struct Word*) resultNode->data;
            print_search_match(wordResult);
            resultNode = resultNode->next;
        }
    } else {
        printf("Aucun mot trouvé pour le mot: %s\n", word);
    }
}







