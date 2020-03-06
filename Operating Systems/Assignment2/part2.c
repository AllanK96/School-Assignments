#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"part2.h"

int main()
{

FILE * fp;		//Open file with pointer
fp = fopen("multilevel_queue_CPU_scheduling_input_file.txt","r");
char line[100];		//Line by line

//Holds all the queues
struct queue_tag queue_list[3];

for (int i=0;i<3;i++){
	struct queue_tag queue;

	for (int n = 0; n<10; n++)		//Fill up the 10 processes
		queue.procQ[n] = n+1;
	
	fgets(line,100,fp);

	for (int j=0; j<(int)strlen(line);j++){
		if (line[j] == 'q' && line[j-1] != 't'){
			int v = line[j+2] - '0';
			queue.num = v;
		}
		if (line[j] == 'p' && line[j+1] == 'r'){
			int p = line[j+3] - '0';	//Turn to int
			queue.priority = p;
		}

		if (line[j] == 'f' && line[j+1] == 'c')		//First come first server
			strcpy(queue.queueType,"FCFS");
		if (line[j] == 'r' && line[j+1] == 'r'){	//Round robin
			strcpy(queue.queueType,"RR");
			int g = line[j+6] - '0';	//Turn to int
			queue.TQ = g;			//Set TQ while here
		}
		if (line[j] == 's' && line[j+1] == 'j')		//Shortest job first
			strcpy(queue.queueType,"SJF");

		if ((line[j] == 'p') && (isdigit(line[j+1])) && (line[j+2] == ' ')){
			int b = line[j+1] - '0';			//Turn process number into int
			if(line[j+4] == ' '){
				int a = line[j+3] - '0';		//Turn char into int
				queue.burst_list[b-1] = a;
			}else{
				char burst[10] = {line[j+3],line[j+4]};  //Turn char into string
				queue.burst_list[b-1] = atoi(burst);	//Turn string into int and put in list
			}
		}
		else if (line[j] == 'p' && line[j+1] == '1' && line[j+2] == '0'){		//p10
			if ((isdigit(line[j+5]))){
				char burst[10] = {line[j+4], line[j+5]};
				queue.burst_list[9] = atoi(burst);
			}else{
				int a = line[j+4] - '0';
				queue.burst_list[9] = a;
			}
		}	
	}
	
	queue_list[i] = queue;		//Save the queues in a list

}


fclose(fp);

//Open file to write into
FILE *f = fopen("multilevel_cpu_output.txt", "w");

//Variables for sorting
struct queue_tag tmp_list;
int pos;

//Sort by priority
for (int i=0;i<3;i++){
	pos = i;
	for (int j=i+1;j<3;j++){
		if((queue_list[j].priority)>(queue_list[pos].priority))
			pos=j;
	}
	tmp_list = queue_list[i];
	queue_list[i] = queue_list[pos];
	queue_list[pos] = tmp_list;
}

//I was having issues with strcmp, so I had to work around with strlen
int TOTAL_TIME = 0;
for (int i = 0; i<3; i++){
	if((int)strlen(queue_list[i].queueType) == 2)
		TOTAL_TIME += round_robin(queue_list[i], f);
	else if((int)strlen(queue_list[i].queueType) == 4)
		TOTAL_TIME += FCFS(queue_list[i], f);
	else if((int)strlen(queue_list[i].queueType) == 3)
		TOTAL_TIME += SJF(queue_list[i], f);
}
printf("Total time taken from all 3 queues is :%d \n", TOTAL_TIME);
fprintf(f,"Total time taken from all 3 queues is :%d \n", TOTAL_TIME);


fclose(f);
return 0;
}

