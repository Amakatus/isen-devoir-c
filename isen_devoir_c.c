#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define PROJECT_NAME "isen-devoir-c"
#define READ_LIMIT 200

struct LinkedList{
    struct LinkedList *next;
    void* data;
};

struct Word {
    char* word;
    FILE file;
    struct LineNumbers* line_numbers;
    int count;
    struct Word *next;
};

struct LineNumbers {
    int index;
    int count_per_lign;
    struct LineNumbers *next;
};

//LinkedList generique

struct LinkedList* newLinkedList(void* data){
    struct LinkedList* new_ll = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    new_ll -> next = NULL;
    new_ll -> data = data;
    return new_ll; 
}

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

    if (line_number == 0) {
        printf("Nombre nul trouvé.");
    }

    new_word -> line_numbers = createNewLineNumbers(line_number);
    struct LinkedList* new_ll = newLinkedList(new_word);
    return new_ll;
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

void listExtFile(const char *argv[]){ // Pas tres utile , mieux vaut verifier par exemple les 50 premiers caracteres
    DIR *dir;
    struct dirent *dent;
    dir = opendir(argv[1]);
    if(dir != NULL){
        while((dent=readdir(dir)) != NULL){
            if((strcmp(dent->d_name,".")==0 || strcmp(dent->d_name,"..")==0 || (*dent->d_name) == '.' )){
            } else {
                if((strcmp(dent -> d_name + strlen(dent -> d_name) - 4,".txt")) == 0){
                    printf("ce fichier est un txt : %s \n", dent -> d_name);
                }
            }
        }
    }
    closedir(dir);
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



int main(int argc, char const *argv[])
{
    //struct Word* wordList = NULL;
    listTxtFile(argv);
    //readFile("./samples/test.txt",&wordList);
    //printWords(wordList);
    //searchWord(wordList,"Bonjour");
    //freeStructs(wordList);
    return 0;
}
