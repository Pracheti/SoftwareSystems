//Function Declaration
void Enroll_New_Course(int Socket_Descriptor);
void Unenroll_Course(int Socket_Descriptor);

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
					//Enroll_New_Course(Socket_Descriptor);
					break;
				case 2:
					//Unenroll_Course(Socket_Descriptor);
					break;
				/*case 3:
					Activate_Student(Socket_Descriptor);
					break;
				case 4:
					Deactivate_Student(Socket_Descriptor);
					break;
				case 5:
					close(Socket_Descriptor);
					break; */
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
	
	int File_Descriptor = open("Course.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Course.txt file");
		
	//Checking if file is empty & fetching value of Id
	lseek(File_Descriptor, 0, SEEK_SET);
	Read_Status = read(File_Descriptor, &Buffer, 1);
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Student ID : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));
	details.Faculty_Id = atoi(Read_Buffer);
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Course ID : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));
	details.Course_Id = atoi(Read_Buffer);	
	
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
	printf("\nStudentId : %d", details.StudentId);
	printf("\nCourseId : %d", details.CourseId);
}

void Unenroll_Course(int Socket_Descriptor){
	ssize_t Write_Status, Read_Status;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	struct Enroll details;
	
	int File_Descriptor = open("Course.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Course.txt file");
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	bzero(Read_Buffer, sizeof(Read_Buffer));
	strcat(Write_Buffer, "Enter Student Id : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
	details.StudentId = atoi(Read_Buffer);
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	bzero(Read_Buffer, sizeof(Read_Buffer));
	strcat(Write_Buffer, "Enter Course Id : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, strlen(Write_Buffer));
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
	details.CourseId = atoi(Read_Buffer);
	
	//int file_Descriptor_temp = open("Temp.txt", );
}