int round_robin(struct queue_tag RRQueue, FILE *f){
	
	printf("Queue #%d, with priority #%d selected\n",RRQueue.num,RRQueue.priority);
	fprintf(f,"Queue #%d, with priority #%d selected\n",RRQueue.num,RRQueue.priority);

	int total_time, i, total_proc = 10;
	int arrival_time[] = {0,1,2,3,4,5,6,7,8,9} ;	//Wasn't specified in assignment
	int flag = 0;
	int burst_clone[10];
	
	//Clone the burst times so they are adjustable
	for (int j = 0; j<10; j++)
		burst_clone[j] = RRQueue.burst_list[j];
	

	for (total_time = 0, i = 0; total_proc!= 0;){

		//printf("This is process p%d, with A CURRENT burst time of %d \n",i+1,burst_time_clone[i]);
		//If the burst can finish in a tq
		if(burst_clone[i] <= RRQueue.TQ && burst_clone[i] > 0){
			//printf("This is process p%d, I'm going to be removed\n",i+1);
			total_time += burst_clone[i];	//Adds burst time to total time
			burst_clone[i] = 0;		//Remove the burst time from process
			flag = 1;				//Flag process to be "removed"
		}

		//If the burst is bigger than the tq
		else if(burst_clone[i] > 0){	
			burst_clone[i] -= RRQueue.TQ;		//Subract the tq from burst to get remaining
			total_time += RRQueue.TQ;			//Add time to total
		}
	
		//If burst time is 0 and flag for removal has been checked
		if(burst_clone[i] == 0 && flag ==1){
			total_proc--;				//Lower the number of processes
			printf("Process p%d. With Burst Time %d  has completed ", i+1, RRQueue.burst_list[i]);
			printf("with Turnaround Time : %d \n",total_time - arrival_time[i]);	
			fprintf(f,"Process p%d. With Burst Time %d  has completed ", i+1, RRQueue.burst_list[i]);
			fprintf(f,"with Turnaround Time : %d \n",total_time - arrival_time[i]);

			flag = 0;	//reset flag
		}
		if (i == 9)
			i = 0;
		else if(arrival_time[i+1] <= total_time)
			i++;
		else
			i=0;
	}
	printf("\n");		//Make it look nicer
	fprintf(f,"\n");
return total_time;
}

int FCFS(struct queue_tag FCFSQueue, FILE *f){

	printf("Queue #%d, with priority #%d selected\n",FCFSQueue.num,FCFSQueue.priority);
	fprintf(f,"Queue #%d, with priority #%d selected\n",FCFSQueue.num,FCFSQueue.priority);
	
	//Calculate wait time of each process
	int wait_time[10] = {0};		//First process wait time is 0
	int total_time,i,j;
	float avg_wait;
	for (i=0;i<10;i++){
		printf("Process p%d. With Burst Time %d  has completed \n", i+1, FCFSQueue.burst_list[i]);
		fprintf(f,"Process p%d. With Burst Time %d  has completed \n", i+1, FCFSQueue.burst_list[i]);
		wait_time[i] = 0;
		for(j=0;j<i;j++){
			wait_time[i] += FCFSQueue.burst_list[j];	//Add wait time together
		}
	
		total_time += wait_time[i];				//Total time
	}

	//Average waiting time
	avg_wait=(float)total_time/10;
	printf("The average wait time of Q%d was: %f \n",FCFSQueue.num,avg_wait);
	fprintf(f,"The average wait time of Q%d was: %f \n",FCFSQueue.num,avg_wait);

	printf("\n");		//Make it look nicer
	fprintf(f,"\n");
	return total_time;
}

int SJF(struct queue_tag SJFQueue, FILE *f){

	printf("Queue #%d, with priority #%d selected\n",SJFQueue.num,SJFQueue.priority);
	fprintf(f,"Queue #%d, with priority #%d selected\n",SJFQueue.num,SJFQueue.priority);

	int wait_time[10] = {0}, total_time=0;
	int i,j, pos, tmp;
	int burst_clone[10], process_clone[10];

	float avg_wait;
	
	//Clone both the Process List and Burst List
	for (int k = 0; k<10; k++){
		burst_clone[k] = SJFQueue.burst_list[k];
	}
	for (int l = 0; l<10; l++){
		process_clone[l] = SJFQueue.procQ[l];
	}
	//sort burst time in ascending w/ selection sort. 
	//Yes, it's O(n^2). Yes, I could've done something more efficient.
	for (i=0;i<10;i++){
		pos = i;
		for (j=i+1;j<10;j++){
			if(burst_clone[j]<burst_clone[pos])
				pos=j;
		}
		tmp = burst_clone[i];
		burst_clone[i] = burst_clone[pos];
		burst_clone[pos] = tmp;

		tmp = process_clone[i];
		process_clone[i] = process_clone[pos];
		process_clone[pos] = tmp;
	}


	//Calculate wait time of each process
	for (i=0;i<10;i++){
		wait_time[i] = 0;
		printf("Process p%d. With Burst Time %d  has completed \n", process_clone[i], burst_clone[i]);
		fprintf(f,"Process p%d. With Burst Time %d  has completed \n", process_clone[i], burst_clone[i]);
		for(j=0;j<i;j++)
			wait_time[i] += burst_clone[j];
		total_time += wait_time[i];
	}

	//Average waiting time
	avg_wait=(float)total_time/10;

	printf("The average wait time of Q%d was: %f \n",SJFQueue.num,avg_wait);
	fprintf(f,"The average wait time of Q%d was: %f \n",SJFQueue.num,avg_wait);

	printf("\n");		//Make it look nicer
	fprintf(f,"\n");


return total_time;
}


