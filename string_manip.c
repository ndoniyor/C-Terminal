#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "string_manip.h"
char** split(char* string){                                             //C function to split string by 'space' delimiter
    int number_of_elements = 0, size_of_token, i = 1;
    int size_of_initial_array = strlen(string);                         //size of array before split
    char pre_split[size_of_initial_array]; 

    while(string[i++]!=NULL){
        if(string[i]==' ')
            number_of_elements++;
    }

    strcpy(pre_split, string);                                          //convert char* to string literal for strtok

    char** post_split = malloc(number_of_elements * sizeof(char *));    //allocate memory for post_split array of strings so it can be returned
    
    char* token = strtok(pre_split, " ");                               //define first token
    i=0;
    while(token!=NULL){                                                 //while not end of string 
        size_of_token = strlen(token);
        post_split[i] = malloc(size_of_token * sizeof(char));           //allocate memory for individual strings in post_split array based on size of token
        strcpy(post_split[i++],token);                                  //copy token to post_split
        token = strtok(NULL," ");                                       //get next token
    }
    return post_split;
}

/*void append_working_directory(char* file){
    if(file[0]!='.')
         return strcat("./", file);
    else 
        return file;
}*/