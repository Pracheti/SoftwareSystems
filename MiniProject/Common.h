#include "Constants.h"

//Structure Declaration
struct Student{
	int Student_Id, Age, Year, Status;  //1=Activate, 0=Deactivate
	char Student_Name[100], Student_Password[100];
};

struct Faculty{
	int Faculty_Id, Age;
	char Faculty_Name[100], Faculty_Password[100];   
};

struct Enroll{
	int Course_Id, Student_Id, Enrollment_Status;    
};

struct Course{
	int Course_Id, Max_Seats, Seats_Left, Faculty_Id;
	char Course_Name[100];
};

//Function Declaration
void Check_Write_Status(int Write_Status){
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
}

//Login Function(Role : 1=Admin, 2=Faculty, 3=Student)
int Login_Check(int Socket_Descriptor, int Role){
	ssize_t Write_Status, Bytes_Read;
	char Write_Buffer[1000], Read_Buffer[1000], Password[1000];
	int Id, UserId_Matched = 0, Password_Matched = 0;
	
	while(UserId_Matched == 0){
		bzero(Write_Buffer, sizeof(Write_Buffer));
		strcat(Write_Buffer, "Enter UserID : ");
		Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
		Check_Write_Status(Write_Status);
		
		bzero(Read_Buffer, sizeof(Read_Buffer)); 
		Bytes_Read = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));  //Collect ID from Client  (use of strlen() doesn't work here)
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
					Bytes_Read = read(Socket_Descriptor, &Read_Buffer, sizeof(Write_Buffer));  //Collect Password from Client
					strcpy(Password, Read_Buffer);
					if(strcmp(Admin_Password, Password) == 0)
						Password_Matched = 1;
					else{
						Password_Matched = 0;
						bzero(Write_Buffer, sizeof(Write_Buffer));
						strcat(Write_Buffer, "Entered Password is wrong! Press any key to continue..");	
						Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
						Check_Write_Status(Write_Status);
						
						read(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));  //Dummy read
					}
				}
			}
			else{
				bzero(Write_Buffer, sizeof(Write_Buffer));
				strcat(Write_Buffer, "Entered UserId is wrong! ");
				//Bytes_Read = read(Socket_Descriptor, &Read_Buffer, 1000);   //Dummy Read
			}
		}
	
		else if(Role == 2){					//Faculty Login
			int File_Descriptor = open("Faculty.txt", O_RDONLY);
			if(File_Descriptor == -1)
				perror("Error opening Faculty.txt file");
			else{
				struct Faculty details;
				if(Id != 1)
					lseek(File_Descriptor, (Id-1) * (sizeof(struct Faculty)), SEEK_SET);
				else
					lseek(File_Descriptor, 0, SEEK_SET);
				Bytes_Read = read(File_Descriptor, &details, sizeof(struct Faculty));
				if(Bytes_Read != 0 && details.Faculty_Id == Id){
					UserId_Matched = 1;
					while(Password_Matched == 0){
						bzero(Write_Buffer, sizeof(Write_Buffer));
						strcat(Write_Buffer, "Enter Password : ");
						Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
						Check_Write_Status(Write_Status);
						
						bzero(Read_Buffer, sizeof(Read_Buffer)); 
						Bytes_Read = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));  //Collect Password from Client
						strcpy(Password, Read_Buffer);
						if(strcmp(details.Faculty_Password, Password) == 0)
							Password_Matched = 1;
						else{
							Password_Matched = 0;
							bzero(Write_Buffer, sizeof(Write_Buffer));
							strcat(Write_Buffer, "Entered Password is wrong! Press any key to continue..");	
							Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
							Check_Write_Status(Write_Status);
							
							read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));  //Dummy read
						}	
					}	
				}
			}
		}
		else{			//Student Login
			int File_Descriptor = open("Student.txt", O_RDONLY);
			if(File_Descriptor == -1)
				perror("Error opening Student.txt file");
			else{
				struct Student details;
				if(Id != 1)
					lseek(File_Descriptor, (Id-1) * (sizeof(struct Student)), SEEK_SET);
				else
					lseek(File_Descriptor, 0, SEEK_SET);
				Bytes_Read = read(File_Descriptor, &details, sizeof(struct Student));
				if(Bytes_Read != 0 && details.Student_Id == Id){
					UserId_Matched = 1;
					while(Password_Matched == 0){
						bzero(Write_Buffer, sizeof(Write_Buffer));
						strcat(Write_Buffer, "Enter Password : ");
						Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
						Check_Write_Status(Write_Status);
						
						bzero(Read_Buffer, sizeof(Read_Buffer)); 
						Bytes_Read = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));  //Collect Password from Client
						strcpy(Password, Read_Buffer);
						if(strcmp(details.Student_Password, Password) == 0)
							Password_Matched = 1;
						else{
							Password_Matched = 0;
							bzero(Write_Buffer, sizeof(Write_Buffer));
							strcat(Write_Buffer, "Entered Password is wrong! Press any key to continue..");	
							Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
							Check_Write_Status(Write_Status);
							
							read(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));  //Dummy read
						}	
					}	
				}
			}
		}
	}
	return Id;
}
