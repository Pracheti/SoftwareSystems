/*
Name : Pracheti Bhale
Roll no : MT2023155

20) Write two programs so that both can communicate by FIFO -Use one way communication.
*/

#include <sys/types.h> 
#include <sys/stat.h>
#include <stdlib.h>  
#include <fcntl.h>     
#include <unistd.h>    
#include <stdio.h> 
#include <string.h>

int main(){
	int fd;
	char data[100];
	printf("\nEnter data to be sent to receiver : ");
	scanf("%[^\n]s", data);
	fd = open("./fifo_for_20th_code", O_WRONLY, 0777);
	if(fd == -1){
		perror("Error while opening fifo file..");
		exit(0);
	}
	write(fd, data , 100);
	close(fd);
}
