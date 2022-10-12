#include "process_creation.h"
#include "string_manip.h"
#include <stdio.h>
#include <string.h>

#define TRUE 1

int main(){
    //while(TRUE){
        char* command;
        getline(stdin, command);
        fork_process(command);
    //}
}