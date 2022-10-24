#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "string_manip.h"
#include "operators.h"

void output_redirect(int arg_count, char** args){
    char* filepath = args[arg_count-1];                                     //output redirection path is final string of argument

    int fd = open(filepath, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR); //open file at specified path and assign a file descriptor to it.
                                                                            //the flags specify read/write, truncation, create if not there,
                                                                            //and outline permissions for user

    strip_operators(&arg_count, args, 2);                                   //gets rid of > operator since we are already handling redirectiomn
    
    dup2(fd, STDOUT_FILENO);                                                //redirects stdout to the file descriptor previously defined
    if(execvp(args[0],args)==-1)                                            //executes command
        perror("Error");
}
void input_redirect(int arg_count, char** args){                            
    char* filepath = args[arg_count-1];                                     //input redirection path is final string of argument

    int fd = open(filepath, O_RDONLY, S_IRUSR | S_IWUSR);                   //opens up file for read only, and defines permissions
    strip_operators(&arg_count, args, 2);                                   //gets rid of < operator since input redirection is being handled

    dup2(fd, STDIN_FILENO);                                                 //redirect stdin to file descriptor previously defined
    if(execvp(args[0],args)==-1)                                            //execute argument
        perror("Error");
}
void background_process(int arg_count, char** args){
    pid_t fpid, wpid;
    int status;
    strip_operators(&arg_count, args, 1);                                   //get rid of & operator
    fpid = fork();                                                          //fork new background process
    if(fpid==0){
        execvp(args[0], args);                                              //execute command
        perror("Program execution failed");
    }           
    wpid = waitpid(-1, &status, WNOHANG);                                   //dont need parent to wait for child to finish

}

void pipe_redirect(char **args){                                            
    int sz1 = 1, sz2 = 1;

    char* arg1full = malloc(9);                                             //need to reformulate arguments here to end up with 2 arrays of strings
                                                                            //one with the first writing pipe command ex: "man info"
    strcpy(arg1full,args[0]);                                               //these lines reformulate the args parameter to split up and concatenate
    strcat(arg1full, " ");
    strcat(arg1full, args[1]);

    char** arg1 = split(&sz1, arg1full);                                    //then it gets split up again to end up with one half of the command:
                                                                            // ex: {"man", "info"}

    char* arg2full = malloc(9);                                             //same thing here but with second reading pipe command "grep os"
    strcpy(arg2full,args[3]);
    strcat(arg2full, " ");
    strcat(arg2full, args[4]);

    char** arg2 = split(&sz2, arg2full);                                    //split to end up with {"grep", "os"}
    int fpipe[2];                                                           //create fpipe fd array
    if(pipe(fpipe) == -1) {                                                 //Create a pipe with I/O pointer
        perror("Pipe redirection failed");
        return;
    }

    if(fork() == 0){                                                        // Child 1 process      
        dup2(fpipe[1], STDOUT_FILENO);                                      // Redirect stdout to output of pipe     
        close(fpipe[0]);                                                    //close pipe read pointer
        close(fpipe[1]);                                                    //close pipe write pointer

        execvp(arg1[0], arg1);                                              //execute first command
        perror("First program execution failed");
        exit(1);
    }

    if(fork() == 0){                                                        // Child 2 process
        dup2(fpipe[0], STDIN_FILENO);                                       // Redirect stdin to input of pipe         
        close(fpipe[1]);                                                    //closing pipe write pointer
        close(fpipe[0]);                                                    //close pipe read pointer

        execvp(arg2[0], arg2);                                              //execute second command
        perror("Second program execution failed");
        exit(1);
    }

    close(fpipe[0]);                                                        //cleanup by closing pipes and waiting for children to finish
    close(fpipe[1]);
    wait(0); 
    wait(0);  
}