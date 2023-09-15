/*
Name : Pracheti Bhale
Roll no : MT2023155

14) Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
*/

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main(){
	int filedes[2];
	char buff[10];
	pipe(filedes);   //Returns 0 on success, or –1 on error
	printf("\nEnter data to be written in pipe : ");
	scanf("%s", buff);
	write(filedes[1], buff, 10);
	//Could also be written as : write(filedes[1], buff, sizeof(buff));
	read(filedes[0], buff, 10);
	//Could also be written as : write(filedes[0], buff, sizeof(buff));
	printf("\nData read from the pipe is : %s", buff);
	return 0;	
}
