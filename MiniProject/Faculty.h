//Function Declaration
void Add_New_Course(int Socket_Descriptor, int Login_Id);
void Remove_Offered_Course(int Socket_Descriptor, int Login_Id);
void View_Enrollment_In_Courses(int Socket_Descriptor, int Login_Id);
void Password_Change1(int Socket_Descriptor, int Login_Id);

void Connect_With_Faculty(int Socket_Descriptor){
	int User_choice, Login_Id;
	ssize_t Write_Status, Bytes_Read;
	char Write_Buffer[1000], choice[100];
	Login_Id = Login_Check(Socket_Descriptor, 2);
	
	while(1){
	/* char *strcat(char *destination, const char *source) */
		bzero(Write_Buffer, sizeof(Write_Buffer));
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
					Add_New_Course(Socket_Descriptor, Login_Id);
					break;
				case 2:
					Remove_Offered_Course(Socket_Descriptor, Login_Id);
					break;
				case 3:
					View_Enrollment_In_Courses(Socket_Descriptor, Login_Id);
					break;
				case 4:
					Password_Change1(Socket_Descriptor, Login_Id);
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

void Add_New_Course(int Socket_Descriptor, int Login_Id){
	ssize_t Write_Status, Read_Status;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	struct Course details, previous_details;
	
	int File_Descriptor = open("Course.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Course.txt file");
		
	int position = lseek(File_Descriptor, 0, SEEK_SET);
	Read_Status = read(File_Descriptor, &Buffer, 1);
	if(Read_Status == 0)					//File is Empty
		details.Course_Id = 1;
	else{
		lseek(File_Descriptor, -1 * (sizeof(struct Course)), SEEK_END);
		read(File_Descriptor, &(previous_details), sizeof(struct Course));
		details.Course_Id = previous_details.Course_Id + 1;
	}
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Course Name : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));
	strcpy(details.Course_Name, Read_Buffer);
	
	bzero(Write_Buffer, sizeof(Write_Buffer));  
	strcat(Write_Buffer, "Enter Maximum number of seats : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));
	details.Max_Seats = atoi(Read_Buffer);	
	details.Seats_Left = atoi(Read_Buffer);
	
	details.Faculty_Id = Login_Id;
	
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	fcntl(File_Descriptor, F_SETLKW, &lock);
	//Writing Fetched data to the Faculty.txt file
	lseek(File_Descriptor, 0, SEEK_END);
	write(File_Descriptor, &(details), sizeof(details));
	lock.l_type = F_UNLCK;
	fcntl(File_Descriptor, F_SETLKW, &lock);
	
	printf("\nFollowing details have been added to the file : ");
	printf("\nFaculty Id : %d", details.Faculty_Id);
	printf("\nMaximum Seats : %d", details.Max_Seats);
	printf("\nSeats Left : %d", details.Seats_Left);
	printf("\nCourse Id: %d", details.Course_Id);
	printf("\nCourse Name : %s", details.Course_Name);
}

void Remove_Offered_Course(int Socket_Descriptor, int Login_Id){   //Not working
	ssize_t Write_Status, Read_Status, Bytes_Read;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	int Id;
	struct Course details, File_details;
	
	int File_Descriptor = open("Course.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Teach.txt file");
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Course ID : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));
	Id = atoi(Read_Buffer);
	
	//Checking if Course ID is valid & no one is enrolled
	if(Id != 1)
		lseek(File_Descriptor, (Id-1) * (sizeof(struct Course)), SEEK_SET);
	else
		lseek(File_Descriptor, 0, SEEK_SET);
	
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(File_Descriptor, &File_details, sizeof(struct Course));
	
	if(File_details.Course_Id != Id){
		bzero(Write_Buffer, sizeof(Write_Buffer));
		strcat(Write_Buffer, "Course ID invalid ! Press any key to continue..");
		Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
		Check_Write_Status(Write_Status);
		bzero(Read_Buffer, sizeof(Read_Buffer));
		Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));	 //Dummy Read
	}
	else{
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = 0;
		lock.l_len = 0;
		lock.l_pid = getpid();
		fcntl(File_Descriptor, F_SETLKW, &lock);
		
		int position = lseek(File_Descriptor, 0, SEEK_SET);
		Read_Status = read(File_Descriptor, &Buffer, 1);
		if(Read_Status == 0){					//File is Empty
			strcat(Write_Buffer, "File is empty, exiting.. Press any key to continue..");
			Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
			Check_Write_Status(Write_Status);
			
			read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));	 //Dummy Read
		}
		else{
			int removed = 0;
			struct Course Temporary_Record;  
			bzero(Read_Buffer, sizeof(Read_Buffer));  
			while(Bytes_Read = read(File_Descriptor, &Temporary_Record, sizeof(struct Course)) > 0){   
				if(Temporary_Record.Faculty_Id == details.Faculty_Id && Temporary_Record.Course_Id == details.Course_Id){
					lseek(File_Descriptor, -1 * (sizeof(struct Course)), SEEK_CUR);
					removed = 1;
				}
				else{
					bzero(Read_Buffer, sizeof(Read_Buffer));
					write(File_Descriptor, &Temporary_Record, sizeof(struct Course));
					bzero(Write_Buffer, sizeof(Write_Buffer));
					Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));	 //Dummy Read
				}
			}
			lock.l_type = F_UNLCK;
			fcntl(File_Descriptor, F_SETLKW, &lock);
			if(removed == 1){
				bzero(Write_Buffer, sizeof(Write_Buffer));
				strcat(Write_Buffer, "Record removed successfully!! Press any key to continue..");
				Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
				Check_Write_Status(Write_Status);
				
				bzero(Read_Buffer, sizeof(Read_Buffer));
				Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));	 //Dummy Read

			}
			else{
				bzero(Write_Buffer, sizeof(Write_Buffer));
				strcat(Write_Buffer, "Record not found.. Press any key to continue..");
				Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
				Check_Write_Status(Write_Status);	
				
				bzero(Read_Buffer, sizeof(Read_Buffer));
				Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));	 //Dummy Read
			}
		}
	}
}

