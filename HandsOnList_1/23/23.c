/*
Name : Pracheti Bhale
Roll No : MT2023155

23) Write a program to create zombie state of the running program.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include<unistd.h>

// Check child process status from another terminal using command cat /proc/<child_pid>/status and child's status, it should be Zombie.

int main(){
	if(fork()==0){
		printf("\n Child process PID : %d", getpid());
	}
	else{
		printf("\n Parent process PID : %d", getpid());
		sleep(30);
	}
}
