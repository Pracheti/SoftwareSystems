/* 
NAME : PRACHETI BHALE
ROLL NO. : MT2023155

33. Write a program to communicate between two machines using socket.
*/

#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/ip.h>
#include <stdio.h>      
#include <unistd.h>   
#include <stdlib.h>

int main(){
	int Socket_File_Descriptor, Bind_Status, Listen_Status, New_Socket_File_Descriptor, Length_of_Address;
	
	struct sockaddr_in Server_Address, Client_Address;   /* IPv4 socket address */
	struct in_addr Socket_Address;   /* IPv4 4-byte address : Unsigned 32-bit integer*/
	
	
	Server_Address.sin_family = AF_INET;
	Server_Address.sin_port = htons(3000);
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
	
	printf("\nServer has started listening on Port 3000");
	
	Listen_Status = listen(Socket_File_Descriptor, 5);
	if(Listen_Status == -1){
		perror("Error while listening.. ");
		exit(0);
	}
	printf("\nServer is listening for incoming Client requests..." );
	
	Length_of_Address = sizeof(Client_Address);
	
	New_Socket_File_Descriptor = accept(Socket_File_Descriptor, (struct sockaddr *)&Client_Address, &Length_of_Address);	
		/* int accept(int sockfd , struct sockaddr * addr , socklen_t * addrlen ); */
	if(New_Socket_File_Descriptor == -1){
		perror("Error creating socket.. ");
		exit(0);
	}
	printf("\nServer has accepted connection request with Socket Descriptor : %d", New_Socket_File_Descriptor);
		
	char data_1[100] = "Hello Client";
	char data_2[100];
	int wB = write(New_Socket_File_Descriptor, &data_1, 100);
	int rB = read(New_Socket_File_Descriptor, &data_2, 100);
	printf("\nMessage from Client : %s\n", data_2);
	close(New_Socket_File_Descriptor);
			
	close(Socket_File_Descriptor);
	return 0;
}
