#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


#include "Utility.h"
#include "SystemCalls.h"
#include "Constants.h"
#include "Parser.h"




int numberOfArguments;//number of arguments splited
int userMode; // interactive of batch
int executionMode; // forground or background
char splitedCommand[100][maxStringLength];// splite command !
char inputCommand[10000];// input command !

FILE *inputStream; // stdin or some file



//read line and set execution mode
//and decide wether it's empyt line of comment or
//execution
int readLine();
//set execution mode and open log file and set inputStream
void setUp(int argc, char * argv[]);
//close log file
void termination();

//call the parser or do nothing case comment line or
//empty line and print error of line is too long
int lineHandeling();

//call the parser to respond to command
void parseLine();
//print to log on process termination
void printToLogFile(int sigNumber);



int main(int argc, char * argv[]) {


    setUp(argc, argv);

    int t;
    do{
        printf("Shell>> ");
        t = lineHandeling();
    }while(t == 0);

    termination();

    return 0;
}


void termination() {

    fclose(historyFile);
    fclose(logFile);

}


//this funtion is so boring
//just many ifs
int readLine() {



    char *k = fgets(inputCommand, 10000, inputStream);

    int ans = 0;

    if(k == NULL) {//end of line = control+D
        printf("\n");
        ans = endShell;
    }
    else {

        int l = strlen(inputCommand);
        inputCommand[l-1] = '\0';//remove the \n at the end
        fprintf(historyFile, "%s\n", inputCommand);//print to history

        //in fileMode print scanned command to the console
        if(userMode == fileMode) {
            printf("%s\n", inputCommand);
        }

       // printf("before|%s|\n",inputCommand);
        trim(inputCommand);//remove white spaces at the begining and end
        //printf("trimed|%s|\n",inputCommand);

        l = strlen(inputCommand);

        if(l == 0) {
            ans = emptyLine;
        }
        else if(l > maxAllowedLength) {
            ans = TooLongCommand;
        }
        else {


           numberOfArguments = splitOnChar(inputCommand,' ',splitedCommand);
            if(numberOfArguments == 0) {
                ans = emptyLine;
            }
            else if(numberOfArguments == 1 && strcmp (splitedCommand[0],"exit") == 0) {
                ans = endShell;
            }
            else if(splitedCommand[0][0] == '#') {
                ans = commentLine;
            }
            else {

                executionMode = foreground;
                int ind = strlen(splitedCommand[numberOfArguments-1])-1;
                if(splitedCommand[numberOfArguments-1][ind] == '&') {

                    executionMode = background;
                    l = strlen(inputCommand);
                    inputCommand[l-1] = '\0';
                    trim(inputCommand);

                    numberOfArguments = splitOnChar(inputCommand,' ',splitedCommand);

                }

                ans = successfulRead;


            }
        }

    }

    return ans;
}



void setUp(int argc, char * argv[]) {

    if(argc > 2) {// too many arguments
        printf("too many arguments !\n");
        exit(1);
    }

    if(argc == 2) {


        // test file existence and accessabliy
        int x = fileAccessMode(argv[1], 0);
        if(x != 0) {
            printf("%s file doesn't exist\n",argv[1]);
            exit(1);
        }

        x = fileAccessMode(argv[1], 4);
        if(x != 0) {
            printf("%s need permission\n",argv[1]);
            exit(1);
        }


        inputStream = fopen(argv[1],"r");
        userMode = fileMode;

    }
    else {
        userMode = interactiveMode;
        inputStream = stdin;
    }


    signal(SIGCHLD, printToLogFile);

    char fileName[50];
    sprintf(fileName,"/home/%s/myShell/%s",getUserName(),"logFile.txt");
    logFile = fopen(fileName,"r+");
    sprintf(fileName,"/home/%s/myShell/%s",getUserName(),"history.txt");
    historyFile = fopen(fileName,"r+");

}


int lineHandeling() {

    int x = readLine();
   //printf("line read ok |%s| %d\n",inputCommand,x);
    int ans = 0;
    switch(x) {
        case endShell:
            ans = -1;
            break;
        case TooLongCommand:
            fprintf(stderr,"too long command\n");
            break;
        case emptyLine:
            break;
        case commentLine:
            break;
        case successfulRead:
            parseLine();
    }

    return ans;
}


void parseLine() {
    parse(inputCommand, executionMode);
}



void printToLogFile(int sigNumber) {
    fprintf(logFile,"Child process was terminated\n");
}







