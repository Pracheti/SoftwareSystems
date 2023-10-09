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

#define PORT 6000

void Connect_With_Client(int Socket_Descriptor){
	int User_choice;
	ssize_t Bytes_Read;
	char choice[100];
	
	bzero(choice, sizeof(choice));
	Bytes_Read = read(Socket_Descriptor, choice, sizeof(choice));
	if(Bytes_Read == -1){
		perror("Error while Reading choice sent by Client.. Exiting..");
		close(Socket_Descriptor);
	}	
	else{
		User_choice = atoi(choice);
		//printf("\nChoice sent by Client : %d", User_choice);
				
		switch(User_choice){
			case 1:	
				//printf("Inside Server Conn Handler");
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

    printf("Terminating connection to client!\n");

}

int main(){
	int Socket_File_Descriptor, Bind_Status, Listen_Status, New_Socket_File_Descriptor, Length_of_Address;
	ssize_t No_of_Bytes_Read, No_of_Bytes_Written;

	struct sockaddr_in Server_Address, Client_Address;   /* IPv4 socket address */
	struct in_addr Socket_Address;   /* IPv4 4-byte address : Unsigned 32-bit integer*/
	
	
	Server_Address.sin_family = AF_INET;
	Server_Address.sin_port = htons(PORT);
	Server_Address.sin_addr.s_addr = htonl(INADDR_ANY);  /* When INADDR_ANY is used as the address when calling bind(), the socket accepts connections to all the IPs of the machine. */
	
	
	Socket_File_Descriptor = socket(AF_INET, SOCK_STREAM, 0);	/* int socket(int domain , int type , int protocol ); */
	if(Socket_File_Descriptor == -1){
		perror("Error creating socket.. ");
		exit(0);
	}
		
	Bind_Status = bind(Socket_File_Descriptor, (struct sockaddr *)&Server_Address, sizeof(Server_Address));   /* int bind(int sockfd , const struct sockaddr * addr , socklen_t addrlen ); */
	if(Bind_Status == -1){
		perror("Error while binding the socket.. ");
		exit(0);
	}
	
	printf("\nServer has started listening on Port : %d", PORT);
	
	Listen_Status = listen(Socket_File_Descriptor, 5);
	if(Listen_Status == -1){
		perror("Error while listening.. ");
		exit(0);
	}
	printf("\nServer is listening for incoming Client requests..." );
	
	Length_of_Address = sizeof(Client_Address);
	while(1){
		
		New_Socket_File_Descriptor = accept(Socket_File_Descriptor, (struct sockaddr *)&Client_Address, &Length_of_Address);	
		/* int accept(int sockfd , struct sockaddr * addr , socklen_t * addrlen ); */
		if(New_Socket_File_Descriptor == -1){
			perror("Error creating socket.. ");
			exit(0);
		}
		printf("\nServer has accepted connection request with Socket Descriptor : %d", New_Socket_File_Descriptor);
		
		if(fork() == 0){ 	//Child Process
			printf("\nCreated a Child Process to handle new request..");
			Connect_With_Client(New_Socket_File_Descriptor);
			close(New_Socket_File_Descriptor);
		}
	} 
	close(Socket_File_Descriptor);
	return 0;
}
