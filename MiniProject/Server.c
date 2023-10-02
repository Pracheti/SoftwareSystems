#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h> 
#include <sys/socket.h>

int main(){
	int Socket_File_Descriptor, Bind_Status, Listen_Status, New_Socket_File_Descriptor, No_of_Bytes_Read;
	char Data_Sent_by_Client[100];
	struct sockaddr_in Server_Address, Client_Address;   /* IPv4 socket address */
	struct in_addr Socket_Address;   /* IPv4 4-byte address : Unsigned 32-bit integer*/
	
	
	Server_Address.sin_family = AF_INET;
	Server_Address.sin_port = htons(8000);
	Server_Address.sin_addr.s_addr = INADDR_ANY;
	
	
	Socket_File_Descriptor = socket(AF_INET, SOCK_STREAM, 0);			/* int socket(int domain , int type , int protocol ); */
	if(Socket_File_Descriptor == -1){
		perror("Error creating socket.. ");
		exit(0);
	}
		
	Bind_Status = bind(Socket_File_Descriptor, (struct sockaddr)&Server_Address, sizeof(Server_Address));   /* int bind(int sockfd , const struct sockaddr * addr , socklen_t addrlen ); */
	if(Bind_Status == -1){
		perror("Error while binding the socket.. ");
		exit(0);
	}
	
	Listen_Status = listen(Socket_File_Descriptor, 5);
	if(Listen_Status == -1){
		perror("Error while listening.. ");
		exit(0);
	}
	
	while(1){
		New_Socket_File_Descriptor = accept(Socket_File_Descriptor, (struct sockaddr)&Client_Address, sizeof(Client_Address)	/* int accept(int sockfd , struct sockaddr * addr , socklen_t * addrlen ); */
		if(New_Socket_File_Descriptor == -1){
			perror("Error creating socket.. ");
			exit(0);
		}
		
		No_of_Bytes_Read = read(New_Socket_File_Descriptor, Data_Sent_by_Client, sizeof(Data_Sent_by_Client));
		if(No_of_Bytes_Read == -1)
			perror("Error while reading from client..");
			
		close(New_Socket_File_Descriptor);
	}
	
	close(Socket_File_Descriptor);
	
	return 0;
}
