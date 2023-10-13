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

void main()
{
	int Socket_File_Descriptor, Connection_Status;
	struct sockaddr_in Server_Address; 		/* IPv4 socket address */
	struct in_addr Socket_Address;   		/* IPv4 4-byte address : Unsigned 32-bit integer*/
	
	Server_Address.sin_family = AF_INET;
	Server_Address.sin_port = htons(3000);
	Server_Address.sin_addr.s_addr = htonl(INADDR_ANY);

	Socket_File_Descriptor = socket(AF_INET, SOCK_STREAM, 0);			/* int socket(int domain , int type , int protocol ); */
	if(Socket_File_Descriptor == -1){
		perror("Error creating socket.. ");
	}

	Connection_Status = connect(Socket_File_Descriptor, (struct sockaddr *)&Server_Address, sizeof(Server_Address)); /* int connect(int sockfd , const struct sockaddr * addr , socklen_t addrlen ); */
	if(Connection_Status == -1){
		perror("Server Down!! Please try again later..");
		close(Socket_File_Descriptor);
	}
	
	char data_1[100] = "Hello Server";
	char data_2[100];	
	int rB = read(Socket_File_Descriptor, &data_2, 100);
	int wB = write(Socket_File_Descriptor, &data_1, 100);
	
	printf("\nMessage from Server : %s\n", data_2);
	close(Socket_File_Descriptor);
}

