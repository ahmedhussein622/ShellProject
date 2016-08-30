#ifndef SYSTEMCALLS_H_INCLUDED
#define SYSTEMCALLS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pwd.h>

#include "Utility.h"

//the purpose of this file is not do use
//system calls directly , so any future change
//in the system call wont need much change

int executeCommand(char *args[]);//execute a command
int waitForChild(int *status);//waits for child process
int cloneThisProcess();// calls fork
int fileExists(char * filePath); // test if a file exists
int fileAccessMode(char * filePath, int m);// test the access mode to a file
int changeDirectory(char * path);//change the current path of the program
//set envirment varialbe name to value
int setEnviromentVariable(char *name, char *value);
//get the value stored in envirnment variable name
char *getEnviromentVariable(char *name);
//given a program name this function searches for
//filePath in currrent path and in enviroment variable path
//the result is put in resultPath
//return 0 on success , -1 on failer
int searchEnvirmentPath(char*filePath, char *resultPath);

char *getUserName();

#endif // SYSTEMCALLS_H_INCLUDED
