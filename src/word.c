#include "word.h"
#include "linenumbers.h"
#include "linkedlist.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <strings.h>

/**
 * @brief Create a word object
 * 
 * @param word 
 * @param lineNumber 
 * @param fileName 
 * @return struct LinkedList* 
 */
struct LinkedList* create_word(const char* word, int lineNumber,const char* fileName){
	struct Word* newWord = (struct Word*)malloc(sizeof(struct Word));
	if (word == NULL ){
		printf("Pas de mot en variable.");
	}
	newWord->word = strdup(word);
	newWord->count = 1;
	newWord->fileName = fileName;
	if (lineNumber == 0) {
		printf("Nombre nul trouve.");
	}

	newWord->lineNumbers = create_new_linenumbers(lineNumber);
	struct LinkedList* newLinkedList = new_linked_list(newWord);
	return newLinkedList;
}

/**
 * @brief 
 * 
 * @param wordList 
 * @param word 
 * @return int 
 */
int check_if_word_exist(struct LinkedList* wordList, const char* word){
	struct LinkedList* current = wordList;
	while (current != NULL){
		struct Word* currentWord = (struct Word*) current->data;
		if(strcmp(word,currentWord->word) == 0){
			printf("Le mot existe deja");
			return 1;
		}
		current = current->next;
	}
	return 0;
}

/**
 * @brief 
 * 
 * @param wordList 
 * @param word 
 * @param lineNumber 
 * @param fileName 
 */
void add_word(struct LinkedList** wordList, const char* word, int lineNumber,const char* fileName) {
	struct LinkedList* current = *wordList;
	while (current != NULL) {
		struct Word* currentWord = (struct Word*)current->data;

		if (strcmp(currentWord->word, word) == 0) {
			struct LinkedList* lines = currentWord->lineNumbers;
			while (lines != NULL) {
				struct LineNumbers* lineNumbers = (struct LineNumbers*)lines->data;
				if (lineNumbers->index == lineNumber) {
					lineNumbers->countPerLign++;
					currentWord->count++;
					return;
				}
				lines = lines->next;
			}
			struct LinkedList* newLine = create_new_linenumbers(lineNumber);
			newLine->next = currentWord->lineNumbers;
			currentWord->lineNumbers = newLine;
			currentWord->count++;
			return;
		}

		current = current->next;
	}

	struct LinkedList* newWord = create_word(word, lineNumber,fileName);
	newWord->next = *wordList;
	*wordList = newWord;
}

/**
 * @brief 
 * 
 * @param linkedList 
 */
void print_words(struct LinkedList* linkedList) {
	while (linkedList != NULL) {
		struct Word* wordList = (struct Word*) linkedList->data;
		printf("Mot : %s\n", wordList->word);
		printf("Occurrence : %d\n", wordList->count);
		printf("Lignes : ");
		struct LinkedList* lines = wordList->lineNumbers;
		while (lines != NULL) {
			struct LineNumbers* currentLine = (struct LineNumbers*) lines->data;
			printf("L%d (%d fois) ", currentLine->index, currentLine->countPerLign);
			printf("Fichier : %s",wordList->fileName);
			lines = lines->next;
		}
		printf("\n");
		linkedList = linkedList->next;
	}
}
