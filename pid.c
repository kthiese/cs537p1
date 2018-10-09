//Alec Scheele
//Kathryn Thiese

#include <string.h>
#include <sys/types.h>
#include <ctype.h>
#include <dirent.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"

// Reads the proc directory
int readDirectory(){
	DIR *myDirectory;
	struct dirent *myFile;
	
	char *proc = "/proc/";
	
	// If a pid is passed in, just read that process file. 
	if (pid != NULL){
		readStatus(pid);
	} else {
		// If no pid is passed in, we need to print every process owned 
		// by the uid. So a while loop is used here to traverse 
		// through every process file, and pass it to readStatus, 
		// which checks whether the process uid matches the user's
		// uid. 
		myDirectory = opendir(proc);
		while ((myFile = readdir(myDirectory))){
			// Checks if the directory name starts with a digit.
			if (isdigit(myFile->d_name[0])){
				readStatus(myFile->d_name);
			}
		}
	}	
	return 0;


}
