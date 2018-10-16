/*
Kathryn Thiese
NetId: Thiese
CS Login: Thiese

Alec Scheele
NetId: abscheele
CS Login ascheele

This file contains the methods to read the stat, statm, status or cmdline files and then print the requested information to the screen depending on which global variables have been set by the main method in the cmdLnParser.c file.

*/

#include <ctype.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include "readFiles.h"

// Declare constants
#define MAX_SIZE 1000
#define PATH_SIZE 100

char * proc = "/proc/";
char * full_path; 

// Intitialize global varible "full_path" that holds the path to the pid directory
void fullPath(char *pid1){
	full_path = (char *)malloc(strlen(proc) + strlen(pid1) + 1);
	strcpy(full_path, proc);
	strcat(full_path, pid1);
}

// This is the initial call from the readDirectory() function. 
// Parses the status file and checks if the process has the same uid. 
// If the p flag was passed into the program, we do not need to 
// check the files uid. 
// If there was no p flag, we need to check each process's uid. 
int readStatus(char* pid1, char** ids, int** flags)
{
	struct dirent *myFile;

	// Initializes the global variable full_path
	fullPath(pid1);
	DIR *myDirectory = opendir(full_path);
		// Checks first if there was no pid passed into the commandline. 
		if(myDirectory && ids[0] == NULL)
		{
			while((myFile = readdir(myDirectory)))
			{
				if(strcmp(myFile->d_name, "status") == 0)
				{
					FILE *status_ptr;
					int buf_size = 200;
					char status_buf[buf_size];
					
					//open file and create string with full path
					char status_path[PATH_SIZE];
					strcpy(status_path, full_path);
					strcat(status_path, "/status");
					status_ptr = fopen(status_path, "r");
					
					if(!status_ptr)
						return 1;

					int linecounter = 0;
					char uidLine[buf_size];
					while(fgets(status_buf, buf_size, status_ptr) != NULL)
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
							// if the status file's uid does not match
							// the global uid, return from call. 
							if (strcmp(status_eof, ids[1]) != 0){
								return 0;
							}
						}
					}
				}
			}
		}
		// If there was a p flag passed into the program or the process 
		// has the same uid as the user, then we go on to parsing 
		// the files. 
		readStat(pid1, flags);	
		return 0;
}

// Parses stat file and prints info based on the flags.
int readStat(char *pid1, int** flags)
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
					char *buf = (char *)malloc(sizeof(char)*MAX_SIZE + 1);
					FILE *stat_file;

					// open file, create string with full path
					char *stat_path = (char *)malloc(strlen(full_path)+strlen("/stat") +1);
					strcpy(stat_path, full_path);
					strcat(stat_path, "/stat");
				
					// Open stat file
					stat_file = fopen(stat_path, "r");
				

					//return 1 if fails to open file
					if(!stat_file){
						free(buf);
						free(stat_path);
						return 1;
					}

					//put first 1000 characters of file into buf
					while(fgets(buf, MAX_SIZE, stat_file) != NULL)
					
					//close file
					fclose(stat_file);

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
							if (*flags[0] == 1)
								printf("%s ", eof);
						}

						// Print user time of process if U flag is 1
						if(counter == 13)
						{
							if (*flags[1] == 1)
								printf("utime=%s ", eof);
						}

						// Print system time of process if S flag is 1
						if(counter == 14)
						{
							if (*flags[2] == 1)
								printf("stime=%s ", eof);
						}

						eof = strtok(NULL, " ");
						counter++;
					}
					// Go on to read the statm file
					readStatm(flags);
					free(buf);
					free(stat_path);
					return 0;
				}
			}
		// If directory not found, print the following. 
		} else {
			printf("Process %s not found.\n", pid1);
			return 1;
		}
		return 0;
		
}

// Parses statm file and prints info based on flags.
int readStatm(int** flags)
{
	if (*flags[3] == 1) {
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
						char statm_buf[MAX_SIZE];

						// open file and create string with full path
						char statm_path[PATH_SIZE];
						strcpy(statm_path, full_path);
						strcat(statm_path, "/statm");
						statm_ptr = fopen(statm_path, "r");

						if(!statm_ptr)
							return 1;

						//put first 1000 characters of file into buf
						while(fgets(statm_buf, MAX_SIZE, statm_ptr) != NULL)

						//close file
						fclose(statm_ptr);

						//split statm_buf on each space, disregard every after the first space
						//because we only want the first col
						char * statm_eof;
						statm_eof = strtok(statm_buf, " ");

						//strcpy(data->memory, statm_eof);
						printf("vmem=%s ", statm_eof);
						
						// Go on to read cmdline after 
						// reading statm.
						readCmdline(flags);
						return 0;		
					}
				}
			}
	}
	// Go onto reading the cmdline if there was not a v flag. 
	readCmdline(flags);
	return 0;
}


// Reads the cmdline file and prints based off flags
int readCmdline(int** flags)
{
	if (*flags[4] == 1) {
		struct dirent *myFile;
		DIR *myDirectory = opendir(full_path);
			if(myDirectory)
			{
				while((myFile = readdir(myDirectory)))
				{
					if(strcmp(myFile->d_name, "cmdline") == 0)
					{
						// same as previous two files, 
						//make a pointer and buffer to hold contents
						FILE *cmdline_ptr;
						char *cmdline_buf = (char *)malloc(sizeof(char)*MAX_SIZE);;
						
						// open file and create string with full path
						char cmdline_path[PATH_SIZE];
						strcpy(cmdline_path, full_path);
						strcat(cmdline_path, "/cmdline");
						
						// Open file
						cmdline_ptr = fopen(cmdline_path, "r");
						
						// Return if file does not exist
						if(!cmdline_ptr){
							free(cmdline_buf);
							return 1;
						}

						// Read file character by character, 
						// replacing any null chars with spaces.						
						int n = 0;
						char c;
						do
						{
							c = fgetc(cmdline_ptr);

							if(isprint(c))
							{
								cmdline_buf[n++] = c;
							}
							else if(c == '\0')
							{
								cmdline_buf[n++] =  ' ';
							} else {
								break;
							}
						} while(c != EOF);
						

						// The following trims any trailing spaces of the cmdline_buf.
						char *space;
						
						space = cmdline_buf + strlen(cmdline_buf) -1;
						while (space > cmdline_buf && isspace((unsigned char)*space)) space--;
						
						space[1] = '\0';

						printf("[%s]", cmdline_buf);

						fclose(cmdline_ptr);
						printf("\n");
						free(cmdline_buf);
						return 0;
					}
				}
			}
	
	}
	printf("\n");
	return 0;
}

