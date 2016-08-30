#include "Parser.h"



// if you are here then there is at least one
//argument splite ok!
void parse(char * inputCommand, int executionMode) {

  // printf("%s %d\n",inputCommand, executionMode);

    line = inputCommand;
    mode = executionMode;

    int i = 0;
    //replace inner tabs with spaces
    //to do split on spaces and every thing works!
    while(i < strlen(inputCommand)) {
        if(inputCommand[i] == '\t')
            inputCommand[i] = ' ';
        i++;
    }

    //splitttttttttttt
    argc = splitOnChar(line, ' ', splited);

    supstituteVariables();

    if(strcmp(splited[0], "cd") == 0) {
        cdCommandHandler();
    }
    else if(strcmp(splited[0], "history") == 0) {
        historyCommandHandler();
    }
    else {
        normalCommandHandler();
    }

}


void normalCommandHandler() {

    char commandPath[200];
    int kk = searchEnvirmentPath(splited[0], commandPath);
    //printf("this is the path:%s\n",commandPath);
    if(kk == -1) {
        // this might be asignment
        // handel asignment here
        otherPossibility();
    }
    else {

        int id = cloneThisProcess();

        if(id == 0) {// this is the child
            //handel error in command
            formatArg(commandPath);
            executeCommand(argv);
        }

        else {// parent process

           if(mode == foreground) {
                int status = 0;
                int x = -1;

                //this bug wasted some time be careful of it
                //if you realise it in the first palce!
                //the bug is : child process include forground and
                //back ground process , wait return on child process
                //termination wither it's forground or background
                //if it's a background process keep waiting
                while(x != id)
                    x = waitForChild(&status);
           }
        }

    }



}


void cdCommandHandler() {

    if(argc == 1) {//jus cd no path
        return;
    }
    else if(argc != 2) {//three argumenst , that's wrong
        printf("too many arguments");
        return;
    }
    else {

        //check if file exists
        if(fileExists(splited[1]) != 0) {
            printf("bash: cd: %s: No such file or directory\n",splited[0]);
        }
        else {//change current directory
            changeDirectory(splited[1]);
        }

    }



}




void otherPossibility() {

    if(argc !=1 ) {
        printf("%s: command not found\n",splited[0]);
    }
    else {

        char tmp[300][maxStringLength];
        int t = splitOnChar(line, '=', tmp);
        if(t != 2) {
            printf("%s: command not found\n",splited[0]);
        }
        else {
            setEnviromentVariable(tmp[0], tmp[1]);
        }
    }

}


void echoCommandHandler() {

    char commandPath[200];
    searchEnvirmentPath(splited[0], commandPath);


        int id = cloneThisProcess();

        if(id == 0) {// this is the child



            formatArg(commandPath);
            executeCommand(argv);

        }

        else {// parent process

            //normalCommandHandler() to understand this
           if(mode == foreground) {
                int status = 0;
                int x = -1;
                while(x != id)
                    x = waitForChild(&status);
           }
        }

}


void formatArg(char *commandPath) {

    strcpy(splited[0],commandPath);//put path in splited of zero
    int i = 0;
    while(i < argc) { // set pointers of argv
        argv[i] = splited[i];
        i++;
    }
    argv[argc] = NULL;//add the null at the end
}

void historyCommandHandler() {


    //reach the begining of history file
    fseek(historyFile, 0, SEEK_SET);
    char l[1000];

    //print the history
    int i = 0;
    while(fgets(l, 10000, historyFile) != NULL) {
        printf(" %d %s",i++,l);
    }

}




void supstituteVariables() {


    int i;
    char * value;
    char name[600];
    for(i = 0; i < argc; i++) {
        if(splited[i][0] == '$') {
            memcpy (name, splited[i]+1, strlen(splited[i]));
            value = getEnviromentVariable(name);
            if(value == NULL) {
                splited[i][0] = '\0';
            }
            if(value != NULL){
                memcpy (splited[i], value, strlen(value)+1);
            }

        }
    }


}





