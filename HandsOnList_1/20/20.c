/*
Name : Pracheti Bhale
Roll No : MT2023155

20) Find out priority of your running program. Modify the priority with nice command.
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<stdlib.h>

int main(){
	//Each process has a nice value in the range –20 (high priority) to +19 (low priority); the default is 0
	int pid = getpid();
	//int getpriority(int which , id_t who );
	//PRIO_PROCESS : Operate on the process whose process ID equals who. If who is 0, use the caller’s process ID.
	printf("The nice value of the process is %d.\n", getpriority(PRIO_PROCESS, 0));
	printf("The id of the process is %d.\n", pid);
	getchar();
	nice(5);
	printf("The nice value of the process is %d\n", getpriority(PRIO_PROCESS, 0));
	while(1);
	return 0;
}
