# C-Terminal
Custom-made shell simulator written in C.

## To-do:
### Functions:
* [x] echo *(operational as is and with > operator, need testing with pipe once it's implemented)*
* [x] cat *(operational as is and with > operator, need testing with pipe once it's implemented)*
* [x] grep
* [x] man
* [ ] cd
### Function operators:
* [x] input redirection (<) 
* [x] output redirection (>) *operational with echo and cat, need testing with man and grep once implemented*
* [x] pipe (|)
* [ ] background exececution (&)
### Other:
* [x] When using output redirection truncate args string to not include operator and filename
        ex: echo hello world > test1.txt outputs hello world > test1.txt to test1.txt
## Running:
Run make