void View_Enrollment_In_Courses(int Socket_Descriptor, int Login_Id){
	ssize_t Write_Status, Read_Status, Bytes_Read;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	int Id;
	struct Course details;
	struct Enroll details1;

	int File_Descriptor = open("Course.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Course.txt file");
	struct flock lock;
	lock.l_type = F_RDLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	fcntl(File_Descriptor, F_SETLKW, &lock);
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "COURSE ID  STUDENT ID  ENROLLMENT ID");
	Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
	
	lseek(File_Descriptor, 0, SEEK_SET);
	bzero(Read_Buffer, sizeof(Read_Buffer));  
	bzero(Write_Buffer, sizeof(Write_Buffer)); 
	while((Bytes_Read = read(File_Descriptor, &details, sizeof(struct Course))) > 0){  
		if(details.Faculty_Id == Login_Id){
			Id = details.Course_Id;
			int File_Descriptor1 = open("Enroll.txt", O_RDWR);
			if(File_Descriptor1 == -1)
				perror("Error opening Enroll.txt file");
				
			struct flock lock1;
			lock1.l_type = F_RDLCK;
			lock1.l_whence = SEEK_SET;
			lock1.l_start = 0;
			lock1.l_len = 0;
			lock1.l_pid = getpid();
			fcntl(File_Descriptor, F_SETLKW, &lock);
			while((Bytes_Read = read(File_Descriptor1, &details1, sizeof(struct Enroll))) > 0){  
				if(details1.Course_Id == Id){
					bzero(Write_Buffer, sizeof(Write_Buffer));
					snprintf(Write_Buffer, sizeof(struct Course),"%d  %d  %d", details1.Course_Id, details1.Student_Id, details1.Enrollment_Status);
					Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(Write_Buffer));
					read(Socket_Descriptor, Read_Buffer, sizeof(Write_Buffer));      //Dummy Read
					Check_Write_Status(Write_Status);
				}
				bzero(Read_Buffer, sizeof(Read_Buffer));
			}
			lock1.l_type = F_UNLCK;
			fcntl(File_Descriptor, F_SETLKW, &lock1);
		}
		bzero(Read_Buffer, sizeof(Read_Buffer));
	}
	lock.l_type = F_UNLCK;
	fcntl(File_Descriptor, F_SETLKW, &lock);

}

void Password_Change1(int Socket_Descriptor, int Login_Id){
	char Password[100], Write_Buffer[1000], Read_Buffer[1000];
	struct Faculty details;

	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "\nEnter new Password : ");
	write(Socket_Descriptor, Write_Buffer, sizeof(struct Faculty));
	bzero(Read_Buffer, sizeof(Read_Buffer));
	read(Socket_Descriptor, Read_Buffer, 1000);
	strcpy(Password, Read_Buffer);
	
	int File_Descriptor = open("Faculty.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Faculty.txt file");
	if(Login_Id != 1)
		lseek(File_Descriptor, (Login_Id-1) * (sizeof(struct Faculty)), SEEK_SET);
	else
		lseek(File_Descriptor, 0, SEEK_SET);
	read(File_Descriptor, &details, sizeof(struct Faculty));
	strcpy(details.Faculty_Password, Password);
	
	struct flock lock1;
	lock1.l_type = F_WRLCK;
	lock1.l_whence = SEEK_SET;
	lock1.l_start = (Login_Id-1)*(sizeof(struct Faculty));
	lock1.l_len = (sizeof(struct Faculty));
	lock1.l_pid = getpid();
	fcntl(File_Descriptor, F_SETLKW, &lock1);
	if(Login_Id != 1)
		lseek(File_Descriptor, (Login_Id-1) * (sizeof(struct Student)), SEEK_SET);
	else
		lseek(File_Descriptor, 0, SEEK_SET);
	write(File_Descriptor, &details, sizeof(struct Faculty));
	lock1.l_type = F_UNLCK;
	fcntl(File_Descriptor, F_SETLKW, &lock1);	

	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Password Updated Successfully!! ");
	write(Socket_Descriptor, Write_Buffer, sizeof(Write_Buffer));
	bzero(Read_Buffer, sizeof(Read_Buffer));
	read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));   //Dummy Read

}

