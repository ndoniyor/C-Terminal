#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
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
    const char* filepath;
    fpid = fork();
    
    if(fpid<0){
        printf("Error in forking process");
    }
    else if(fpid==0){
        printf("Child process | ID: %d\n\n", getpid());
        printf("Checking for redirection...\n");
        if(check_for_redirect(arg_count, args)==TRUE){
            printf("Redirection found, appending working directory...\n");
            filepath = append_working_directory(args[arg_count-1]);
            printf("Redirect found, path: %s\n", filepath);
            fd = open(filepath, O_WRONLY | O_CREAT);
        }
        else
            printf("Redirect not found\n");
        dup2(STDOUT_STREAM, fd);
       // printf("hello");
        //if(execvp("echo","echo hello world")==-1)
        //    printf("%d",errno);
        printf("%d\n",execvp("echo","echo hello"));
    }
    else{
        printf("Parent process | ID: %d\n\n",getpid());
        waitpid(-1, &status, 0);
    }
    printf("Count: %d\n",count);
    return;
}

//int main(){
  //  fork_process("echo hello > test.txt");
//}
