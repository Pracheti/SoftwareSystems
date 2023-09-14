/*
Name : Pracheti Bhale
Roll No : MT2023155

12) Write a program to find out the opening mode of a file. Use fcntl.
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	int fd = open(argv[1], O_RDWR|O_CREAT, 777);
	if(fd == -1){
		printf("The file doesn't exist\n");
		return 0;
	}
	int flags = fcntl(fd, F_GETFL);
	if(flags & O_RDWR){
		printf("The file is opened in read-write mode");
	}
	else{
		printf("The file is opened in read-write mode");
	}
	return 0;
}
