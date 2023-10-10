#include <stdbool.h>
#include "Common.h"

//Function Declaration
void Add_New_Student(int Socket_Descriptor);
void Add_New_Faculty(int Socket_Descriptor);
void Activate_Student(int Socket_Descriptor);
void Deactivate_Student(int Socket_Descriptor);
void Update_Student(int Socket_Descriptor);
void Update_Faculty(int Socket_Descriptor);


void Connect_With_Admin(int Socket_Descriptor){
	int User_choice;
	ssize_t Write_Status, Bytes_Read;
	char Write_Buffer[1000], choice[100];
	//Credentials_Check();
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	//do{
	/* char *strcat(char *destination, const char *source) */
		strcat(Write_Buffer, "\n*************WELCOME TO ADMIN PORTAL*************");
		strcat(Write_Buffer, "\n1. Add new Student");
		strcat(Write_Buffer, "\n2. Add new Faculty");
		strcat(Write_Buffer, "\n3. Activate Student");
		strcat(Write_Buffer, "\n4. Deactivate Student");
		strcat(Write_Buffer, "\n5. Update Student details");
		strcat(Write_Buffer, "\n6. Update Faculty details");
		strcat(Write_Buffer, "\n7. Exit");
		strcat(Write_Buffer, "\nEnter Your Choice : ");
		
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
					Add_New_Faculty(Socket_Descriptor);
					break;
				case 3:
					Activate_Student(Socket_Descriptor);
					break;
				case 4:
					Deactivate_Student(Socket_Descriptor);
					break;
				case 5:
					Update_Student(Socket_Descriptor);
					break;
				case 6:
					Update_Faculty(Socket_Descriptor);
					break;
				case 7:
					close(Socket_Descriptor);
					break;
				default:
					printf("\nEnter valid choice");
			}
		}
	//}while(User_choice != 7);
}

void Add_New_Student(int Socket_Descriptor){
	ssize_t Write_Status, Read_Status;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	struct Student details;
	
	int File_Descriptor = open("Student.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Student.txt file");
		
	//Checking if file is empty & fetching value of Id
	int position = lseek(File_Descriptor, 0, SEEK_SET);
	if(position == 0){
		Read_Status = read(File_Descriptor, &Buffer, 1);
		if(Read_Status == 0)					//File is Empty
			details.Id = 1;
		else{
			lseek(File_Descriptor, -1 * (sizeof(struct Student)), SEEK_END);
			details.Id = read(File_Descriptor, (int*) &Buffer, 1);
			details.Id += 1;
		}
	}
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Student Name : ");
	Write_Status = write(Socket_Descriptor, Write_Buffer, strlen(Write_Buffer));
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
	Read_Status = read(Socket_Descriptor, (char*)details.Name, 100);
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Student Age : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
	details.Age = atoi(Read_Buffer);
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Student Year : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
	details.Year = atoi(Read_Buffer);
	
	details.Status = true;
	
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = -1 * (sizeof(struct Student));
	lock.l_len = (sizeof(struct Student));
	lock.l_pid = getpid();
	fcntl(File_Descriptor, F_SETLKW, &lock);
	//Writing Fetched data to the Student.txt file
	lseek(File_Descriptor, 0, SEEK_END);
	write(File_Descriptor, &(details), sizeof(details));
	lock.l_type = F_UNLCK;
	fcntl(File_Descriptor, F_SETLKW, &lock);
	
	printf("\nFollowing details have been added to the file : ");
	printf("\nId : %d", details.Id);
	printf("\nName : %s", details.Name);
	printf("\nAge : %d", details.Age);
	printf("\nYear : %d", details.Year);
	printf("\nActivation Status : %d", details.Status);
}

void Add_New_Faculty(int Socket_Descriptor){
	ssize_t Write_Status, Read_Status;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	struct Faculty details;
	
	int File_Descriptor = open("Faculty.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Faculty.txt file");
		
	//Checking if file is empty & fetching value of Id
	int position = lseek(File_Descriptor, 0, SEEK_SET);
	if(position == 0){
		Read_Status = read(File_Descriptor, &Buffer, 1);
		if(Read_Status == 0)					//File is Empty
			details.Id = 1;
		else{
			lseek(File_Descriptor, -1 * (sizeof(struct Faculty)), SEEK_END);
			details.Id = read(File_Descriptor, (int*) &Buffer, 1);
			details.Id += 1;
		}
	}
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Faculty Name : ");
	Write_Status = write(Socket_Descriptor, Write_Buffer, strlen(Write_Buffer));
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
	Read_Status = read(Socket_Descriptor, (char*)details.Name, 100);
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Faculty Age : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
	details.Age = atoi(Read_Buffer);
	
	details.Status = true;
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Course taught : ");
	Write_Status = write(Socket_Descriptor, Write_Buffer, strlen(Write_Buffer));
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
	Read_Status = read(Socket_Descriptor, (char*)details.Course, 100);
	
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = -1 * (sizeof(struct Faculty));
	lock.l_len = (sizeof(struct Faculty));
	lock.l_pid = getpid();
	fcntl(File_Descriptor, F_SETLKW, &lock);
	//Writing Fetched data to the Student.txt file
	lseek(File_Descriptor, 0, SEEK_END);
	write(File_Descriptor, &(details), sizeof(details));
	lock.l_type = F_UNLCK;
	fcntl(File_Descriptor, F_SETLKW, &lock);
	
	printf("\nFollowing details have been added to the file : ");
	printf("\nId : %d", details.Id);
	printf("\nName : %s", details.Name);
	printf("\nAge : %d", details.Age);
	printf("\nCourse : %s", details.Course);
	printf("\nActivation Status : %d", details.Status);
}

