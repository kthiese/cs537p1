#include <string.h>
#include <sys/types.h>
#include <ctype.h>
#include <dirent.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

int readDirectory(){
	DIR *myDirectory;
	struct dirent *myFile;
	
	char *proc = "/proc/";
	
	if (pid != NULL){
		printf("Reading files\n");
		readStatus(pid);
	} else {
		printf("about to open dir\n");
		myDirectory = opendir(proc);
		printf("opened dir\n");
		while (myFile = readdir(myDirectory)){
			if (isdigit(myFile->d_name[0])){
				printf("%s\n", myFile->d_name);
				readStatus(myFile->d_name);
			}
		}
	}	
	return 0;


}
