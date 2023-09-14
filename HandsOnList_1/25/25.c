/*
Name : Pracheti Bhale
Roll No : MT2023155

25) Write a program to create three child process. The parent should wait for a particular child(use waitpid system call).
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>	

/* waitpid() suspends the calling process until the system gets status information on the PARTICULAR child. */

int main(){
	int pid1, pid2, pid3, wait_pid, stat;
	if(fork() == 0){   //Child Process - 1
		pid1 = getpid(); 
		printf("\n1. %d", pid1);
	}
	else{
		if(fork() == 0){  //Child Process - 2
			pid2 = getpid();
			printf("\n2. %d", pid2);
		}
		else{
			if(fork() == 0){  //Child Process - 3
				pid3 = getpid();
				printf("\n3. %d", pid3);
			}
			else{	//Parent Process
				printf("Following are the PID's of 3 Child process :-");
				printf("\nEnter the PID of child process for whom Parent should wait : ");
				scanf("%d", &wait_pid);
				
				pid_t child_status = waitpid((pid_t)wait_pid, &stat, 0);
				if(child_status)
					printf("\nRequested Child process exited with status of %d\n", stat);
				else
					printf("\nError in waitpid system call.");
			}
		}
		/* 1st arg : If pid is greater than 0, waitpid() waits for termination of the specific child whose process ID is equal to pid.
		   2nd arg : Points to a location where waitpid() can store a status value.
		   3rd arg : The options value is constructed from the bitwise inclusive-OR of zero or more of the flags(WCONTINUED, WNOHANG, WUNTRACED)
		   If successful, waitpid() returns a value of the process (usually a child) whose status information has been obtained.
		*/	
	}
}
