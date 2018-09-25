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
		readStatus(pid);
	} else {
		myDirectory = opendir(proc);
		while (myFile = readdir(myDirectory)){
			if (isdigit(myFile->d_name[0])){
				readStatus(myFile->d_name);
			}
		}
	}	
	return 0;


}
