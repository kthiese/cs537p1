// Kathryn Thiese
// Alec Scheele
// CS 537 Prog 1 Fall 2018

#include <sys/types.h>
#include <ctype.h>
#include <dirent.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "pid.h"

// The flags are stored as ints: 1 being true, 0 being false. 

// Parses the command line and runs the program. 
int main (int argc, char *argv[]){
	int** flags = malloc(sizeof(int*)*5);
	for (int i = 0; i < 5; i++){
		flags[i] = (int*)malloc(sizeof(int));
		if (i == 1){
			*flags[i] = 1;
		}
		if (i == 4) {
			*flags[i] = 1;
		}
	}	
	char** ids = (char**)malloc(sizeof(char*)*2);
	int uid_size = 8;
	char *pid = NULL;
	ids[1] = (char *)malloc(sizeof(unsigned int)*uid_size + 1);
	 
	sprintf(ids[1], "%u", getuid());	
	
	int opt = 0;
	// Parses the command line and does the appropriate action
	while ((opt = getopt (argc, argv, "p:s::U::S::v::c::")) != -1) {
		switch (opt)
		{
			case 'p':
			 // Checks if the argument passed in for the -p
			 // flag is a number. 
			 if (optarg != NULL){
				for (int i = 0; i < strlen(optarg); i++) {
	        	 		if (!isdigit(optarg[i])) {
						printf("PID must be numeric.\n");
						return 0;
					}
			 	}
			 }
			 ids[0] = (char *)malloc(strlen(optarg)+1);
			 ids[0] = optarg;
  			 break;
	      		case 's':
	        	 if (optarg != NULL && *optarg == '-'){
				 break;
			 }else if (optarg != NULL && optarg != "-") {
				 printf("ERROR: 's' flag has no arguments. Only '-s-' , but it has no effect.\n");
				 return 0;	 
			 }else{ 
			 	*flags[0] = 1;
	        	 	break;
			 }
	     	        case 'U':
	        	 if (optarg != NULL && *optarg == '-'){
				 *flags[1] = 0;
				 break;
			 } else if (optarg != NULL && *optarg != '-') {
				  printf("ERROR: 'U' flag has no arguments. Only '-U-': does not show utime when listing processes.\n");
				 return 0;
			 }else {
			 	 break;
			 }
	      		case 'S':
			 if (optarg != NULL && *optarg == '-'){
				 break;
			 } else if (optarg != NULL && *optarg != '-') {
				  printf("ERROR: 'S' flag has no arguments. Only '-S-' , but it has no effect.\n");
				 return 0;
			 }else {
			 	*flags[2] = 1;
	        	 	break;
			 }
	     	 	case 'v':
			 if (optarg != NULL && *optarg == '-') {
				 break;
			 } else if (optarg != NULL && *optarg != '-') {
				  printf("ERROR: 'v' flag has no arguments. Only '-v-' , but it has no effect.\n");
				 return 0;
			 }else {
			 	*flags[3] = 1;
			 	break;
			 }
	      		case 'c':
			 if (optarg != NULL && *optarg == '-'){
				 *flags[4] = 0;
				 break;
			 } else if (optarg != NULL && *optarg != '-') {
				  printf("ERROR: 'c' flag has no arguments. Only '-c-': does not show command when listing processes.\n");
				 return 0;
			 }else {
			 	break;
			 }
			case '?':
			 printf("ERROR: Ivalid flag. The following flags are accepted: s, U, S, v, c.\n");
			 return 0;
	      }
	}

	// Go onto reading the /proc/ directory
	readDirectory(flags, ids);

	return 0;
}

