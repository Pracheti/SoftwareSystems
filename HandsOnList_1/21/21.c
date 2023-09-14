/*
Name : Pracheti Bhale
Roll No : MT2023155

21) Write a program call, fork() and print the parent & child process id.
*/

#include<sys/types.h>
#include<stdio.h>
#include<unistd.h>

int main(){
	if(fork()==0){
		printf("\n Child process PID : %d", getpid());
	}
	else{
		printf("\n Parent process PID : %d", getpid());
	}
}
