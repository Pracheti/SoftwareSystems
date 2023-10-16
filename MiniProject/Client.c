#include <stdio.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <string.h>
#include <stdlib.h>

#define PORT 6000

void Connect_With_Server(int Socket_File_Descriptor){
	char Menu[1000], Message[1000], User_Input[1000], choice;
	ssize_t Bytes_Read, Read_Status, Bytes_Written;
	
	//Login Check
	do{
		bzero(User_Input, sizeof(User_Input));
		Bytes_Read = read(Socket_File_Descriptor, Message, sizeof(Message)); 
		printf("\n%s", Message);
		if(Bytes_Read == 0)
			break;
		scanf("%s", User_Input);
		
		Bytes_Written = write(Socket_File_Descriptor, User_Input, 1000);
		if(Bytes_Written == -1){
			perror("Error while sending data to server, Please try later");
			exit(0);
		}
	}while(Bytes_Read>0);
	
	do{
		bzero(Menu, sizeof(Menu));
		Read_Status = read(Socket_File_Descriptor, Menu, sizeof(Menu));  /* Read Menu from Server.c->Admin.h/Faculty.h/Student.h file*/
		if(Read_Status == -1)
			perror("Error while reading Admin Menu from Server");
		else if(Read_Status == 0)
			printf("\nUnable to read Menu sent by server");
		else{
			Bytes_Read = write(1, Menu, strlen(Menu));  /* Writing MENU to the terminal */ 
			if(Bytes_Read == -1)
				printf("\nUnable to read Menu sent by Server");
			
			Bytes_Read = read(0, &choice, 1);
			if(Bytes_Read == -1){
				perror("Error while Reading choice written by Server.. Exiting..");
				close(Socket_File_Descriptor);
			}	
			else{
				write(Socket_File_Descriptor, &choice, 1);
				do{
					bzero(User_Input, sizeof(User_Input));
					Bytes_Read = read(Socket_File_Descriptor, Message, sizeof(Message)); 
					printf("\n%s", Message);
					if(Bytes_Read == 0)
						break;
					scanf("%s", User_Input);
					Bytes_Written = write(Socket_File_Descriptor, User_Input, 1000);
					if(Bytes_Written == -1){
						perror("Error while sending data to server, Please try later");
						exit(0);
					}
				}while(Bytes_Read>0);
			}	
		}
	}while(1);
}

int main(){
	int Socket_File_Descriptor, Connection_Status;
	ssize_t Bytes_Written;
	char choice;
	
	struct sockaddr_in Server_Address; 		/* IPv4 socket address */
	struct in_addr Socket_Address;   		/* IPv4 4-byte address : Unsigned 32-bit integer*/
	
	Server_Address.sin_family = AF_INET;
	Server_Address.sin_port = htons(PORT);
	Server_Address.sin_addr.s_addr = htonl(INADDR_ANY);

	Socket_File_Descriptor = socket(AF_INET, SOCK_STREAM, 0);			/* int socket(int domain , int type , int protocol ); */
	if(Socket_File_Descriptor == -1){
		perror("Error creating socket.. ");
		exit(0);
	}

	Connection_Status = connect(Socket_File_Descriptor, (struct sockaddr *)&Server_Address, sizeof(Server_Address)); /* int connect(int sockfd , const struct sockaddr * addr , socklen_t addrlen ); */
	if(Connection_Status == -1){
		perror("Server Down!! Please try again later..");
		close(Socket_File_Descriptor);
        exit(0);
	}
	//printf("Connection status : %d", Connection_Status);  //(Should print 0, if successful)
	
	printf("Successfully connected with the Server...\n");
	printf("\n****************WELCOME TO COURSE REGISTRATION PORTAL********************");
	printf("\n1. Admin");
	printf("\n2. Faculty");
	printf("\n3. Student");
	printf("\n4. Exit");
	printf("\nEnter login type : ");
	scanf("%c", &choice);
	//printf("\n**************************************************************************");
	Bytes_Written = write(Socket_File_Descriptor, &choice, 1);
	if(Bytes_Written == -1){
		perror("Unable to write data to server..");
		exit(0);
	}
	
	Connect_With_Server(Socket_File_Descriptor);
	close(Socket_File_Descriptor);
	
	return 0;
}
