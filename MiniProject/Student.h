//Function Declaration
void Enroll_New_Course(int Socket_Descriptor);
void Unenroll_Course(int Socket_Descriptor);
void View_Enrolled_Courses(int Socket_Descriptor);

void Connect_With_Student(int Socket_Descriptor){
	int User_choice;
	ssize_t Write_Status, Bytes_Read;
	char Write_Buffer[1000], choice[100];
	//Credentials_Check();
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	//do{
	/* char *strcat(char *destination, const char *source) */
		strcat(Write_Buffer, "\n*************WELCOME TO STUDENT PORTAL*************");
		strcat(Write_Buffer, "\n1. Enroll to new course");
		strcat(Write_Buffer, "\n2. Unenroll from already enrolled courses");
		strcat(Write_Buffer, "\n3. View Enrolled courses");
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
					Enroll_New_Course(Socket_Descriptor);
					break;
				case 2:
					Unenroll_Course(Socket_Descriptor);
					break;
				case 3:
					View_Enrolled_Courses(Socket_Descriptor);
					break;
				case 4:
					
					break;
				default:  
					printf("\nEnter valid choice");
			}
		}
	//}while(User_choice != 7);
}

void Enroll_New_Course(int Socket_Descriptor){
	ssize_t Write_Status, Read_Status;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	struct Enroll details;
	struct Teach Temporary_Record;
	
	int File_Descriptor = open("Teach.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Course.txt file");
		
	struct flock lock1;
	lock1.l_type = F_RDLCK;
	lock1.l_whence = SEEK_SET;
	lock1.l_start = 0;
	lock1.l_len = 0;
	lock1.l_pid = getpid();
	fcntl(File_Descriptor, F_SETLKW, &lock1);
	
	//Displaying all courses to Student
	/*while((Read_Status = read(File_Descriptor, &Temporary_Record, sizeof(struct Teach)))>0){
		bzero(Write_Buffer, sizeof(Write_Buffer));
		sprintf(Write_Buffer, "%d   %d   %s   %s\n", Temporary_Record.Faculty_Id, Temporary_Record.Course_Id,  Temporary_Record.Faculty_Name, Temporary_Record.Course_Name);
		Write_Status = write(Socket_Descriptor, Write_Buffer, strlen(Write_Buffer));
		Check_Write_Status(Write_Status);
	}	
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer)); //Dummy Read
	
	*/
	lock1.l_type = F_UNLCK;
	fcntl(File_Descriptor, F_SETLKW, &lock1);	
	
	//Checking if file is empty & fetching value of Id
	lseek(File_Descriptor, 0, SEEK_SET);
	Read_Status = read(File_Descriptor, &Buffer, 1);
	if(Read_Status == 0){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
		
	bzero(Write_Buffer, sizeof(Write_Buffer));   //to be removed
	strcat(Write_Buffer, "Enter Student ID : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));
	details.Student_Id = atoi(Read_Buffer);
	
	bzero(Write_Buffer, sizeof(Write_Buffer));   
	strcat(Write_Buffer, "Enter Course ID : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));
	details.Course_Id = atoi(Read_Buffer);	
	
	File_Descriptor = open("Enroll.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Enroll.txt file");
	
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = -1 * (sizeof(struct Enroll));
	lock.l_len = (sizeof(struct Enroll));
	lock.l_pid = getpid();
	fcntl(File_Descriptor, F_SETLKW, &lock);
	//Writing Fetched data to the Course.txt file
	lseek(File_Descriptor, 0, SEEK_END);
	write(File_Descriptor, &(details), sizeof(details));
	lock.l_type = F_UNLCK;
	fcntl(File_Descriptor, F_SETLKW, &lock);
	
	printf("\nFollowing details have been added to the file : ");
	printf("\nStudentId : %d", details.Student_Id);
	printf("\nCourseId : %d", details.Course_Id);
}

void Unenroll_Course(int Socket_Descriptor){
	ssize_t Write_Status, Read_Status, Bytes_Read;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	struct Enroll details;
	
	int File_Descriptor = open("Course.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Course.txt file");
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	bzero(Read_Buffer, sizeof(Read_Buffer));
	strcat(Write_Buffer, "Enter Student Id : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));
	details.Student_Id = atoi(Read_Buffer);
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	bzero(Read_Buffer, sizeof(Read_Buffer));
	strcat(Write_Buffer, "Enter Course Id : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));
	details.Course_Id = atoi(Read_Buffer);
	
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
	struct Enroll Temporary_Record;  
	bzero(Read_Buffer, sizeof(Read_Buffer));  
	bzero(Write_Buffer, sizeof(Write_Buffer)); 
	while(Bytes_Read = read(File_Descriptor, &Temporary_Record, sizeof(struct Enroll)) > 0){   //Logic for 1 record to be verified
		if(Temporary_Record.Course_Id == Temporary_Record.Course_Id && Temporary_Record.Student_Id == Temporary_Record.Student_Id){
			lseek(File_Descriptor, -1 * (sizeof(struct Enroll)), SEEK_CUR);
			removed = 1;
		}
		else
			write(File_Descriptor, &Temporary_Record, sizeof(struct Enroll));
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

void View_Enrolled_Courses(int Socket_Descriptor){
	ssize_t Write_Status, Read_Status;
	char Read_Buffer[1000], Write_Buffer[1000];	
	int id;
	struct Enroll Temporary_Record;

	int File_Descriptor = open("Enroll.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Course.txt file");
		
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Student ID : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));
	id = atoi(Read_Buffer);
		
	struct flock lock1;
	lock1.l_type = F_RDLCK;
	lock1.l_whence = SEEK_SET;
	lock1.l_start = 0;
	lock1.l_len = 0;
	lock1.l_pid = getpid();
	fcntl(File_Descriptor, F_SETLKW, &lock1);
	
	//Displaying all courses to Student
	while((Read_Status = read(File_Descriptor, &Temporary_Record, sizeof(struct Enroll)))>0){
	
		bzero(Write_Buffer, sizeof(Write_Buffer));
		if(Temporary_Record.Student_Id == id){
			sprintf(Write_Buffer, "%d   %d\n", Temporary_Record.Course_Id, Temporary_Record.Student_Id);
			Check_Write_Status(Write_Status);
		}
	}	
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
	lock1.l_type = F_UNLCK;
	fcntl(File_Descriptor, F_SETLKW, &lock1);

}

