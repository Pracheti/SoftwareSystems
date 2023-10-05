/*
Name : Pracheti Bhale
Roll no : MT2023155

20) Write two programs so that both can communicate by FIFO -Use one way communication.
*/

#include <sys/types.h> 
#include <sys/stat.h>  
#include <fcntl.h>     
#include <unistd.h>    
#include <stdio.h> 
#include <stdlib.h>

int main()
{
	int fd;
	char data[100];
	fd = open("./fifo_for_20th_code", O_RDONLY, 0777);
	if(fd == -1){
		perror("Error while opening fifo file..");
		exit(0);
	}
	read(fd, &data, 100);
	printf("%s",data);
	close(fd);
	return 0;
}
