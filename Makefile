CC = gcc
CFLAGS = -g -Wall
default: final

final: main.o string_manip.o process_creation.o
	$(CC) $(CFLAGS) -o output main.o string_manip.o process_creation.o
	$(RM) *.o
	
main:
	$(CC) $(CFLAGS) -c main.c

string_manip.o:
	$(CC) $(CFLAGS) -c string_manip.c

process_creation.o:
	$(CC) $(CFLAGS) -c process_creation.c

clean:
	$(RM) output *.o