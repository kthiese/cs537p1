

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]){
	int pid = 0;
	int opt = 0;
	int s = 0;
	int U = 1;
	int S = 0;
	int v = 0;
	int c = 1;
	
	while ((opt = getopt (argc, argv, "p:sUSvc")) != -1) {
		switch (opt)
		{
			case 'p':
	        	 pid = atoi(optarg);;
  			 break;
	      		case 's':
	        	 s = 1;
	        	 break;
	     	        case 'U':
	        	 U = 0;
	        	 break;
	      		case 'S':
			 S = 1;
	        	 break;
	     	 	case 'v':
			 v = 1;
			 break;
	      		case 'c':
			 c = 0;
			 break;
	      }
	}

	if (p == 1){
			
	}

	printf("%i %d %d %d %d %d", pid, s, U, S, v, c);


	return 0;
}
