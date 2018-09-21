#include <sys/types.h>
#include <ctype.h>
#include <dirent.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Struct holding info for a process
struct Process{
	char * pid;
	char *state;
	int utime;
	int stime;
	int memory;
	char *cmdline;
};

// Struct used for a linked list of processes.
struct linklist {
	struct Process *p;
	struct linklist *next;
};


char *pid = NULL;
int uid = 0;
int s = 0;
int U = 1;
int S = 0;
int v = 0;
int c = 1;

int main (int argc, char *argv[]){
	uid = getuid();	
	int opt = 0;
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


	printf("%s %d %d %d %d %d %d", pid, uid, s, U, S, v, c);
	
	getProcesses();

	return 0;
}

int getProcesses(){
	readDirectory();

	printf("%s: ", pid);
	if (s == 1){
//		printf("%s ", state);
	}
	if (U == 1) {
//		printf("utime=%d ",p1->utime);
	}
	if (S == 1) {
//		printf("stime=%d ", p1->stime);
	}
	if (v == 1) {
//		printf("vmemory=%d ", p1->memory);
	}
	if (c == 1) {
//		printf("[%s]", *p1->cmdline);
	}

	return 0;

}

int readDirectory(){
	DIR *dir;
	struct dirent *dp;
	char *filename;
	dir=opendir("/proc/");
	// Declare linked list that holds the processes
	struct linklist head;
	while ((dp=readdir(dir)) != NULL){
		// Do the following if there was a p flag
		if (pid != NULL){
			// This only takes the files in the directory that are numbers.
			if (isdigit(dp->d_name[0])){
				if (strcmp(dp->d_name, pid) == 0){
					struct Process p1 = {NULL, NULL, 0, 0, 0, NULL};
					p1.pid = dp->d_name;
					head.p = p1;
				}
			}	
		} else {
			if (isdigit(dp->d_name[0])){

			}
		}



		
	}	
	return 0;
}
