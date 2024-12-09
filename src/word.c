#include "include/word.h"
#include "include/linenumbers.h"
#include "include/linkedlist.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <strings.h>

struct LinkedList* createWord(const char* word, int line_number){
	struct Word* new_word = (struct Word*)malloc(sizeof(struct Word));
	if (word == NULL ){
		printf("Pas de mot en variable.");
	}
	new_word->word = strdup(word);
	new_word->count = 1;

	if (line_number == 0) {
		printf("Nombre nul trouve.");
	}

	new_word->line_numbers = createNewLineNumbers(line_number);
	struct LinkedList* new_ll = newLinkedList(new_word);
	return new_ll;
}

int checkIfWordExist(struct LinkedList* wordList, const char* word){
	struct LinkedList* current = wordList;
	while (current != NULL){
		struct Word* current_word = (struct Word*) current->data;
		if(strcmp(word,current_word->word) == 0){
			printf("Le mot existe deja");
			return 1;
		}
		current = current->next;
	}
	return 0;
}


void addWord(struct LinkedList** wordList, const char* word, int line_number) {
	struct LinkedList* current = *wordList;
	while (current != NULL) {
		struct Word* current_word = (struct Word*)current->data;

		if (strcmp(current_word->word, word) == 0) {
			struct LinkedList* line = current_word->line_numbers;
			while (line != NULL) {
				struct LineNumbers* line_numbers = (struct LineNumbers*)line->data;
				if (line_numbers->index == line_number) {
					line_numbers->count_per_lign++;
					current_word->count++;
					return;
				}
				line = line->next;
			}
			struct LinkedList* new_line = createNewLineNumbers(line_number);
			new_line->next = current_word->line_numbers;
			current_word->line_numbers = new_line;
			current_word->count++;
			return;
		}

		current = current->next;
	}

	struct LinkedList* new_word = createWord(word, line_number);
	new_word->next = *wordList;
	*wordList = new_word;
}

void searchWord(struct LinkedList* linkedList, const char* word, int casesensitive) {
    while (linkedList != NULL) {
        struct Word* wordList = (struct Word*) linkedList->data;
        if ((casesensitive == 0 && strcasecmp(wordList->word, word) == 0) || 
            (casesensitive == 1 && strcmp(wordList->word, word) == 0)) {
            printf("Mot trouve dans le fichier : %s\n", wordList->word);
            printf("Occurence %d\n", wordList->count);
            printf("Lignes : \n");
            struct LinkedList* line = wordList->line_numbers;
            while (line != NULL) {
                struct LineNumbers* current_line = (struct LineNumbers*) line->data;
                printf("L%d (%d fois)\n", current_line->index, current_line->count_per_lign);
                line = line->next;
            }
            return;
        }
        linkedList = linkedList->next;
    }
    printf("Mot non trouve: %s\n", word);
}

void printWords(struct LinkedList* linkedList) {
	while (linkedList != NULL) {
		struct Word* wordList = (struct Word*) linkedList->data;
		printf("Mot : %s\n", wordList->word);
		printf("Occurrence : %d\n", wordList->count);
		printf("Lignes : ");
		struct LinkedList* line = wordList->line_numbers;
		while (line != NULL) {
			struct LineNumbers* current_line = (struct LineNumbers*) line->data;
			printf("L%d (%d fois) ", current_line->index, current_line->count_per_lign);
			line = line->next;
		}
		printf("\n");
		linkedList = linkedList->next;
	}
}
