#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define FILENAME "jokes.txt"
#define BUFFER_SIZE 4096

int getLineCount(FILE* fp);
char** buildStringArray(int line_count, FILE* fp);
int randomNumGen(int line_count);
void printLine(int random_num, char** strings);

int main(void) {
    FILE* fp = fopen(FILENAME, "r");

    if (!fp) {
        fprintf(stderr, "Error opening file '%s'\n", FILENAME);
        return EXIT_FAILURE;
    }

    int line_count = getLineCount(fp);
    
    rewind(fp);
    
    char** strings = buildStringArray(line_count, fp);
    int random_num = randomNumGen(line_count);
    
    printLine(random_num, strings);
    
    // free the memory
    for (int i = 0; i < line_count; i++)
        free(strings[i]);
    
    free(strings);
    fclose(fp);
    
    return EXIT_SUCCESS;
}

int getLineCount(FILE* fp) {
    char chr = getc(fp);                // get first char
    int lines = 1;

    while (chr != EOF) {
        if (chr == '\n') {
            ++lines;
        }
        
        chr = getc(fp);                 // get next char
    }
    
    return lines;
}

char** buildStringArray(int line_count, FILE* fp) {
    char** strings;
    char buffer[BUFFER_SIZE];           // temporary buffer
    int str_length = 0;

    strings = malloc(line_count * sizeof(char*));

    for (int i = 0; i < line_count; i++) {
        fgets(buffer, BUFFER_SIZE, fp);

        str_length = strlen(buffer);
        buffer[str_length - 1] = '\0';      // removes \n char from string
        strings[i] = malloc(str_length * sizeof(char));
        strcpy(strings[i], buffer);
    }

    return strings;
}

int randomNumGen(int line_count) {
    srand((unsigned int)time(NULL));
    int random_num = rand() % line_count;

    return random_num;
}

void printLine(int random_num, char** strings) {
    printf("%s", strings[random_num]);
}
