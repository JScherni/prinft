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
    int inputSize= 512;
    char* input = calloc(inputSize, sizeof(char));
    char* temp = calloc(128, sizeof(char));

    char c = 'y';

    while(temp[0]!=':'&&temp[1]!='q'){
        printf("Enter a string: \n");
        fgets(temp,128,stdin);
        if((strlen(input)+strlen(temp)+1)>512)
        {
            inputSize+=512;
            input = realloc(input, inputSize* sizeof(char));
        }

        strcat(input,temp);
        //strcat(input,"\n");
    }
    free(temp);
    return input;
}

int main() {
    char test[]={
            "eyo\nschlecht\ntest\naaaa\nwie\n"
    };

    //char* input = createInputStringFromFile("test.txt");
    char *input = createInputStringFromConsole();
    printf("Input: \n%s\n",input);
    createFilteredString(input,2,3);

    destroyString(input);
    return 0;
}