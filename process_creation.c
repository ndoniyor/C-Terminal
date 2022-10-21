#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include "string_manip.h"
#include "process_creation.h"

#define TRUE 1
#define STDOUT_STREAM 1

void fork_process(char* command){
    pid_t fpid; 
    int arg_count=1;
    char** args = split(&arg_count,command);
    int count = 0,fd;
    char* status;
    char* filepath;
    fpid = fork();
    
    if(fpid<0){
        printf("Error in forking process");
    }
    else if(fpid==0){
        printf("Child process | ID: %d\n\n", getpid());

        if(check_for_redirect(arg_count, args)==TRUE){
            printf("Redirection found, appending working directory...\n");
            filepath = append_working_directory(args[arg_count-1]);

            printf("Redirect found, path: %s\n", filepath);
            fd = open(filepath, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

            printf("Removing redirection...\n");
            strip_operators(&arg_count, args);
            dup2(fd, STDOUT_STREAM);
        }
        if(execvp(args[0],args)==-1)
            printf("error: %d\n",errno);
    }
    else{
        printf("Parent process | ID: %d\n\n",getpid());
        waitpid(-1, &status, 0);
    }
    return;
}
