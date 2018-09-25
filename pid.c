#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

// struct to hold all things we might need to print
struct Process
{
	char pid[50];
	char state[5];
	char user_time[50];
	char sys_time[50];
	char virt_mem[50];
	char cmd_line[200];
	char user_id[50];
};

int main(int c, char *v[])
{

	//directory
	DIR *myDirectory;
	struct dirent *myFile;

	//process struct to hold relevant info from parsed stat
	struct Process *data = (struct Process*)malloc(sizeof(struct Process));

	if(c == 2)
	{
		char full_path[100];

		//put "/proc/" into variable
		strcpy(full_path, "/proc/");
		
		//add pid string to full path 
		strcat(full_path, v[1]);
		
		//open directory belonging to pid		
		myDirectory = opendir(full_path);

		if(myDirectory)
		{
			//puts("dir opened, files:");
			while((myFile = readdir(myDirectory)))
			{
				//printf("%s\n", myFile->d_name);

				if(strcmp(myFile->d_name, "stat") == 0)
				{
					//printf("%s\n", "stat found");
					// file pointer and buf to hold contents of file
					FILE *ptr_file;
					char buf[1000];

					// open file, create string with full path
					char stat_path[100];
					strcpy(stat_path, full_path);
					strcat(stat_path, "/stat");
					//printf("%s\n",stat_path);
					ptr_file = fopen(stat_path, "r");
					
					//return 1 if fails to open file
					if(!ptr_file)
						return 1;

					//put first 1000 characters of file into buf
					while(fgets(buf, 1000, ptr_file) != NULL)

					//close file
					fclose(ptr_file);

					//print contents of buf
					//printf("%s", buf);

					//split buf on each space
					char * eof;
					eof = strtok(buf, " ");
					int counter = 0;
					
					while(eof != NULL && counter < 20)
					{

						//printf("%s\n", eof);


						if(counter == 0)
						{
							//printf("%s\n","1");
							//data.pid = eof;
							//printf("%s\n", eof);
							strcpy(data->pid, eof);
						}
						if(counter == 2)
						{
							//printf("%s\n","3");
							//printf("%s\n", eof);
							strcpy(data->state, eof);
						}
						if(counter == 13)
						{
							//printf("%s\n","14");
							//printf("%s\n", eof);
							strcpy(data->user_time, eof);
						}
						if(counter == 14)
						{
							//printf("%s\n","15");
							//printf("%s\n", eof);
							strcpy(data->sys_time, eof);
						}

						//printf("%s", "Counter: ");
						//puts(counter);
						//printf("%d\n",counter);
						//printf("%s", "EOF Val: ");
						//printf("%s\n", eof);
						eof = strtok(NULL, " ");
						counter++;
					}

					//return 0;
					
				}


				if(strcmp(myFile->d_name, "statm") == 0)
				{
					// same as with stat file, make a FILE ptr and a buffer to hold contents of file
					//printf("%s\n","statm found");
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

					//print contents of statm_buf
					//printf("%s\n", statm_buf);

					//split statm_buf on each space, disregard every after the first space
					//because we only want the first col
					char * statm_eof;
					statm_eof = strtok(statm_buf, " ");
					strcpy(data->virt_mem, statm_eof);
				}
	
				if(strcmp(myFile->d_name, "cmdline") == 0)
				{
					//printf("%s\n", "cmdline found");
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

					//put first 200 characters of file into buf
					while(fgets(cmdline_buf, 200, cmdline_ptr) != NULL)

					//printf("%s\n", cmdline_buf);

					//close file
					fclose(cmdline_ptr);
					
					char * cmdline_eof;
					cmdline_eof = strtok(cmdline_buf, " ");

					strcpy(data->cmd_line, cmdline_eof);
				}

				if(strcmp(myFile->d_name, "status") == 0)
				{
					//printf("%s\n", "status found");
					//printf("%d\n", getuid());
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
						//printf("%d", linecounter);
						//printf("%s", ":   ");
						//printf("%s\n", status_buf);
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
						//printf("%s\n", status_eof);
						status_eof = strtok(NULL, "\t");
						uidCounter++;
						if(uidCounter == 2)
						{
							strcpy(data->user_id, status_eof);
						}
					}

					//printf("%s\n", uidLine);
				}

					
			}
			if(closedir(myDirectory) == 0)
			{
				//puts("directory closed");
			}
			else
			{
				//puts("directory cannot be closed");
			}
		}

		printf("%s\n","end reached");
		printf("%s\n", data->pid);
		printf("%s\n", data->state);
		printf("%s\n", data->user_time);
		printf("%s\n", data->sys_time);
		printf("%s\n", data->virt_mem);
		printf("%s\n", data->cmd_line);
		printf("%s\n", data->user_id);
		
		
	}
}
