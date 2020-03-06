#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

int x=10, y=20, z=0;		//Global variables

//Computes on the thread
void *thread_compute(void* arg){

	printf("This is the beginning of the thread \n");
	printf("The value of x,y,z before thread process completes is :%d %d %d \n", x,y,z);
	z = x + y;
	printf("The value of Z before thread process exits is :%d \n",z);
	
	return NULL;
}

int main(){

pid_t pid;
pthread_t tid;

printf("The value of Z before child process is created is :%d \n",z);
//fork child
if ((pid = fork()) < 0){
	perror("fork error");
}

//parent process
else if (pid > 0){
	
	wait(NULL);
	printf("The value of Z after child process completes is :%d \n",z);	
	
	//Create thread
	if(pthread_create(&tid, NULL, thread_compute, NULL)){
		fprintf(stderr, "Error while creating thread \n");
		exit(1);
	}
	else{
		pthread_join(tid,NULL);	//"Wait" for the thread to complete
		
	}
	printf("The value of Z after thread process completes is :%d \n",z);
	
	
}
//Same old child process
else{
	printf("The value of x,y,z before child process completes is :%d %d %d \n", x,y,z);
	z = x + y;
	printf("The value of Z after child process computes is :%d \n",z);
}
return 0;
}


