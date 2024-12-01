#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PROJECT_NAME "isen-devoir-c"
#define READ_LIMIT 200

struct Word {
    char* word;
    struct LineNumbers* line_numbers;
    int count; // occurence de mots
    struct Word *next;
};

struct LineNumbers {
    int index;
    struct LineNumbers *next;
};


struct LineNumbers* createNewLineNumbers(int line_number){
    if(line_number <= 0){
        perror("ligne inferieure a 0.");
    }
    struct LineNumbers* new_line_numbers = (struct LineNumbers*)malloc(sizeof(struct LineNumbers));
    new_line_numbers -> index = line_number;
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
    printf("Nouveau mot trouve");
    return 0;
}

int checkifLignExist(struct LineNumbers* list_line, int line_number){
    struct LineNumbers *current = list_line;
    while(current != NULL) {
        if(current -> index == line_number){
            printf("La ligne existe deja");
            return 1;
        }
        current = current -> next;
    }
    printf("Nouveau mot trouve");
    return 0;
}


void addWord(struct Word* wordList, const char* word, int line_number){
    struct Word* current = wordList;
    
     while (current != NULL) {
        if (strcmp(word, current->word) == 0) {
            if (!checkifLignExist(current->line_numbers, line_number)) {
                struct LineNumbers* new_line = createNewLineNumbers(line_number);
                new_line->next = current->line_numbers;
                current->line_numbers = new_line;
                current->count++;
            } else {
                printf("Ligne deja existante");
            }
        }
        current = current -> next;
     }

    struct Word* new_word = createWord(word, line_number);
    new_word->next = wordList;
    wordList = new_word;
}

int readFile(char* fileName,struct Word* wordList){
    FILE *file;
    char* state;
    char* token;
    char stored_file[READ_LIMIT];
    file = fopen(fileName,"r");
    if (file == NULL){
        printf("Erreur à l'ouverture du fichier");
        return 1;
    }
    int line_number = 1;
    printf("Ouverture du fichier...\n");
    while (fgets(stored_file, READ_LIMIT, file) != NULL) {
        printf("Ligne lue : %d %s \n",line_number,stored_file);
        token = strtok_r(stored_file, " ", &state);
        while (token != NULL) {
            addWord(wordList,token,line_number);
            token = strtok_r(NULL, " ", &state);
        }
        line_number++;
    }

    fclose(file);
    return 0;

}




void printWords(struct Word* wordList){
    while(wordList != NULL){
        printf("Mot %s, Occurence %d\n",wordList -> word, wordList->count);
        printf("Lignes : ");
        while(wordList -> line_numbers != NULL){
            printf("%d",wordList -> line_numbers ->index);
            wordList -> line_numbers = wordList -> line_numbers -> next;
        }
        printf("\n");
        wordList = wordList -> next;
    }
}


int main(int argc, char const *argv[])
{
    struct Word* wordList = NULL;
    readFile("test.txt",wordList);
    printWords(wordList);
    return 0;
}
