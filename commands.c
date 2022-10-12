#include <stdio.h>

void echo_command(int output_redirect_flag, char* text){
    if(output_redirect_flag=1){
        output_redirect();
    }
    else printf("%s",text);
}

void man_command(int pipe_flag, char* man_page){
    //compare string to man page name, have txt files and output those
    if(strcmp(man_page, "echo")==0){

    }
    else if(strcmp(man_page,"grep")==0){

    }
    else if(strcmp(man_page,"cat")==0){
        
    }
    else if(strcmp(man_page,"man")==0){
        
    }
    else if(strcmp(man_page,"cd")==0){
        
    }
}

void cat(int input_redirection_flag, char* file){
    int fd = open("file");

    if(input_redirection_flag==0){
        
    }
}