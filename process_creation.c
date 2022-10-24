#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "string_manip.h"
#include "process_creation.h"
#include "operators.h"

#define OUTPUT_REDIRECT 1
#define INPUT_REDIRECT 2
#define PIPE_TRANSFER 3
#define BACKGROUND_PROCESS 4
#define STDOUT_STREAM 1
#define STDIN_STREAM 0
#define CHANGE_DIRECTORY 5

void fork_process(char* command){
    pid_t fpid;                                         //holds fpid of forked process
    int arg_count=1;                                    //holds number of arguments inputted in main.c
    char** args = split(&arg_count,command);            //splits argument to array of strings for easier processing
    if(strcmp(args[0],"exit")==0)                       //early handling of exit command to quit terminal
        exit(1);
    char* status;
    char* home = getenv("HOME");                        //gets home directory
    fpid = fork();                                      //fork process
    
    if(fpid<0)                                          //fork failed
        printf("Error in forking process");
    else if(fpid==0){
        switch(check_for_operator(arg_count, args)){    //switch case to check for <, >, |, &, or cd
            case CHANGE_DIRECTORY:
                if(args[1] == NULL)                     //if only "cd" is inputted without other args, chdir to home directory
                    chdir(home);    
                else
                    chdir(args[1]);                     //otherwise change dir to specfiied directory
                break;
            case OUTPUT_REDIRECT:
                output_redirect(arg_count,args);        //call output redirection function
                break;
            case INPUT_REDIRECT:
                input_redirect(arg_count,args);         //call input redirection function  
                break;
            case PIPE_TRANSFER:                         //call pipe redirection function
                pipe_redirect(args);
                break;
            case BACKGROUND_PROCESS:                    //call background process function
                background_process(arg_count, args);
                break;
            default:                                    //default case where no operators/cd are found
            if(execvp(args[0],args)==-1)                
                perror("Error");
            break;
        }
    }
    else
        waitpid(-1, &status, 0);                        //if parent, wait for child to finish
    return;
}
