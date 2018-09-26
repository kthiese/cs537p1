CS 537 Programming Assignment 1:

	The objective of this assignment was to create a program that functions similarly to the linux "ps" command.  When run without any arguments the program displays all currently running processes that belong to the current user as well as the user time and command line entries that started the process.  Using input flags the output can be changed to only show information for a single program as well as show the single character state of the running program or programs, the system time consumed by the program or programs, and the virtual memory currently being used in pages by the program or programs.

	We chose to seperate our program into three C files:

	pid.c contains a method which returns all the pid's in the proc folder.

	readFiles.c contains methods to read and parse the stat, status, statm, and cmdline files as well as checks whether the uid of the process matches the global uid (the uid of the user).

	cmdLnParser.c contains the main method, it takes the command line input, parses the flags and calls the readDirectory method in pid.c which in turn calls the various methods in readFiles.c to print the requested information.

	We chose to divide our program into these modules because it seemed to be a good way to divide the total work load between group members as well as because it is what is suggested on the assigment page.
