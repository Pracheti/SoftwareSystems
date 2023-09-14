/*
Name : Pracheti Bhale
Roll No : MT2023155

13) Write a program to wait for STDIN for 10 sec using select. Write a proper print statement to verify whether the data is available within 10 sec or not.
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	fd_set rfds;
	struct timeval tv;
	int retval;
	
	//void FD_ZERO(fd_set * fdset );
	//void FD_SET(int fd , fd_set * fdset );
	FD_ZERO(&rfds);
	FD_SET(0, &rfds);
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	retval = select(3, &rfds, NULL, NULL, &tv);
	
	//int select(int nfds , fd_set * readfds , fd_set * writefds , fd_set * exceptfds , struct timeval * timeout );
	//Returns number of ready file descriptors, 0 on timeout, or –1 on error
	//Press Enter after writing to get correct output. 
	printf("\n Press 'Enter' to finish.");
	if(retval == -1)
		printf("An error has occurred.");
	else if(retval)
		printf("\nData is available for reading within 5 seconds.");
	else
		printf("Data is not available for reading within 5 seconds.");
	return 0;
}
