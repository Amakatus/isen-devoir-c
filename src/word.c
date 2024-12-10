#include "include/word.h"
#include "include/linenumbers.h"
#include "include/linkedlist.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <strings.h>

struct LinkedList* create_word(const char* word, int line_number,const char* fileName){
	struct Word* new_word = (struct Word*)malloc(sizeof(struct Word));
	if (word == NULL ){
		printf("Pas de mot en variable.");
	}
	new_word->word = strdup(word);
	new_word->count = 1;
	new_word->fileName = fileName;
	if (line_number == 0) {
		printf("Nombre nul trouve.");
	}

	new_word->line_numbers = create_new_linenumbers(line_number);
	struct LinkedList* new_ll = new_linked_list(new_word);
	return new_ll;
}

int check_if_word_exist(struct LinkedList* wordList, const char* word){
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


void add_word(struct LinkedList** wordList, const char* word, int line_number,const char* fileName) {
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
			struct LinkedList* new_line = create_new_linenumbers(line_number);
			new_line->next = current_word->line_numbers;
			current_word->line_numbers = new_line;
			current_word->count++;
			return;
		}

		current = current->next;
	}

	struct LinkedList* new_word = create_word(word, line_number,fileName);
	new_word->next = *wordList;
	*wordList = new_word;
}

void print_words(struct LinkedList* linkedList) {
	while (linkedList != NULL) {
		struct Word* wordList = (struct Word*) linkedList->data;
		printf("Mot : %s\n", wordList->word);
		printf("Occurrence : %d\n", wordList->count);
		printf("Lignes : ");
		struct LinkedList* line = wordList->line_numbers;
		while (line != NULL) {
			struct LineNumbers* current_line = (struct LineNumbers*) line->data;
			printf("L%d (%d fois) ", current_line->index, current_line->count_per_lign);
			printf("Fichier : %s",wordList->fileName);
			line = line->next;
		}
		printf("\n");
		linkedList = linkedList->next;
	}
}
