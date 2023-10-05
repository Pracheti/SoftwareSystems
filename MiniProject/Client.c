#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <string.h>
#include <stdlib.h>
#include "./ClientConnectionHandler.h"

#define PORT 8001

int main(){
	int Socket_File_Descriptor, Connection_Status, Write_Status;
	char choice[10];
	struct sockaddr_in Server_Address; 		/* IPv4 socket address */
	struct in_addr Socket_Address;   /* IPv4 4-byte address : Unsigned 32-bit integer*/
	
	Server_Address.sin_family = AF_INET;
	Server_Address.sin_port = htons(PORT);
	Server_Address.sin_addr.s_addr = INADDR_ANY;

	Socket_File_Descriptor = socket(AF_INET, SOCK_STREAM, 0);			/* int socket(int domain , int type , int protocol ); */
	if(Socket_File_Descriptor == -1){
		perror("Error creating socket.. ");
		exit(0);
	}

	Connection_Status = connect(Socket_File_Descriptor, (struct sockaddr *)&Server_Address, sizeof(Server_Address)); /* int connect(int sockfd , const struct sockaddr * addr , socklen_t addrlen ); */
	if(Connection_Status == -1){
		perror("Error connectioning to the server...");
		close(Socket_File_Descriptor);
        exit(0);
	}
	
	printf("Successfully connected with the Server...\n\n");
	printf("\n****************WELCOME TO COURSE REGISTRATION PORTAL********************");
	printf("\n1. Admin");
	printf("\n2. Faculty");
	printf("\n3. Student");
	printf("\n4. Exit");
	printf("\nEnter login type : ");
	scanf("%s", choice);
	printf("\n*************************************************************************\n");
	Write_Status = write(Socket_File_Descriptor, choice, sizeof(choice));
	
	if(Write_Status == -1){
		perror("Unable to write data to server..");
		exit(0);
	}
	
	Connect_With_Respective_Client(Socket_File_Descriptor);
	while(1);
	close(Socket_File_Descriptor);
	
	return 0;
}
