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
					printf("stat found");
					// file pointer and buf to hold contents of file
					FILE *ptr_file;
					char buf[1000];

					// open file, create string with full path
					char stat_path[100];
					strcpy(stat_path, full_path);
					strcat(stat_path, "/stat");
					printf("%s\n",stat_path);
					ptr_file = fopen(stat_path, "r");
					
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
					
					//while(eof != NULL || counter < 16)
					while(counter < 16)
					{
						//printf("%s\n", eof);
						eof = strtok(NULL, " ");
						if(counter == 1)
						{
							printf("%s\n","1");
							//data.pid = eof;
							printf("%s\n", eof);
							strcpy(data->pid, eof);
						}
						if(counter == 3)
						{
							printf("%s\n","3");
							printf("%s\n", eof);
							strcpy(data->state, eof);
						}
						if(counter == 13)
						{
							printf("%s\n","14");
							printf("%s\n", eof);
							strcpy(data->user_time, eof);
						}
						if(counter == 14)
						{
							printf("%s\n","15");
							printf("%s\n", eof);
							strcpy(data->sys_time, eof);
						}

						counter++;
					}

					//return 0;
					
				}
			}
			if(closedir(myDirectory) == 0)
				puts("directory closed");
			else
				puts("directory cannot be closed");
		}

		printf("%s\n","end reached");
		printf("%s\n",data->pid);
		printf("%s\n",data->state);
		printf("%s\n",data->user_time);
		printf("%s\n",data->sys_time);
		
		
	}
}
