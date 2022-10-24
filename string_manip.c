#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string_manip.h"

void print_args(int size, char** args){                                 //prints array of strings for debugging purposes
    int i;
    for(i=0;i<size;i++){
        printf("args[%d]=%s\n",i,args[i]);
    }
}
char** split(int* number_of_elements, char* string){                    //Function to split string by 'space' delimiter into array of strings
                                                                        //ex: "echo hello" -> {"echo", "hello"}
    int size_of_token, i = 1;
    int size_of_initial_array = strlen(string);                         //size of array before split
    char pre_split[size_of_initial_array]; 

    while(string[i++]!=NULL){                                           //count number of spaces. This corresponds to how many tokens since
                                                                        //tokens = number of spaces + 1
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
    post_split[i] = NULL;                                               //end string with NULL
    return post_split;                                                  
}

int check_for_operator(int size, char** args){                          //checks for <, >, |, &, or cd in args
    int i;
    if(strcmp(args[0],"cd") == 0)                                       //initially use strcmp to check for "cd"
        return 5;
    for(i = 0; i<size;i++){
        if(strchr(args[i],'>'))                                         //then use strchr to see if operator is present in string
            return 1;
        if(strchr(args[i],'<'))
            return 2;
        if(strchr(args[i],'|'))
            return 3;
        if(strchr(args[i],'&'))
            return 4;
    }
    return 0;
}

void strip_operators(int* size, char** args, int char_to_strip){        //once operator has been recognized and is being handled, the operator
    *size-=char_to_strip;                                               //and its args are no longer needed so this strips them so the base arg
    args = realloc(args,(*size) * sizeof(char *));                      //can be passed into execvp
    args[*size]=NULL;
}
