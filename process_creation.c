#include <unistd.h>
#include <stdio.h>
#include "string_manip.h"
#include "process_creation.h"

void fork_process(char* command){
    pid_t fpid; 
    char** split_string = split(command);
    int count = 0;
    char* status;
    fpid = fork();
    
    if(fpid<0){
        printf("Error in forking process");
    }
    else if(fpid==0){
        printf("Child process | ID: %d\n", getpid());
        execvp(split_string[0],split_string);
    }
    else{
        printf("Parent process | ID: %d",getpid());
        waitpid(-1, &status, 0);
    }
    printf("Count: %d",count);
    return;
}