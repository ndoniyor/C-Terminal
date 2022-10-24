CC = gcc
CFLAGS = -g -Wall
default: final

final: string_manip.o operators.o process_creation.o main.o
	$(CC) $(CFLAGS) -o output string_manip.o operators.o process_creation.o main.o
	$(RM) *.o

string_manip.o:
	$(CC) $(CFLAGS) -c string_manip.c
operators.o:
	$(CC) $(CFLAGS) -c operators.c
process_creation.o:
	$(CC) $(CFLAGS) -c process_creation.c

main.o:
	$(CC) $(CFLAGS) -c main.c

clean:
	$(RM) output *.o 
