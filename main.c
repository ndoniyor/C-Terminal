#include "process_creation.h"
#include "string_manip.h"
#include <stdio.h>
#include <string.h>

#define TRUE 1

int main(){
char* wd[1024];                             //holds working directory
    while(TRUE){
        if(getcwd(wd, sizeof(wd)) != NULL)  //assigns working directory to wd char*
            printf("\n[%s] $ ", wd);
        char buf[4096];                     //holds user input
        fgets(buf, sizeof(buf), stdin);     //assign user input to buf

        buf[strcspn(buf, "\n")] = 0;        //removes newline character from input
        fork_process(buf);                  //initiate fork for argu
    }
}
