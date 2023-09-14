/*
Name : Pracheti Bhale
Roll No : MT2023155

22) Write a program, open a file, call fork & then write to the file by both the child as well as the parent process. Check output of the file.
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main(){
	int fd;
	char buff;
	fd = open("NewFile.txt", O_RDWR);
	printf("\nThe file descriptor value is : %d \n", fd);
	
	if(fork()==0){
		printf("\n Child process PID : %d", getpid());
		printf("\n Writing into the file by child process....");
		buff = 'a';
		write(fd, &buff, 1);
	}
	else{
		printf("\n Parent process PID : %d", getpid());
		printf("\n Writing into the file by parent process....");
		buff = 'b';
		write(fd, &buff, 1);
	}
	return 0;
}
