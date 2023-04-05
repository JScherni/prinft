#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int decideLongShort(int ac, char *av[], char **input_file,
                    int *ersteZeile, int *letzteZeile, int *Zeilennummer, int *hilfe, int *version);

int process_args(int ac, char *av[], char **input_file,
                 int *ersteZeile, int *letzteZeile, int *Zeilennummer);

int processLongArgs(int ac, char *av[], int *hilfe, int *version);

int isInt(char *str);




int decideLongShort(int ac, char *av[], char **input_file,  // 1 bei erfolgreicher decodierung ; 0 -> Syntax error
                    int *ersteZeile, int *letzteZeile, int *Zeilennummer,
                    int *hilfe, int *version)
{
    if ((ac == 2) && (av[1][1] == '-')) //ist das zweite zeichen des ersten Strings ein '-' so handelt es sich um einen --Befehl
    {
        return processLongArgs(ac, av, hilfe, version);
    }
    else
    {
        return process_args(ac, av, input_file, ersteZeile, letzteZeile, Zeilennummer);
    }
}

int processLongArgs(int ac, char *av[], int *hilfe, int *version)   // 1 bei erfolgreicher decodierung ; 0 -> Syntax error
{
    if (!strcmp(av[1], "--version"))
    {
        *version = 1;
        return 1;
    }
    else if (!strcmp(av[1], "--help"))
    {
        *hilfe = 1;
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
                 int *ersteZeile, int *letzteZeile, int *Zeilennummer)
{
    int c = 0;

    *Zeilennummer = 0;

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
            *Zeilennummer = 1;
            break;

        case 'f': // bei dieser Zeile wird begonnen
            if (!isInt(optarg))
            {
                //fprintf(stderr, "\n Parameter ist kein Int\n");
                return 0;
            }

            *ersteZeile = atoi(optarg); // atoi converts a string to an int
            break;

        case 't': // letzte auszugebende Zeile
            if (!isInt(optarg))
            {
                //fprintf(stderr, "\n Parameter ist kein Int\n");
                return 0;
            }

            *letzteZeile = atoi(optarg); // atoi converts a string to an int
            break;

        case ':':
            //fprintf(stderr, "\n Error -%c missing arg\n", optopt);
            // usage();
            return 0;
            break;
        case '?':
            //fprintf(stderr, "\n Error unknown arg -%c\n", optopt);
            // usage();
            return 0;
            break;
        default:
            printf("optopt: %c\n", optopt);
        }
    }

    if (optind < (ac - 1)) // Zu viele Argumente
    {
        //fprintf(stderr, "\n Syntax error zu viele Parameter\n");
        // usage();
        return 0;
    }
    else if (optind == ac - 1) // der letzte Parameter ist das File
    {
        *input_file = av[optind];
    }

    return 1;
}

void printUntilNewLine(char* print){
    int i = 0;
    while(print[i]!='\n' && print[i]!='\0'){
        printf("%c",print[i++]);
    }
    printf("\n");
}

void createFilteredString(char* input, int beginOutput, int endOutput, int numberLines){
    char* temp = calloc(strlen(input), sizeof(char));
    strcpy(temp,input);

    int wholeFile = endOutput<0 ? 1 : 0;
    
    printf("create filtered string: \n");

    for (int i = 1; (i <= endOutput) || wholeFile; i++) {
        if(beginOutput<=i){
            if(numberLines) {
                printf("%d: ", i);
            }
            printUntilNewLine(temp);
        }
        temp=strchr(temp,'\n')==NULL? NULL : &(strchr(temp,'\n')[1]);
        if(temp==NULL){
            break;
        }
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

void printHelp(){
    printf("Usage: ./fprintf [OPTION]... [FILE]...\n");
    printf("Write to standard output according to a format.\n");
}

int main(int argc, char *argv[]) {

    int ersteZeile = 0;
    int letzteZeile = -1;
    int Zeilennummerierung = 0;
    //char *filename = NULL;
    char filename[] = "test.txt";
    int version = 0;
    int hilfe = 0;

    // process_args(argc, argv, &filename, &ersteZeile, &letzteZeile, &Zeilennummerierung);

    if(!decideLongShort(argc, argv, &filename, &ersteZeile, &letzteZeile, &Zeilennummerierung, &hilfe, &version))
    {
        fprintf(stderr, "syntax error");
        return 1;
    }


    printf("\n Arg values: -f %d -t %d ", ersteZeile, letzteZeile);
    if (Zeilennummerierung)
    {
        printf("-n ");
    }
    if (version)
    {
        printf("--version");
    }
    if (hilfe)
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

    createFilteredString(input,ersteZeile,letzteZeile,Zeilennummerierung);

    destroyString(input);
    return 0;
}