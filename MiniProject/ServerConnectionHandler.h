#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <string.h>
#include <stdlib.h>
#include "Admin.h"

void Connect_With_Respective_Client(int Socket_Descriptor){
	int Read_Status, User_choice;
	char choice[10];

	printf("\nReached here");
	
	Read_Status = read(Socket_Descriptor, choice, sizeof(choice));
	User_choice = atoi(choice);
	printf("\nChoice : %d", User_choice);
	if(Read_Status == -1){
		perror("Error while Reading choice sent by Client");
		close(Socket_Descriptor);
	}
	switch(User_choice){
		case 1:	
			printf("Inside Server Conn Handler");
			Connect_With_Admin(Socket_Descriptor);
			break;
		case 2:
			//Connect_With_Faculty(Socket_Descriptor);
			break;
		case 3:
			//Connect_With_Student(Socket_Descriptor);
			break;
		default:
			printf("\nEnter valid choice");
			close(Socket_Descriptor);
	}
}
