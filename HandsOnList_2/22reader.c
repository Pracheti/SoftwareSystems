/* 
NAME : PRACHETI BHALE
ROLL NO : MT2023155

22) Write a program to wait for data to be written into FIFO within 10 seconds, use select system call with FIFO.
*/

#include <sys/types.h> 
#include <sys/stat.h>  
#include <fcntl.h>     
#include <unistd.h>    
#include <stdio.h> 

int main(){
	//Creating a Fifo file
	mkfifo("./fifo_for_22_code", 0777); 

	//Fifo file initialization
	int sending_fd;
	sending_fd = open("./fifo_for_22_code", O_WRONLY, 0777);


	//Select System Call values initialization
	fd_set rfds;
	struct timeval tv;
	int retval;
	FD_ZERO(&rfds);  			  //void FD_ZERO(fd_set * fdset );
	FD_SET(sending_fd, &rfds);    //void FD_SET(int fd , fd_set * fdset );
	tv.tv_sec = 10;
	tv.tv_usec = 0;
	retval = select(5, &rfds, NULL, NULL, &tv);
	
	//Checking if any write was performed on fifo in these 10 seconds
	if(retval == -1)
		printf("An error has occurred.");
	else if(retval){
		char readingBuffer[100];
		read(sending_fd, &readingBuffer, 100);
		printf("Data written is : %s", readingBuffer);
		
		}
	else
		printf("\nNo input was given within 10 seconds, data is not available for reading.");
	
	return 0;
}
