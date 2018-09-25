CC=gcc
CFLAGS=-Wall -Wextra

rm: prog
	rm -f *.o

prog: cmdLnParser.o pid.o readFiles.o
	$(CC) $(CFLAGS) *.o -o prog

pid.o: pid.c
	$(CC) -c pid.c

cmdLnParser.o: cmdLnParser.c
	$(CC) -c cmdLnParser.c

readFiles.o: readFiles.c
	$(CC) -c readFiles.c


