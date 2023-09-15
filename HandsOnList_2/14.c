/*
Name : Pracheti Bhale
Roll no : MT2023155

14) Write a simple program to create a pipe, write to the pipe, read from pipe and display on the monitor.
*/

#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main(){
	int i, j, filedes[2];
	char buff[10];
	i = pipe(filedes);   //Returns 0 on success, or –1 on error
	printf("\nEnter data to be written in pipe : ");
	scanf("%s", buff);
	write(filedes[1], buff, 10);
	read(filedes[0], buff, 10);
	printf("\nData read from the pipe is : %s", buff);
	return 0;	
}
