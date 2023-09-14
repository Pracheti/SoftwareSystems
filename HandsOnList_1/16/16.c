/*
Name : Pracheti Bhale
Roll No : MT2023155

16) Write a program to perform mandatory locking: 
a) Implement read lock
b) Implement write lock
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>


int main(){
	struct flock lock;
	int fd = open("NewFile", O_RDWR);
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	printf("\nBefore entering into critical section");
	fcntl(fd, F_SETLKW, &lock);
	printf("\nInside the critical section");
	printf("\nPress enter to unlock");
	getchar();
	printf("\nFile unlocked");
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
}
