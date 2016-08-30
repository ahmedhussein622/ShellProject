#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "SystemCalls.h"
#include "Constants.h"


char *line;
char *argv[300];
char splited[300][maxStringLength];
int mode, argc;



//parse the input command and execute it
//the input command will be just program name
//end arguments , excution mode is pre deturment
//and is given in executionMode
//empty lines and comments are alos pre processed
//and wont come here, if you are here then you have
//a real command .
void parse(char * inputCommand, int executionMode);

 //normal commands that don't need special hanedlling
void normalCommandHandler();

//cd command
void cdCommandHandler();

//echo this function handels accessing
//environment varialbes
void echoCommandHandler();

//the history command
void historyCommandHandler();

//mainly creation of enviroment varialbe
void otherPossibility();


//do regular stuff to generate argv
//namely puts path in the first index of argv[]
//and putsh NULL in the index after the last
void formatArg(char *commandPath);

void supstituteVariables();


#endif // PARSER_H_INCLUDED