void Activate_Student(int Socket_Descriptor){
	ssize_t Write_Status, Read_Status;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	int id;
	struct Student details;
	
	int File_Descriptor = open("Student.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Student.txt file");

	int position = lseek(File_Descriptor, 0, SEEK_SET);
	if(position == 0){
		Read_Status = read(File_Descriptor, &Buffer, 1);
		if(Read_Status == 0){					//File is Empty
			strcat(Write_Buffer, "File is empty, exiting..");
			close(Socket_Descriptor);
		}
	}
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "\nEnter Student Id that needs to be activated : ");
	Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(struct Student));
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));  //Collected Student ID from Client
	id = atoi(Read_Buffer);
	
	File_Descriptor = open("Student.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Faculty.txt file");
		
	position = lseek(File_Descriptor, 0, SEEK_SET);
	int reached = 0;
	do{
		Read_Status = read(File_Descriptor, &details, sizeof(struct Student));
		if(details.Id == id){
			if(details.Status == false){
				details.Status == true;
				bzero(Write_Buffer, sizeof(Write_Buffer));
				strcat(Write_Buffer, "\nThe student is now activated!!");	
				reached = 1;
				break;
			}
			else{
				bzero(Write_Buffer, sizeof(Write_Buffer));
				strcat(Write_Buffer, "\nThe activation status of student is already True!!");	
				reached = 1;
				break;
			}
		}	
	}while(Read_Status != 0);
	
	if(reached == 0){
		bzero(Write_Buffer, sizeof(Write_Buffer));
		strcat(Write_Buffer, "\nId not found, Enter valid ID");	
	}
	else{
		write(Socket_Descriptor, Write_Buffer, strlen(Write_Buffer));
	}
}

void Deactivate_Student(int Socket_Descriptor){
	ssize_t Write_Status, Read_Status;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	int id;
	struct Student details;
	
	int File_Descriptor = open("Student.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Student.txt file");

	int position = lseek(File_Descriptor, 0, SEEK_SET);
	if(position == 0){
		Read_Status = read(File_Descriptor, &Buffer, 1);
		if(Read_Status == 0){					//File is Empty
			strcat(Write_Buffer, "File is empty, exiting..");
			close(Socket_Descriptor);
		}
	}
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "\nEnter Student Id that needs to be deactivated : ");
	Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(struct Student));
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));  //Collected Student ID from Client
	id = atoi(Read_Buffer);
	
	File_Descriptor = open("Student.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Student.txt file");
		
	position = lseek(File_Descriptor, 0, SEEK_SET);
	int reached = 0;
	do{
		Read_Status = read(File_Descriptor, &details, sizeof(struct Student));
		if(details.Id == id){
			if(details.Status == true){
				strcat(Write_Buffer, "\nThe student is deactivated!!");	
				details.Status == false;
				reached = 1;
				break;
			}
			else{
				bzero(Write_Buffer, sizeof(Write_Buffer));
				strcat(Write_Buffer, "\nThe activation status of student is already false!!");	
				reached = 1;
				break;
			}
		}	
	}while(Read_Status != 0);
	
	if(reached == 0){
		bzero(Write_Buffer, sizeof(Write_Buffer));
		strcat(Write_Buffer, "\nId not found, Enter valid ID");	
	}
	else
		write(Socket_Descriptor, Write_Buffer, strlen(Write_Buffer));
}

