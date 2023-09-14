/*
Name : Pracheti Bhale
Roll No : MT2023155

3) Write a program to create a file & print the file descriptor value. Use creat() System call.
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){
	int fd;
	
	//The "creat()" system call creates a file. It has the syntax:
	//<file descriptor variable> = creat( <filename>, <protection bits> );
	
	fd = creat("test_file", 777);
	printf("\nThe file descriptor value is : %d\n", fd);
	return 0;
}
