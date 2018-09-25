#include <sys/types.h>
#include <ctype.h>
#include <dirent.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "header.h"


char *pid = NULL;
char *uid = NULL;
int s = 0;
int U = 1;
int S = 0;
int v = 0;
int c = 1;

int main (int argc, char *argv[]){
	uid = (char *)malloc(sizeof(unsigned int)*8 + 1);
	sprintf(uid, "%u", getuid());	
	int opt = 0;
	// Parses the command line and does the appropriate action
	while ((opt = getopt (argc, argv, "p:s::U::S::v::c::")) != -1) {
		switch (opt)
		{
			case 'p':
	        	 if (!isdigit(optarg[0])) {
				printf("PID must be numeric.\n");
				return 0;
			 }
			 pid = optarg;
  			 break;
	      		case 's':
	        	 if (optarg != NULL && *optarg == '-'){
				 break;
			 }else if (optarg != NULL && *optarg != '-') {
				 printf("ERROR: 's' flag has no arguments. Only '-s-' , but it has no effect.\n");
				 return 0;	 
			 }else{ 
			 	s = 1;
	        	 	break;
			 }
	     	        case 'U':
	        	 if (optarg != NULL && *optarg == '-'){
				 U = 0;
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
			 	S = 1;
	        	 	break;
			 }
	     	 	case 'v':
			 if (optarg != NULL && *optarg == '-') {
				 break;
			 } else if (optarg != NULL && *optarg != '-') {
				  printf("ERROR: 'v' flag has no arguments. Only '-v-' , but it has no effect.\n");
				 return 0;
			 }else {
			 	v = 1;
			 	break;
			 }
	      		case 'c':
			 if (optarg != NULL && *optarg == '-'){
				 c = 0;
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

	readDirectory();

	return 0;
}

