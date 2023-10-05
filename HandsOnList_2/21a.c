/*
Name : Pracheti Bhale
Roll no : MT2023155

21) Write two programs so that both can communicate by FIFO -Use two way communication.
*/

#include <sys/types.h> 
#include <sys/stat.h>
#include <stdlib.h>  
#include <fcntl.h>     
#include <unistd.h>    
#include <stdio.h> 
#include <string.h>

/* 
pracheti@pracheti-Lenovo-ideapad-320-15IKB:~/SoftwareSystem/HandsOnList_2$ mkfifo -m 777 /home/pracheti/SoftwareSystem/HandsOnList_2/fifo_for_21a_code
pracheti@pracheti-Lenovo-ideapad-320-15IKB:~/SoftwareSystem/HandsOnList_2$ mkfifo -m 777 /home/pracheti/SoftwareSystem/HandsOnList_2/fifo_for_21b_code
*/

int main(){
	int sending_fd, receiving_fd;
	char sendingBuffer[100], receivingBuffer[100];
	
	// Sending data to program 21b.c
	printf("\nEnter data to be sent to receiver : ");
	scanf("%[^\n]s", sendingBuffer);
	sending_fd = open("./fifo_for_21a_code", O_WRONLY, 0777);
	if(sending_fd == -1){
		perror("Error while opening fifo file..");
		exit(0);
	}
	write(sending_fd, sendingBuffer, 100);
	close(sending_fd);
	
	//Receiving data from program 21b.c
	receiving_fd = open("./fifo_for_21b_code", O_RDONLY, 0777);
	if(receiving_fd == -1){
		perror("Error while opening fifo file..");
		exit(0);
	}
	read(receiving_fd, &receivingBuffer, 100);
	printf("Data sent from Receiver is : %s",receivingBuffer);
	close(receiving_fd);
}
