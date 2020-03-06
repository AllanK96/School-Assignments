#ifndef PART2_H
#define PART2_H
#include<stdio.h>

struct queue_tag{
	int num;		//Queue number
	int priority;		//Priority level of queue
	int procQ[10];		//List of processes	
	int burst_list[10];	//List of burst times connected to processes
	int TQ;			//Time quantum, set when queue type R
	char queueType[10];	//FCFS, RR, or SJF
};


int round_robin(struct queue_tag RRQueue, FILE *f);		//declare
int FCFS(struct queue_tag FCFSQueue, FILE *p);
int SJF(struct queue_tag SJFQueue, FILE *f);

#endif 
