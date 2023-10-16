//Function Declaration
void Add_New_Course(int Socket_Descriptor);
void Remove_Offered_Course(int Socket_Descriptor);
void View_Enrollment_In_Courses(int Socket_Descriptor);

void Connect_With_Faculty(int Socket_Descriptor){
	int User_choice, Login_Id;
	ssize_t Write_Status, Bytes_Read;
	char Write_Buffer[1000], choice[100];
	Login_Id = Login_Check(Socket_Descriptor, 2);
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	while(1){
	/* char *strcat(char *destination, const char *source) */
		strcat(Write_Buffer, "\n*************WELCOME TO FACULTY PORTAL*************");
		strcat(Write_Buffer, "\n1. Add new Course");
		strcat(Write_Buffer, "\n2. Remove offered Course");
		strcat(Write_Buffer, "\n3. View enrollments in Courses");
		strcat(Write_Buffer, "\n4. Password Change");
		strcat(Write_Buffer, "\n5. Exit");
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
					//Add_New_Course(Socket_Descriptor);
					break;
				case 2:
					//Remove_Offered_Course(Socket_Descriptor);
					break;
				case 3:
					//View_Enrollment_In_Courses(Socket_Descriptor);
					break;
				case 4:
					//Password_Change(Socket_Descriptor);
					break;
				case 5:
					close(Socket_Descriptor);
					break;
				default:
					bzero(Write_Buffer, sizeof(Write_Buffer));
					strcat(Write_Buffer, "Enter valid choice : ");
					Write_Status = write(Socket_Descriptor, Write_Buffer, strlen(Write_Buffer));
					Check_Write_Status(Write_Status);
			}
		}
	}
}
/*
void Add_New_Course(int Socket_Descriptor){
	ssize_t Write_Status, Read_Status;
	char Read_Buffer[1000], Write_Buffer[1000];
	struct Teach NewTeach;
	
	int File_Descriptor = open("Course.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Course.txt file");
		
	//lseek(File_Descriptor, -1 * (sizeof(struct Faculty)), SEEK_END);

	bzero(Write_Buffer, sizeof(Write_Buffer));  //to be fetched from faculty file based on ID entered
	strcat(Write_Buffer, "Enter Faculty Name : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));
	strcpy(NewTeach.Faculty_Name, Read_Buffer);
	
	bzero(Write_Buffer, sizeof(Write_Buffer));  
	strcat(Write_Buffer, "Enter Course ID : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));
	NewTeach.Course_Id = atoi(Read_Buffer);	
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Course Name : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));
	strcpy(NewTeach.Course_Name, Read_Buffer);
	
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	fcntl(File_Descriptor, F_SETLKW, &lock);
	//Writing Fetched data to the Faculty.txt file
	lseek(File_Descriptor, 0, SEEK_END);
	write(File_Descriptor, &(NewTeach), sizeof(NewTeach));
	lock.l_type = F_UNLCK;
	fcntl(File_Descriptor, F_SETLKW, &lock);
	
	printf("\nFollowing details have been added to the file : ");
	printf("\nFaculty Id : %d", NewTeach.Faculty_Id);
	printf("\nFaculty Name : %s", NewTeach.Faculty_Name);
	printf("\nCourse Id: %d", NewTeach.Course_Id);
	printf("\nCourse Name : %s", NewTeach.Course_Name);
}

void Remove_Offered_Course(int Socket_Descriptor){
	ssize_t Write_Status, Read_Status, Bytes_Read;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	struct Teach NewTeach;
	
	int File_Descriptor = open("Teach.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Teach.txt file");
		
	bzero(Write_Buffer, sizeof(Write_Buffer));   //to be removed
	strcat(Write_Buffer, "Enter Faculty ID : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));
	NewTeach.Faculty_Id = atoi(Read_Buffer);
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Course ID : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));
	NewTeach.Course_Id = atoi(Read_Buffer);
	
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	fcntl(File_Descriptor, F_SETLKW, &lock);
	//Writing Fetched data to the Faculty.txt file
	
	int position = lseek(File_Descriptor, 0, SEEK_SET);
	Read_Status = read(File_Descriptor, &Buffer, 1);
	if(Read_Status == 0){					//File is Empty
		strcat(Write_Buffer, "File is empty, exiting..");
		Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
		Check_Write_Status(Write_Status);
	}
	
	int removed = 0;
	struct Teach Temporary_Record;  
	bzero(Read_Buffer, sizeof(Read_Buffer));  
	bzero(Write_Buffer, sizeof(Write_Buffer)); 
	while(Bytes_Read = read(File_Descriptor, &Temporary_Record, sizeof(struct Teach)) > 0){   //Logic for 1 record to be verified
		if(Temporary_Record.Faculty_Id == NewTeach.Faculty_Id && Temporary_Record.Course_Id == NewTeach.Course_Id){
			lseek(File_Descriptor, -1 * (sizeof(struct Teach)), SEEK_CUR);
			removed = 1;
		}
		else
			write(File_Descriptor, &Temporary_Record, sizeof(struct Teach));
		bzero(Read_Buffer, sizeof(Read_Buffer));
		bzero(Write_Buffer, sizeof(Write_Buffer));
	}
	
	if(removed == 1){
		lock.l_type = F_UNLCK;
		fcntl(File_Descriptor, F_SETLKW, &lock);
		bzero(Write_Buffer, sizeof(Write_Buffer));
		strcat(Write_Buffer, "Record removed successfully!! : ");
		Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
		Check_Write_Status(Write_Status);
	}
	else{
		lock.l_type = F_UNLCK;
		fcntl(File_Descriptor, F_SETLKW, &lock);
		bzero(Write_Buffer, sizeof(Write_Buffer));
		strcat(Write_Buffer, "Record not found");
		Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
		Check_Write_Status(Write_Status);	
	}
}

void View_Enrollment_In_Courses(int Socket_Descriptor){
	

}
*/
