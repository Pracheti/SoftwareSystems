#include "Common.h"

//Function Declaration
void Add_New_Student(int Socket_Descriptor);

void Connect_With_Admin(int Socket_Descriptor){
	int User_choice;
	ssize_t Write_Status, Bytes_Read;
	char Write_Buffer[1000], choice[100];
	//Credentials_Check();
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
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
		
		Write_Status = write(Socket_Descriptor, Write_Buffer, strlen(Write_Buffer));
		if(Write_Status == -1)
			perror("Error while writing Admin Menu to Client..");
		else{
			bzero(choice, sizeof(choice));
			Bytes_Read = read(Socket_Descriptor, choice, sizeof(choice));
			User_choice = atoi(choice);
			switch(User_choice){
				case 1:	
					Add_New_Student(Socket_Descriptor);
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
					close(Socket_Descriptor);
					break;
				default:
					printf("\nEnter valid choice");
			}
		}
	}while(1);
}

void Add_New_Student(int Socket_Descriptor){
	ssize_t Write_Status, Read_Status;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer_1;
	int Buffer;
	struct Student details;
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "\nEnter Student Name");
	Write_Status = write(Socket_Descriptor, Write_Buffer, strlen(Write_Buffer));
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
	Read_Status = read(Socket_Descriptor, details.Name, 100);
	
	/*bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "\nEnter Student Age");
	Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(Buffer));
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
	Read_Status = read(Socket_Descriptor, details.Age, sizeof(Buffer));
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "\nEnter Student Gender");
	Write_Status = write(Socket_Descriptor, Buffer_1, strlen(Buffer_1));
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
	Read_Status = read(Socket_Descriptor, details.Gender, sizeof(Buffer_1));*/
}