void Update_Student(int Socket_Descriptor){
	ssize_t Write_Status, Read_Status;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	int id;
	struct Student details;
	
	int File_Descriptor = open("Student.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Student.txt file");

	int position = lseek(File_Descriptor, 0, SEEK_SET);
	if(position == 0){
		Read_Status = read(File_Descriptor, &Buffer, 1);
		if(Read_Status == 0){					//File is Empty
			strcat(Write_Buffer, "File is empty, exiting..");
			close(Socket_Descriptor);
		}
	}
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "\nEnter ID of student that needs to be updated : ");
	Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(struct Student));
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));  //Collected Student ID from Client
	id = atoi(Read_Buffer);
	
	File_Descriptor = open("Student.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Student.txt file");
		
	position = lseek(File_Descriptor, 0, SEEK_SET);
	int reached = 0;
	do{
		Read_Status = read(File_Descriptor, &details, sizeof(struct Student));
		if(details.Id == id){
			reached = 1;
			bzero(Write_Buffer, sizeof(Write_Buffer));
			strcat(Write_Buffer, "\n1. Name\n2. Age\n3. Year\n 4. Status");
			strcat(Write_Buffer, "\n Enter your choice : ");
			Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(struct Student));
				
			int User_choice;
			ssize_t Bytes_Read;
			char choice[100];
	
			bzero(choice, sizeof(choice));
			Bytes_Read = read(Socket_Descriptor, choice, sizeof(choice));
			if(Bytes_Read == -1){
				perror("Error while Reading choice sent by Client.. Exiting..");
				close(Socket_Descriptor);
			}	
			else{
				User_choice = atoi(choice);
				switch(User_choice){
					case 1: 
						bzero(Write_Buffer, sizeof(Write_Buffer));
						strcat(Write_Buffer, "\n Enter new Name : ");
						write(Socket_Descriptor, Write_Buffer, sizeof(struct Student));
						Read_Status = read(Socket_Descriptor, (char*)details.Name, 100);
						break;
					case 2: 
						bzero(Write_Buffer, sizeof(Write_Buffer));
						strcat(Write_Buffer, "\n Enter new Age : ");
						write(Socket_Descriptor, Write_Buffer, sizeof(struct Student));
						bzero(Read_Buffer, sizeof(Read_Buffer));
						Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
						details.Age = atoi(Read_Buffer);
						break;
					case 3:
						bzero(Write_Buffer, sizeof(Write_Buffer));
						strcat(Write_Buffer, "\n Enter new Year : ");
						write(Socket_Descriptor, Write_Buffer, sizeof(struct Student));
						bzero(Read_Buffer, sizeof(Read_Buffer));
						Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
						details.Year = atoi(Read_Buffer);
						break;
					case 4:
						bzero(Write_Buffer, sizeof(Write_Buffer));   //To be Verified
						strcat(Write_Buffer, "\n Enter new Status : ");
						write(Socket_Descriptor, Write_Buffer, sizeof(struct Student));
						bzero(Read_Buffer, sizeof(Read_Buffer));
						Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
						details.Status = Read_Buffer;        
						break;
				}
			}
		}
	}while(Read_Status != 0);
}

void Update_Faculty(int Socket_Descriptor){
	ssize_t Write_Status, Read_Status;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	int id;
	struct Faculty details;
	
	int File_Descriptor = open("Faculty.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Student.txt file");

	int position = lseek(File_Descriptor, 0, SEEK_SET);
	if(position == 0){
		Read_Status = read(File_Descriptor, &Buffer, 1);
		if(Read_Status == 0){					//File is Empty
			strcat(Write_Buffer, "File is empty, exiting..");
			close(Socket_Descriptor);
		}
	}
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "\nEnter ID of Faculty that needs to be updated : ");
	Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(struct Student));
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));  //Collected Student ID from Client
	id = atoi(Read_Buffer);
	
	File_Descriptor = open("Faculty.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Faculty.txt file");
		
	position = lseek(File_Descriptor, 0, SEEK_SET);
	int reached = 0;
	do{
		Read_Status = read(File_Descriptor, &details, sizeof(struct Faculty));
		if(details.Id == id){
			reached = 1;
			bzero(Write_Buffer, sizeof(Write_Buffer));
			strcat(Write_Buffer, "\n1. Name\n2. Age\n3. Status\n 4. Course");
			strcat(Write_Buffer, "\nEnter your choice : ");
			Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(struct Faculty));
				
			int User_choice;
			ssize_t Bytes_Read;
			char choice[100];
	
			bzero(choice, sizeof(choice));
			Bytes_Read = read(Socket_Descriptor, choice, sizeof(choice));
			if(Bytes_Read == -1){
				perror("Error while Reading choice sent by Client.. Exiting..");
				close(Socket_Descriptor);
			}	
			else{
				User_choice = atoi(choice);
				switch(User_choice){
					case 1: 
						bzero(Write_Buffer, sizeof(Write_Buffer));
						strcat(Write_Buffer, "\n Enter new Name : ");
						write(Socket_Descriptor, Write_Buffer, sizeof(struct Faculty));
						Read_Status = read(Socket_Descriptor, (char*)details.Name, 100);
						break;
					case 2: 
						bzero(Write_Buffer, sizeof(Write_Buffer));
						strcat(Write_Buffer, "\n Enter new Age : ");
						write(Socket_Descriptor, Write_Buffer, sizeof(struct Faculty));
						bzero(Read_Buffer, sizeof(Read_Buffer));
						Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
						details.Age = atoi(Read_Buffer);
						break;
					
					case 3:
						bzero(Write_Buffer, sizeof(Write_Buffer));   //To be Verified
						strcat(Write_Buffer, "\n Enter new Status : ");
						write(Socket_Descriptor, Write_Buffer, sizeof(struct Faculty));
						bzero(Read_Buffer, sizeof(Read_Buffer));
						Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
						details.Status = Read_Buffer;        
						break;
					case 4:
						bzero(Write_Buffer, sizeof(Write_Buffer));
						strcat(Write_Buffer, "\n Enter new Course : ");
						write(Socket_Descriptor, Write_Buffer, sizeof(struct Faculty));
						Read_Status = read(Socket_Descriptor, (char*)details.Course, 100);
						break;
				}
			}
		}
	}while(Read_Status != 0);
}
