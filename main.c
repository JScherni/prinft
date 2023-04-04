#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printUntilNewLine(char* print){
    int i = 0;
    while(print[i]!='\n'){
        printf("%c",print[i++]);
    }
    printf("\n");
}

char* createFilteredString(char* input, int beginOutput, int endOutput){
    char* temp = calloc(strlen(input), sizeof(char));
    strcpy(temp,input);
    for (int i = 1; i <= endOutput; i++) {
        if(beginOutput<=i)
        {
            printUntilNewLine(temp);
        }
        temp=&(strchr(temp,'\n')[1]);
    }
}

char* createInputStringFromFile(char* filename){
    FILE *fp = fopen(filename, "r");

    if (fp == NULL){
        //print error in error stream
        fprintf(stderr, "Error opening file '%s'", filename);
        return NULL;
    }

    fseek(fp, 0L, SEEK_END);
    int size = ftell(fp);
    rewind(fp);

    char* input = calloc(size, sizeof(char));
    fread(input, size, 1, fp);
    fclose(fp);

    return input;
}

char* destroyString(char* input){
    free(input);
    return NULL;
}

char* createInputStringFromConsole(){
    char* input = calloc(255, sizeof(char));

    fgets(input,100,stdin);
    return input;
}

int main() {
    char test[]={
            "eyo\nschlecht\ntest\naaaa\nwie\n"
    };

    char* input = createInputStringFromFile("test.txt");
    createFilteredString(input,2,4);

    destroyString(input);
    return 0;
}