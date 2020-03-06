#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(){

int n;		// track of num byttes read
int x,y;	// Variables
int fd[2]; 	// holds fds of both ends of pipe
pid_t pid;	// PID of Child Process

//Create pipe
if (pipe(fd) < 0){
	perror("pipe error");
}

printf("A pipe is created for communication between parent (PID: %d) and child \n", getpid());

//fork child
if ((pid = fork()) < 0){
	perror("fork error");
}

//parent process
else if (pid > 0){
	printf("Parent (PID: %d) create a child (PID: %d)\n",getpid(),pid);
	x = 10;		//Said in class that hardcoding the user input was fine
	printf("Parent (PID: %d) Reading X = %d from the user* \n",getpid(),x);
	wait(NULL);	//Wait for child to complete

	n = read(fd[0], &y, 80);	//Read Y from the pipe
	printf("Parent (PID: %d) Reading Y from the pipe (Y = %d)\n", getpid(),y);	
	printf("Parent (PID: %d) adding X + Y = %d\n", getpid(), y+x);

	exit(0);
}
//child process
else{
	y = 20;		//Said in class that hardcoding the user input was fine
			//Since scanf is funky

	printf("Child (PID: %d) Reading Y = %d from the user* \n",getpid(),y);
	printf("Child (PID: %d) Writing Y into the pipe \n", getpid());
	write(fd[1], &y, sizeof(y));		//Write Y to the pipe
}

return 0;
}
