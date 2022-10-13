#include "process_creation.h"
#include "string_manip.h"
#include <stdio.h>
#include <string.h>

#define TRUE 1

int main(){
 //   while(TRUE){
        char buf[4096] = "echo hello world > test1.txt";
      //fgets(buf, sizeof(buf), stdin);
        fork_process(buf);
   // }
}
