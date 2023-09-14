/*
Name : Pracheti Bhale
Roll No : MT2023155

6) Write a program to take input from STDIN & display on STDOUT. Use read/write system call.
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

/* ssize_t read(int fd , void * buffer , size_t count );  A successful call to read() returns the number of bytes actually read, or 0 if end-of-file is encountered. 
ssize_t write(int fd, const void *buf, size_t count);  On success, the number of bytes written is returned. On error, -1 is returned, and errno is set to indicate the cause of the error.
*/

int main(){
	printf("Enter some data (Enter 0 to break): ");
	while(1){
		int buff;
		read(0, &buff, 2);   //Reading from STDIN (Here, terminal)
		if(buff == 0)
			break;	
			
		printf("Data Entered : ");
		write(1, &buff, 2);     //Writing to STDOUT (Here, terminal)
	}
	return 0;
}
