#Alec Scheele
#Kathryn Thiese 

CC=gcc
CFLAGS=-Wall -Wextra
SCAN_BUILD_DIR = scan-build-out

537ps: cmdLnParser.o pid.o readFiles.o
	$(CC) $(CFLAGS) *.o -o 537ps

pid.o: pid.c
	$(CC) $(CFLAGS) -c pid.c

cmdLnParser.o: cmdLnParser.c
	$(CC) $(CLAGFS) -c cmdLnParser.c

readFiles.o: readFiles.c
	$(CC) $(CFLAGS) -c readFiles.c

clean: 
	rm -f 537ps *.o
	rm -rf $(SCAN_BUILD_DIR)

scan-build: clean
	scan-build -o $(SCAN_BUILD_DIR) make

scan-view: scan-build
	chrome -new-window $(SCAN_BUILD_DIR)/*/index.html
