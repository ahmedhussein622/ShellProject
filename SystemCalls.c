#include "SystemCalls.h"


//use execv to excute command with args in args[]
int executeCommand(char *args[]) {
    int ans = execv(args[0], args);

    if(ans == -1) {
        char *a = "";
        perror(a);
    }

    return ans;
}

//waits for a child process
int waitForChild(int *status) {
    return wait(status);
}


//creat new process
int cloneThisProcess() {
    return fork();
}

// return 0 if the file exist
//else return some other number
int fileExists(char * filePath) {
    return fileAccessMode(filePath, 0);
}


//test file accessability
int fileAccessMode(char * filePath, int m) {
     return access(filePath, m);
}


int searchEnvirmentPath(char*filePath, char *resultPath) {

    //be optimistic and think you have the full path
    if(fileExists(filePath) == 0) { // you are lucky
        memcpy(resultPath, filePath, strlen(filePath)+1);
        resultPath[strlen(filePath)] = '\0';
        return 0;
    }

    //bad luck search the eniroment variable


    //get paths
    char paths[100][maxStringLength];
    int t = splitOnChar(getEnviromentVariable("PATH"), ':', paths);


    int i = 0;

    while(i < t) {//go throw all paths

        strConcatenate(resultPath, paths[i], "/");
        strConcatenate(resultPath, resultPath, filePath);
        if(fileExists(resultPath) == 0) {// test file existence
            return 0;
        }
        i++;
    }


    return -1;

}

//chane current working directory
int changeDirectory(char * path) {
    return chdir(path);
}

// set the enviroment variable
int setEnviromentVariable(char *name, char *value) {
    return setenv(name, value, 1);
}

//get enviroment variable

char *getEnviromentVariable(char *name) {
    return getenv(name);
}



char *getUserName() {
    return getpwuid(getuid())->pw_name;
}






