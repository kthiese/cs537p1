#Alec Scheele
#Kathryn Thiese 

CC=gcc
CFLAGS=-Wall -Wextra

rm: 537ps
	rm -f *.o

537ps: cmdLnParser.o pid.o readFiles.o
	$(CC) $(CFLAGS) *.o -o 537ps

pid.o: pid.c
	$(CC) -c pid.c

cmdLnParser.o: cmdLnParser.c
	$(CC) -c cmdLnParser.c

readFiles.o: readFiles.c
	$(CC) -c readFiles.c


