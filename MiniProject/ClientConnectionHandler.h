#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <string.h>
#include <stdlib.h>

//==================================================================
// Function Declaration
void Connect_With_Admin(int Socket_Descriptor);
void Connect_With_Respective_Client(int Socket_Descriptor);
//==================================================================

void Connect_With_Respective_Client(int Socket_Descriptor){
	char choice[10];
	int User_choice;
	
	read(Socket_Descriptor, (char *)&choice, 2);
	User_choice = atoi(choice);
	switch(User_choice){
		case 1:	
			printf("\nInside client conn handler");
			Connect_With_Admin(Socket_Descriptor);
			
			break;
		case 2:
			//Connect_With_Faculty(Socket_Descriptor);
			break;
		case 3:
			//Connect_With_Student(Socket_Descriptor);
			break;
		default:
			close(Socket_Descriptor);	
	}
}

void Connect_With_Admin(int Socket_Descriptor){
	char Message_Received[1000], Message_Sent[1000];
	int Read_Status;
	
	do{
		Read_Status = read(Socket_Descriptor, Message_Received, 1000);  /* Read Admin Menu from Server.c->ServerConnectionHandler.h->Admin.h file*/
		if(Read_Status == -1)
			perror("Error while reading Admin Menu from Server");
		
		printf("%s", Message_Received);
		
	
	}while(Read_Status>0);

}
