#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int decideLongShort(int ac, char *av[], char **input_file,
                    int *firstLine, int *lastLine, int *numberLines, int *help, int *version);

int process_args(int ac, char *av[], char **input_file,
                 int *firstLine, int *lastLine, int *numberLines);

int processLongArgs(int ac, char *av[], int *help, int *version);

int isInt(char *str);




int decideLongShort(int ac, char *av[], char **input_file,  // 1 bei erfolgreicher decodierung ; 0 -> Syntax error
                    int *firstLine, int *lastLine, int *numberLines,
                    int *help, int *version)
{
    if ((ac == 2) && (av[1][1] == '-')) //ist das zweite zeichen des ersten Strings ein '-' so handelt es sich um einen --Befehl
    {
        return processLongArgs(ac, av, help, version);
    }
    else
    {
        return process_args(ac, av, input_file, firstLine, lastLine, numberLines);
    }
}

int processLongArgs(int ac, char *av[], int *help, int *version)   // 1 bei erfolgreicher decodierung ; 0 -> Syntax error
{
    if (!strcmp(av[1], "--version"))
    {
        *version = 1;
        return 1;
    }
    else if (!strcmp(av[1], "--help"))
    {
        *help = 1;
        return 1;
    }
    return 0;
}

int isInt(char *str) // 1 bei ist Integer; 0 kein Integer
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!(str[i] >= 48 && str[i] <= 57))
        {
            return 0;
        }
    }
    return 1;
}

int process_args(int ac, char *av[], char **input_file, // 1 bei erfolgreicher decodierung ; 0 -> Syntax error
                 int *firstLine, int *lastLine, int *numberLines)
{
    int c = 0;

    *numberLines = 0;

    while (1)
    {

        // "f:"  means -f option has an arg  "n"  -n does not

        c = getopt(ac, av, "f:t:n");

        if (c == -1)
        {
            break; // nothing left to parse in the command line
        }

        switch (c)
        { // switch stmt can be used in place of some chaining if-else if

        case 'n': // Sollen Zeilen nummeriert werden: 1 -> ja ; 0 -> nein
            *numberLines = 1;
            break;

        case 'f': // bei dieser Zeile wird begonnen
            if (!isInt(optarg)) //Parameter ist kein Int
            {
                return 0;
            }

            *firstLine = atoi(optarg); // atoi converts a string to an int
            break;

        case 't': // letzte auszugebende Zeile
            if (!isInt(optarg)) //Parameter ist kein Int
            {
                return 0;
            }

            *lastLine = atoi(optarg); // atoi converts a string to an int
            break;

        case ':':
            //Error missing arg
            return 0;
            break;

        case '?':
            //Error unknown arg
            return 0;
            break;

        default:
            printf("optopt: %c\n", optopt);
        }
    }

    if (optind < (ac - 1)) // Syntax error Zu viele Argumente
    {
        return 0;
    }

    else if (optind == ac - 1) // der letzte Parameter ist das File
    {
        if(strcmp(av[optind], "-")) // wird als File nur '-' angegeben
        {
            *input_file = av[optind];
        }
    }

    return 1;
}

//automatische Ausgabe von ./printf.o: invalid option -- 'a' ?!?!?!
void printSyntaxError() 
{
    fprintf(stderr, "Syntax error\n"
                    "Try 'prnft --help' for more information\n");
    return;
}

void printVersion()
{
    fprintf(stdout, 
            "prnft (FHS extentions) 1.37\n"
            "Copyright (C) 2023 FHS\n"
            "License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.\n"
            "This is free software: you are free to change and redistribute it.\n"
            "There is NO WARRANTY, to the extent permitted by law.\n"
            "\n"
            "Written by Jonas Schernthaner and David Gahleitner.\n"
            "\n");
    return;
}

void printHelp()
{
    fprintf(stdout,
            "Usage: prnft [OPTION]... [FILE]... \n"
            "Concatenate FILES to standard output.\n"
            "\n"
            "With no FILE, or when FILE is -, read standard input.\n"
            "\n"
            "Parameter:\n"
            "  -f n       first line which will be displayed\n"
            "             if left blank start from beginning\n"
            "  -t m       last line which will be displayed\n"
            "             if left blank all lines till end will be displayed\n"
            "  -n         number all output lines\n"
            "  --help     display this help and exit\n"
            "  --version  output version information and exit\n"
            "\n"
            "Examples:\n"
            "  prnft -f 10 -t 15 test.txt\n"
            "    prints line 10 to 15 from file test.txt\n"
            "  cat test.txt | prntf -t 15 -n\n"
            "    data is read from stdin and printed from beginning to line 15\n"
            "    lines are printed with associated linenumber\n"
            "\n"
            "Full documentation <https://github.com/JScherni/prinft>\n"
            "\n");
    return;
}

void printUntilNewLine(char* print){
    int i = 0;
    while(print[i]!='\n'){
        printf("%c",print[i++]);
    }
    printf("\n");
}

char* createFilteredString(char* input, int beginOutput, int endOutput, int numberLines){
    char* temp = calloc(strlen(input), sizeof(char));
    //strcpy(temp,input);

    endOutput = 4;

    if(endOutput<0){
        endOutput = 5;
    }

    printf("create filtered string");

    for (int i = 1; i <= endOutput; i++) {
        if(beginOutput<=i){
            if(numberLines) {
                printf("%d: ", i);
            }
            printUntilNewLine(temp);
        }
        memset(temp,0,strlen(temp));
        temp=strchr(input,'\n');
        printf("temp %d: %s\n", i, temp);
        if(temp==NULL){
            break;
        }
        temp=&temp[1];
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
    //FILE *fp = fopen("test.txt", "r");

    while(1){
        memset(temp,0,128);
        //printf("Enter a string: \n");
        fgets(temp,128,stdin);

        if((temp[0]==':' && temp[1]=='q') || temp==NULL || temp[0]=='\0'){
            break;
        }


        if((strlen(input)+strlen(temp)+1)>512)
        {
            inputSize+=512;
            input = realloc(input, inputSize* sizeof(char));
        }

        strcat(input,temp);
    }
    //fclose(fp);
    free(temp);
    return input;
}

/*
void printHelp(){
    printf("Usage: ./fprintf [OPTION]... [FILE]...\n");
    printf("Write to standard output according to a format.\n");
}
*/

int main(int argc, char *argv[]) {

    int firstLine = 0;
    int lastLine = -1;
    int Zeilennummerierung = 0;
    char *filename = NULL;
    int version = 0;
    int help = 0;

    if(!decideLongShort(argc, argv, &filename, &firstLine, &lastLine, &Zeilennummerierung, &help, &version))
    {
        printSyntaxError();
        return 1;
    }

    if(version)
    {
        printVersion();
        return 0;
    }

    if(help)
    {
        printHelp();
        return 0;
    }


    printf("\n Arg values: -f %d -t %d ", firstLine, lastLine);
    if (Zeilennummerierung)
    {
        printf("-n ");
    }
    if (version)
    {
        printf("--version");
    }
    if (help)
    {
        printf("--help");
    }
    if (filename)
    {
        printf("%s\n", filename);
    }
    printf("\n");

    char *input = NULL;
    if(filename==NULL){
        input = createInputStringFromConsole();
    } else{
        input = createInputStringFromFile(filename);
    }

    if(input==NULL){
        fprintf(stderr, "Error opening file '%s'", filename);
        return 1;
    }

    createFilteredString(input,firstLine,lastLine,Zeilennummerierung);

    destroyString(input);
    return 0;
}