/*
Name : Pracheti Bhale
Roll No : MT2023155

24) Write a program to create an Orphan process.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main(){
	if(fork()==0){
		printf("\n Child process before becaming orphan...");
		printf("\n Child process PID : %d", getpid());
		sleep(1);
		printf("\n Child process after becaming orphan...");
		printf("\n Child process PID : %d", getpid());
		while(1);  //To check Child process's pid
	}
	else{
		printf("\n Parent process PID : %d", getpid());
		sleep(30);
	}
}
