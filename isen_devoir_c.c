#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROJECT_NAME "isen-devoir-c"
#define READ_LIMIT 200

struct Word {
    char* word;
    struct LineNumbers* line_numbers;
    int count;
    struct Word *next;
};

struct LineNumbers {
    int index;
    int count_per_lign;
    struct LineNumbers *next;
};


struct LineNumbers* createNewLineNumbers(int line_number){
    if(line_number <= 0){
        perror("ligne inferieure a 0.");
    }
    struct LineNumbers* new_line_numbers = (struct LineNumbers*)malloc(sizeof(struct LineNumbers));
    new_line_numbers -> index = line_number;
    new_line_numbers -> count_per_lign = 1;
    new_line_numbers -> next = NULL;
    return new_line_numbers;
}

struct Word* createWord(const char* word, int line_number){
    struct Word* new_word = (struct Word*)malloc(sizeof(struct Word));
    if (word == NULL ){
        printf("Pas de mot en variable.");
    }
    new_word -> word = strdup(word);
    new_word -> count = 1;
    new_word -> next = NULL;

    if (line_number == 0) {
        printf("Nombre nul trouvé.");
    }

    new_word -> line_numbers = createNewLineNumbers(line_number);

    return new_word;
}

int checkifWordExist(struct Word* wordList, const char* word){
    struct Word *current = wordList;
    while (current != NULL){
        if(strcmp(word,current -> word) == 0){
            printf("Le mot existe deja");
            return 1;
        }
        current = current -> next;
    } 
    return 0;
}

int checkifLignExist(struct LineNumbers* list_line, int line_number){
    struct LineNumbers *current = list_line;
    while(current != NULL) {
        if(current -> index == line_number){
            printf("Ce mot est deja present sur la ligne \n");
            return 1;
        }
        current = current -> next;
    }
    return 0;
}


void addWord(struct Word** wordList, const char* word, int line_number) {
    struct Word* current = *wordList;

    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            struct LineNumbers* line = current->line_numbers;
            while (line != NULL) {
                if (line->index == line_number) {
                    line->count_per_lign++;
                    current->count++;
                    return;
                }
                line = line->next;
            }

            struct LineNumbers* new_line = createNewLineNumbers(line_number);
            new_line->next = current->line_numbers;
            current->line_numbers = new_line;
            current->count++;
            return;
        }
        current = current->next;
    }

    struct Word* new_word = createWord(word, line_number);
    new_word->next = *wordList;
    *wordList = new_word;
}

void searchWord(struct Word* wordList, const char* word){
    while(wordList != NULL){
        if(strcmp(wordList->word,word) == 0){
            printf("Mot trouve dans le fichier : %s\n",wordList->word);
            printf("Occurence %d\n",wordList->count);
            printf("Lignes : \n");
            struct LineNumbers* current_line = wordList->line_numbers;
            while (current_line != NULL) {
                printf("L%d (%d fois) ", current_line->index, current_line -> count_per_lign);
                current_line = current_line->next;
            }
            return;
        }
        wordList = wordList -> next;
    }
    printf("Mot non trouve %s",word);
}


int readFile(char* fileName, struct Word** wordList) {
    FILE *file;
    char* state;
    char* token;
    char stored_file[READ_LIMIT];
    file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Erreur à l'ouverture du fichier");
        return 1;
    }
    int line_number = 1;
    printf("Ouverture du fichier...\n");
    while (fgets(stored_file, READ_LIMIT, file) != NULL) {
        //printf("Ligne lue : %d %s \n", line_number, stored_file);
        token = strtok_r(stored_file," ", &state);
        while (token != NULL) {
            //printf("%s\n", token);
            token[strcspn(token, "\n")] = 0;
            addWord(wordList, token, line_number);
            token = strtok_r(NULL," ", &state);
        }
        line_number++;
    }

    fclose(file);
    return 0;
}


void printWords(struct Word* wordList) {
    while (wordList != NULL) {
        printf("Mot : %s\n", wordList->word);
        printf("Occurence : %d\n", wordList->count);
        printf("Lignes : ");
        struct LineNumbers* current_line = wordList->line_numbers;
        while (current_line != NULL) {
            printf("L%d (%d fois) ", current_line->index, current_line -> count_per_lign);
            current_line = current_line->next;
        }
        printf("\n");

        wordList = wordList->next;
    }
}


void freeStructs(struct Word* wordList){
    while(wordList != NULL){
        struct LineNumbers* current_line = wordList->line_numbers;
        while(current_line != NULL){
            struct LineNumbers* temp_line = current_line;
            current_line = current_line->next;
            free(temp_line);
        }
        struct Word* temp_word = wordList;
        wordList = wordList->next;
        free(temp_word->word);
        free(temp_word);
    }
}

void lower_string_file


int main(int argc, char const *argv[])
{
    struct Word* wordList = NULL;
    readFile("test.txt",&wordList);
    printWords(wordList);
    searchWord(wordList,"Bonjour");
    freeStructs(wordList);
    return 0;
}
