#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(){

pid_t pid, child_pid, child_pid2; //Child 1. Child1.1. And Child 2.


pid = fork();

if (pid < 0){
	perror("fork()");
	printf("main function: error number is %d\n", errno);
	exit(pid);
}

if (pid > 0){
	printf("Parent process (PID: %d) created child_1 (PID: %d) \n",getpid(),pid);
	printf("Parent (PID: %d) is waiting for Child_1 (PID: %d) to complete before creating child_2 \n",getpid(),pid);
	wait(NULL);		//Wait for Child 1 to finish
	printf("Child_1 (PID: %d) is now completed \n", pid);
	
	child_pid2 = fork();

	if (child_pid2 < 0){
		perror("ford()");
		printf("main function: error number is %d\n", errno);
		exit(child_pid2);
	}
	if (child_pid2 > 0){
		printf("Parent (PID: %d) created child_2 (PID: %d) \n",getpid(),child_pid2);	
		wait(NULL);	//Wait for Child 2 to finish

	}
	else{
		printf("child_2 (PID: %d) is calling an external program B.out and leaving child_2 \n", getpid());
		//Call to external Hello World program
		printf("From the external program B: \n ");
		execl("B.out", NULL);
		//End of program.
		printf("This line should not have been printed if execl was successful \n");
	}

}
//Child 1
else{
	
	child_pid = fork();		//Create Child1.1

	if (child_pid < 0){
		perror("ford()");
		printf("main function: error number is %d\n", errno);
		exit(child_pid);
	}
	if (child_pid > 0){
		printf("Child_1 (PID: %d) created Child_1.1 (PID: %d) \n",getpid(),child_pid);
		wait(NULL);		//Wait for Child 1.1 to finish
	}
	//Child 1.1
	else{
		//printf("I am child 1.1. My PID is: %d\n", getpid());
		//printf("I am child 1.1. My parent PID is %d\n", getppid());
	}
}
return 0;
}


