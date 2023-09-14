/*
Name : Pracheti Bhale
Roll No : MT2023155

4) 4) Write a program to open an existing file with read write mode. Try O_EXCL flag also.
*/
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){
	//The "open()" system call opens an existing file for reading or writing. It has the syntax:
	//<file descriptor variable> = open( <filename>, <access mode> );

	int fd1, fd2;
	fd1 = open("new_file", O_RDWR);
	printf("\nThe file descriptor value is : %d \n", fd1);
	
	//If both O_CREAT and O_EXCL are set, then open fails if the specified file already exists. 
	fd2 = open("new_file", O_CREAT | O_EXCL, O_RDWR);
	printf("The file descriptor value is : %d \n", fd2);
	return 0;
}
