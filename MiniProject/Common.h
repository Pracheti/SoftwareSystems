#include "Constants.h"

//Structure Declaration
struct Student{
	int Student_Id, Age, Year, Status;  //1=Activate, 0=Deactivate
	char Student_Name[100], Student_Password[100];
};

struct Faculty{
	int Faculty_Id, Age;
	int Status;
	char Faculty_Name[100], Course[100], Faculty_Password[100];   //Course needs to be removed
};

struct Enroll{
	int Course_Id, Student_Id;    //EnrollId needs to be removed
};

struct Course{
	int Course_Id, Max_Seats, Seats_Left;
	char Course_Name[100], Faculty_Name[100];
};

struct Teach{
	int Faculty_Id, Course_Id;
	char Faculty_Name[100], Course_Name[100];
};

//Function Declaration
void Check_Write_Status(int Write_Status){
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
}

//Login Function(Role : 1=Admin, 2=Faculty, 3=Student)
void Login_Check(int Socket_Descriptor, int Role){
	ssize_t Write_Status, Bytes_Read;
	char Write_Buffer[1000], Read_Buffer[1000], Password[1000];
	int Id, UserId_Matched = 0, Password_Matched = 0;
	
	while(UserId_Matched == 0){
		bzero(Write_Buffer, sizeof(Write_Buffer));
		strcat(Write_Buffer, "Enter UserID : ");
		Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
		Check_Write_Status(Write_Status);
		
		bzero(Read_Buffer, sizeof(Read_Buffer)); 
		Bytes_Read = read(Socket_Descriptor, &Read_Buffer, 1000);  //Collect ID from Client  (use of strlen() doesn't work here)
		Id = atoi(Read_Buffer);
		
		if(Role == 1){   //Admin Login
			if(Id == Admin_Id){
				UserId_Matched = 1;
				while(Password_Matched == 0){
					bzero(Write_Buffer, sizeof(Write_Buffer));
					strcat(Write_Buffer, "Enter Password : ");
					Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
					Check_Write_Status(Write_Status);
					
					bzero(Read_Buffer, sizeof(Read_Buffer)); 
					Bytes_Read = read(Socket_Descriptor, &Read_Buffer, 1000);  //Collect Password from Client
					strcpy(Password, Read_Buffer);
					if(strcmp(Admin_Password, Password) == 0)
						Password_Matched = 1;
					else{
						Password_Matched = 0;
						bzero(Write_Buffer, sizeof(Write_Buffer));
						strcat(Write_Buffer, "\nEntered UserId is wrong! ");	

						//Bytes_Read = read(Socket_Descriptor, &Read_Buffer, 1000); //Dummy Read
					}
				}
			}
			else{
				bzero(Write_Buffer, sizeof(Write_Buffer));
				strcat(Write_Buffer, "\nEntered UserId is wrong! ");
				//Bytes_Read = read(Socket_Descriptor, &Read_Buffer, 1000);   //Dummy Read
			}
		}
		/*
		else if(){
		
		}
		
		else{
		
		}
		*/
	}
}
