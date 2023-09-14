/*
Name : Pracheti Bhale
Roll No : MT2023155

5) Write a program to create five new files with infinite loop. Execute the program in the background & check the file descriptor table at /proc/pid/fd.
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){
	int fd1, fd2, fd3, fd4, fd5;
	
	fd1 = creat("test_file1", 777);
	fd2 = creat("test_file2", 777);
	fd3 = creat("test_file3", 777);
	fd4 = creat("test_file4", 777);
	fd5 = creat("test_file5", 777);
	
	while(1);
	return 0;
}
