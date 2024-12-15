#include "filters.h"
#include "linkedlist.h"
#include "search.h"
#include "word.h"
#include "linenumbers.h"
#include <stdio.h>

/**
 * @brief 
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
 * @brief 
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

void search_case_insensitive(struct LinkedList* wordList, char* word){
    struct Word* result = (struct Word*)linked_list_search(wordList, case_insensitive_match,(void*) word);
    if (result != NULL){
        print_search_match(result);
    } else {
        printf("Mot non trouve: %s\n", word);
    }
}


void search_wildcard(struct LinkedList* wordList, char* word) {
    struct LinkedList* results = NULL;
    struct LinkedList* currentNode = wordList;
    
    // Parcours de la liste des mots
    while (currentNode != NULL) {
        struct Word* wordItem = (struct Word*) currentNode->data;  // Récupération du mot
        if (wildcard_match(wordItem, word)) {
            struct LinkedList* newNode = new_linked_list(wordItem);  // Création d'un nouveau noeud
            if (results == NULL) {
                results = newNode;  // Si c'est le premier résultat, on l'ajoute comme tête de liste
            } else {
                struct LinkedList* temp = results;
                while (temp->next != NULL) {
                    temp = temp->next;  // Recherche de la fin de la liste
                }
                temp->next = newNode;  // Ajout du nouveau noeud à la fin
            }
        }
        currentNode = currentNode->next;  // Passage au noeud suivant
    }

    if (results != NULL) {
        struct LinkedList* resultNode = results;
        
        // Parcours de la liste des résultats pour imprimer les correspondances
        while (resultNode != NULL) {
            struct Word* wordResult = (struct Word*) resultNode->data;  // Cast vers Word*
            print_search_match(wordResult);  // Affichage du résultat
            resultNode = resultNode->next;
        }
    } else {
        printf("Aucun mot trouvé pour le mot: %s\n", word);  // Si aucun résultat trouvé
    }
}







