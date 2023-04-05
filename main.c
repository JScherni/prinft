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
    int i = 0;
    FILE *fp = fopen("test.txt", "r");

    while(/*temp[0]!=':'&&temp[1]!='q' && temp[0]!=EOF*/i++<12){
        printf("Enter a string: \n");
        fgets(temp,128,fp);

        if(temp[strlen(temp)+1]==EOF || (temp[0]==':' && temp[1]=='q') || temp==NULL || temp[0]=='\0'){
            break;
        }


        if((strlen(input)+strlen(temp)+1)>512)
        {
            inputSize+=512;
            input = realloc(input, inputSize* sizeof(char));
        }

        strcat(input,temp);
        //strcat(input,"\n");
    }
    free(temp);

    fclose(fp);
    return input;
}

void printHelp(){
    printf("Usage: ./fprintf [OPTION]... [FILE]...\n");
    printf("Write to standard output according to a format.\n");
}

int main() {
    char test[]={
            "eyo\nschlecht\ntest\naaaa\nwie\n"
    };

    // a b c \0 EOF

    //char* input = createInputStringFromFile("test.txt");
    char *input = createInputStringFromConsole();
    printf("Input: \n%s\n",input);
    createFilteredString(input,2,3);

    destroyString(input);
    return 0;
}