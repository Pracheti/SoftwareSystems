#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h> 
#include <sys/socket.h>

int main(){
	int Socket_File_Descriptor, ;
	struct sockaddr_in Client_Address; 		/* IPv4 socket address */
	struct in_addr Socket_Address;   /* IPv4 4-byte address : Unsigned 32-bit integer*/
	
	Client_Address.sin_family = AF_INET;
	Client_Address.sin_port = htons(7000);
	Client_Address.sin_addr.s_addr = INADDR_ANY;

	Socket_File_Descriptor = socket(AF_INET, SOCK_STREAM, 0);			/* int socket(int domain , int type , int protocol ); */
	if(Socket_File_Descriptor == -1){
		perror("Error creating socket.. ");
		exit(0);
	}

	/* int connect(int sockfd , const struct sockaddr * addr , socklen_t addrlen ); */
	return 0;
}
