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

int main() {
    char test[]={
            "eyo\nschlecht\ntest\naaaa\nwie\n"
    };

    createFilteredString(test,2,4);

    //rintf("Hello, World!\n");
    return 0;
}