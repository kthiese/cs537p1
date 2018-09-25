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
	printf("COMMAND PARSER\n");
	uid = (char *)malloc(sizeof(unsigned int)*8 + 1);
	sprintf(uid, "%u", getuid());	
	int opt = 0;
	printf("reading input\n");
	// Parses the command line and does the appropriate action
	while ((opt = getopt (argc, argv, "p:s::U::S::v::c::")) != -1) {
		switch (opt)
		{
			case 'p':
	        	 pid = optarg;
  			 break;
	      		case 's':
	        	 if (*optarg == '-'){
				 break;
			 }else{ 
			 	s = 1;
	        	 	break;
			 }
	     	        case 'U':
	        	 if (*optarg == '-'){
				 U = 0;
				 break;
			 } else {
			 	 break;
			 }
	      		case 'S':
			 if (*optarg == '-'){
				 break;
			 } else {
			 	S = 1;
	        	 	break;
			 }
	     	 	case 'v':
			 if (*optarg == '-') {
				 break;
			 } else {
			 	v = 1;
			 	break;
			 }
	      		case 'c':
			 if (*optarg == '-'){
				 c = 0;
			 } else {
			 	break;
			 }
			case '?':
			 printf("WRONG INPUT");
			 break;

	      }
	}


	printf("%s %s %d %d %d %d %d\n", pid, uid, s, U, S, v, c);
	
	readDirectory();

	return 0;
}

