#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void Connect_With_Admin(int Socket_Descriptor){

	int Write_Status;
	char Write_Buffer[1000];
	
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
	if(Write_Status == -1){
		perror("Error while writing Admin Menu to Client..");
	else{
	
	}
	return 0;
}