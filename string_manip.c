#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string_manip.h"

void print_args(int size, char** args){
    printf("Printing...\n");
    int i;
    for(i=0;i<size;i++){
        printf("args[%d]=%s\n",i,args[i]);
    }
}
/*This function needs to be modified to allow for inputs with spaces like 'echo hello world' printing 'hello world'*/
char** split(int* number_of_elements, char* string){                                             //C function to split string by 'space' delimiter
    int size_of_token, i = 1;
    int size_of_initial_array = strlen(string);                         //size of array before split
    char pre_split[size_of_initial_array]; 

    while(string[i++]!=NULL){
        if(string[i]==' ')
            *number_of_elements+=1;
    }
    strcpy(pre_split, string);                                          //convert char* to string literal for strtok

    char** post_split = malloc(*number_of_elements * sizeof(char *)+1);    //allocate memory for post_split array of strings so it can be returned
    
    char* token = strtok(pre_split, " ");                               //define first token
    i=0;
    while(token!=NULL){                                                 //while not end of string 
        size_of_token = strlen(token);
        post_split[i] = malloc(size_of_token * sizeof(char));           //allocate memory for individual strings in post_split array based on size of token
        strcpy(post_split[i++],token);                                  //copy token to post_split
        token = strtok(NULL," ");                                       //get next token
    }
    post_split[i] = NULL;
    return post_split;
}

char* append_working_directory(char* file){
    char* directory = malloc(strlen(file)+2);
    strcpy(directory, "./");
    printf("Filename: %s, first char: %c\n",file,file[0]);
    if(file[0]!='.'){
        printf("Concatenating directory...\n");
        strcat(directory,file);
    }
    else{
        printf("comparison failed\n");
    }
    printf("dir: %s\n",directory);
    
    return directory;
}

int check_for_redirect(int size, char** args){
    int i;
    for(i = 0; i<size;i++){
        if(strchr(args[i],'>'))
            return 1;
    }
    return 0;
}

void strip_operators(int* size, char** args){
    int i;
    *size-=2;
    args = realloc(args,(*size) * sizeof(char *));
    args[*size]=NULL;
}
