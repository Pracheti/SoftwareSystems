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
	
	//Writing data into fifo file
	char data[]="Hello Receiver, Have a good day!!";
	int fd = open("./fifo_for_22_code",O_WRONLY);
	write(fd, &data, sizeof(data));
	close(fd);
	return 0;
	
}
