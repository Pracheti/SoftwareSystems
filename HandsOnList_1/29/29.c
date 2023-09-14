/*
Name : Pracheti Bhale
Roll No : MT2023155

29) Write a program to get scheduling policy & modify the scheduling policy (SCHED_FIFO, SCHED_RR).
*/

#include<stdio.h>
#include<unistd.h>
#include<sched.h>

int main(){
	int policy, pid;
	
	/*The sched_setscheduler() system call changes both the scheduling policy and the priority of the process whose process ID is specified 	in pid. If pid is specified as 0, the attributes of the calling process are changed. The sched_getparam() system call returns the 		  realtime priority of the specified process in the sched_priority field of the sched_param structure pointed to by param.*/
	
	//int sched_setscheduler(pid_t pid , int policy , const struct sched_param * param );
	
	/* The param argument is a pointer to a structure of the following form:
	struct sched_param {
		int sched_priority;
	};
	*/
	struct sched_param priority; 
	priority.sched_priority = 1;   //Highest priority = 1, lowest priority = 99
	pid = getpid();
	policy = sched_getscheduler(pid);
	printf("\nThe current scheduling policy returned is %d", policy);
	
	printf("\nEnter which policy needs to be applied : ");
	printf("\n1. Round Robin \n2. FIFO\n");
	scanf("%d", &policy);
	if(policy == 1)
		sched_setscheduler(pid, SCHED_FIFO, &priority);
	else 
		sched_setscheduler(pid, SCHED_RR, &priority);
	
	policy = sched_getscheduler(pid);
	printf("\nThe changed policy returned number is %d\n", policy);
}
