#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h> 
#include <sys/socket.h>

#define PORT 8000

//Function Definition
Connect_With_Respective_Client(Socket_Descriptor);

int main(){
	int Socket_File_Descriptor, Bind_Status, Listen_Status, New_Socket_File_Descriptor, No_of_Bytes_Read, No_of_Bytes_Written, Length_of_Address;
	char Data_Sent_by_Client[100];
	struct sockaddr_in Server_Address, Client_Address;   /* IPv4 socket address */
	struct in_addr Socket_Address;   /* IPv4 4-byte address : Unsigned 32-bit integer*/
	
	
	Server_Address.sin_family = AF_INET;
	Server_Address.sin_port = htons(PORT);
	Server_Address.sin_addr.s_addr = INADDR_ANY;  /* When INADDR_ANY is used as the address when calling bind(), the socket accepts connections to all the IPs of the machine. */
	
	
	Socket_File_Descriptor = socket(AF_INET, SOCK_STREAM, 0);			/* int socket(int domain , int type , int protocol ); */
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
	
	printf("\nServer is listening for incoming Client requests...");
	
	while(1){
		Length_of_Address = sizeof(Client_Address);
		New_Socket_File_Descriptor = accept(Socket_File_Descriptor, (struct sockaddr *)&Client_Address, &Length_of_Address);	/* int accept(int sockfd , struct sockaddr * addr , socklen_t * addrlen ); */
		if(New_Socket_File_Descriptor == -1){
			perror("Error creating socket.. ");
			exit(0);
		}
		
		printf("\nServer has accepted connection request with Socket Descriptor : %d", New_Socket_File_Descriptor);
		
		if(fork() == 0){ 	//Child Process
			Connect_With_Respective_Client(New_Socket_File_Descriptor);
			close(New_Socket_File_Descriptor);
		}
	}
	close(Socket_File_Descriptor);
	return 0;
}

void Connect_With_Respective_Client(int Socket_Descriptor){
	int choice;
	read(Socket_Descriptor, &choice, sizeof(choice));
	
	switch(choice){
		case 1:	
			Connect_With_Admin(Socket_Descriptor);
			break;
		case 2:
			//Connect_With_Faculty(Socket_Descriptor);
			break;
		case 3:
			//Connect_With_Student(Socket_Descriptor);
			break;
		default:
			printf("\n Enter valid choice");
	
	}
}
