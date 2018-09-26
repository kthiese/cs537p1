#include <ctype.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "header.h"

// Max size of file buffer
int MAX_SIZE = 1000;
char * proc = "/proc/";
char * full_path; 

// Intitialized global varible "full_path" that holds the path to the pid directory
void fullPath(char *pid1){
	full_path = (char *)malloc(strlen(proc) + strlen(pid1) + 1);
	strcpy(full_path, proc);
	strcat(full_path, pid1);
}

// Parses stat file and prints info based on the flags.
int readStat(char *pid1)
{
	struct dirent *myFile;
	DIR *myDirectory = opendir(full_path);
		if(myDirectory)
		{
			while((myFile = readdir(myDirectory)))
			{
				if(strcmp(myFile->d_name, "stat") == 0)
				{
					// file pointer and buf to hold contents of file
					char *buf = (char *)malloc(sizeof(char)*1000 + 1);
					FILE *stat_file;

					// open file, create string with full path
					char *stat_path = (char *)malloc(strlen(full_path)+strlen("/stat") +1);
					strcpy(stat_path, full_path);
					strcat(stat_path, "/stat");
				
					
					stat_file = fopen(stat_path, "r");
				

					//return 1 if fails to open file
					if(!stat_file)
						return 1;
					
					//put first 1000 characters of file into buf
					while(fgets(buf, 1000, stat_file) != NULL)
					
					//close file
					fclose(stat_file);
					
					//split buf on each space
					//char * eof;
					//eof = strtok(buf, " ");
					//int counter = 0;

					//split buf on ") " character
					char *eof;
					eof = strtok(buf, ")");
					int counter = 1; 
					
					// Print the pid of the process
					printf("%s: ", pid1);
					
					while(eof != NULL && counter < 20)
					{
						
						// Print state of process if s flag is 1
						if(counter == 2)
						{
							if (s == 1)
								printf("%s ", eof);
						}

						// Print user time of process if U flag is 1
						if(counter == 13)
						{
							if (U == 1)
								printf("utime=%s ", eof);
						}

						// Print system time of process if S flag is 1
						if(counter == 14)
						{
							if (S == 1)
								printf("stime=%s ", eof);
						}

						eof = strtok(NULL, " ");
						counter++;
					}
					
					readStatm(pid1);
					return 0;
				}
			}
		
		} else {
			printf("Process %s not found.\n", pid1);
			return 1;
		}
		
}


int readStatm(char *pid1)
{
	if (v == 1) {
		struct dirent *myFile;
		DIR *myDirectory = opendir(full_path);
			if(myDirectory)
			{
				while((myFile = readdir(myDirectory)))
				{
					if(strcmp(myFile->d_name, "statm") == 0)
					{
						// same as with stat file, make a FILE ptr and a buffer to hold contents of file
						FILE *statm_ptr;
						char statm_buf[1000];

						// open file and create string with full path
						char statm_path[100];
						strcpy(statm_path, full_path);
						strcat(statm_path, "/statm");
						statm_ptr = fopen(statm_path, "r");

						if(!statm_ptr)
							return 1;

						//put first 1000 characters of file into buf
						while(fgets(statm_buf, 1000, statm_ptr) != NULL)

						//close file
						fclose(statm_ptr);

						//split statm_buf on each space, disregard every after the first space
						//because we only want the first col
						char * statm_eof;
						statm_eof = strtok(statm_buf, " ");
						//strcpy(data->memory, statm_eof);
						printf("vmem=%s ", statm_eof);
						readCmdline(pid1);
						return 0;		
					}
				}
			}
	}
	readCmdline(pid1);
	return 0;
}

int readCmdline(char *pid1)
{
	if (c == 1) {
		struct dirent *myFile;
		DIR *myDirectory = opendir(full_path);
			if(myDirectory)
			{
				while((myFile = readdir(myDirectory)))
				{
					if(strcmp(myFile->d_name, "cmdline") == 0)
					{
						// same as previous two files, make a pointer and buffer to hold contents
						FILE *cmdline_ptr;
						char cmdline_buf[200];
						
						// open file and create string with full path
						char cmdline_path[100];
						strcpy(cmdline_path, full_path);
						strcat(cmdline_path, "/cmdline");

						cmdline_ptr = fopen(cmdline_path, "r");

						if(!cmdline_ptr)
							return 1;

						int cmdCounter = 0;
						do
						{
							char c = fgetc(cmdline_ptr);

							if(isprint(c))
							{
								//printf("\n");
								//break;
								printf("%c", c);
							}
							else if(c == '\0')
							{
								printf(" ");
							}
							else
							{
								break;
							}

							

							cmdCounter++;

						} while(cmdCounter < 300);

						fclose(cmdline_ptr);

						printf("\n");
						

				

						return 0;
					}
				}
			}
	
	}
	printf("\n");
	return 0;
}

int readStatus(char *pid1)
{
	struct dirent *myFile;

	// Initializes the global variable full_path
	fullPath(pid1);
	DIR *myDirectory = opendir(full_path);

		if(myDirectory && pid == NULL)
		{
			while((myFile = readdir(myDirectory)))
			{
				if(strcmp(myFile->d_name, "status") == 0)
				{
					FILE *status_ptr;
					char status_buf[200];
					
					//open file and create string with full path
					char status_path[100];
					strcpy(status_path, full_path);
					strcat(status_path, "/status");
					status_ptr = fopen(status_path, "r");
					
					if(!status_ptr)
						return 1;

					int linecounter = 0;
					char uidLine[200];
					while(fgets(status_buf, 200, status_ptr) != NULL)
					{
						linecounter++;
						if(linecounter == 9)
						{
							strcpy(uidLine, status_buf);
						}
					}

					fclose(status_ptr);
					char *status_eof;
					status_eof = strtok(uidLine, "\t");
					int uidCounter = 0;
					while(status_eof != NULL)
					{
						status_eof = strtok(NULL, "\t");
						uidCounter++;
						if(uidCounter == 2)
						{
							if (strcmp(status_eof, uid) != 0){
								return 0;
							}
						}
					}
				}
			}
		}
		readStat(pid1);	
		return 0;
}
			

