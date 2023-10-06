#include <stdio.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <string.h>
#include <stdlib.h>



void Connect_With_Admin(int Socket_Descriptor){
	int User_choice;
	ssize_t Write_Status, Bytes_Read;
	char Write_Buffer[1000], choice[100];
	//Credentials_Check();
	do{
	/* char *strcat(char *destination, const char *source) */
	strcat(Write_Buffer, "\n*************WELCOME TO ADMIN PORTAL*************");
	strcat(Write_Buffer, "\n1. Add new Student");
	strcat(Write_Buffer, "\n2. Add new Faculty");
	strcat(Write_Buffer, "\n3. Activate Student");
	strcat(Write_Buffer, "\n4. Deactivate Student");
	strcat(Write_Buffer, "\n5. Update Student details");
	strcat(Write_Buffer, "\n6. Update Faculty details");
	strcat(Write_Buffer, "\n7. Exit");
	
	Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(Write_Buffer));
	if(Write_Status == -1)
		perror("Error while writing Admin Menu to Client..");
	else{
		bzero(choice, sizeof(choice));
		Bytes_Read = read(Socket_Descriptor, choice, sizeof(choice));
		User_choice = atoi(choice);
		switch(User_choice){
			case 1:	
				printf("\n Reached here");
				break;
			case 2:
				
				break;
			case 3:
				
				break;
			case 4:
				
				break;
			case 5:
				
				break;
			case 6:
				
				break;
			case 7:
				
				break;
			default:
				printf("\nEnter valid choice");
				close(Socket_Descriptor);
		}
	}
	}while(1);
}

//boolean Credentials_Check(){ }
