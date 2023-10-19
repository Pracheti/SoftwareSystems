//Function Declaration
void Enroll_New_Course(int Socket_Descriptor, int Login_Id);
void Unenroll_Course(int Socket_Descriptor, int Login_Id);
void View_Enrolled_Courses(int Socket_Descriptor, int Login_Id);
void Password_Change(int Socket_Descriptor, int Login_Id);

void Connect_With_Student(int Socket_Descriptor){
	int User_choice, Login_Id;
	ssize_t Write_Status, Bytes_Read;
	char Write_Buffer[1000], choice[100];
	Login_Id = Login_Check(Socket_Descriptor, 3);
	
	do{
	/* char *strcat(char *destination, const char *source) */
		bzero(Write_Buffer, sizeof(Write_Buffer));
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
					Enroll_New_Course(Socket_Descriptor, Login_Id);
					break;
				case 2:
					Unenroll_Course(Socket_Descriptor, Login_Id);
					break;
				case 3:
					View_Enrolled_Courses(Socket_Descriptor, Login_Id);
					break;
				case 4:
					Password_Change(Socket_Descriptor, Login_Id);
					break;
				default:  
					printf("\nEnter valid choice");
			}
		}
	}while(User_choice != 7);
}

void Enroll_New_Course(int Socket_Descriptor, int Login_Id){
	ssize_t Write_Status, Read_Status;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	struct Enroll details;
	struct Course Course_details;
	int Id;
	
	int File_Descriptor = open("Course.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Course.txt file");
		
	//Checking if file is empty & fetching value of Id
	lseek(File_Descriptor, 0, SEEK_SET);
	Read_Status = read(File_Descriptor, &Buffer, 1);
	if(Read_Status == 0){
		perror("Cannot enroll to courses, no courses available, exiting!");
		exit(0);
	}
	
	bzero(Write_Buffer, sizeof(Write_Buffer));   
	strcat(Write_Buffer, "Enter Course ID : ");
	Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
	Id = atoi(Read_Buffer);	
	//Pending : Checking if course id is valid
	//Checking if seats exists
	if(Id != 1)
		lseek(File_Descriptor, (Id-1) * (sizeof(struct Course)), SEEK_SET);
	else
		lseek(File_Descriptor, 0, SEEK_SET);
	read(File_Descriptor, &Course_details, sizeof(struct Course));
	
	if(Course_details.Seats_Left > 0){
		Course_details.Seats_Left--;
	
		if(Id != 1)
			lseek(File_Descriptor, (Id-1) * (sizeof(struct Course)), SEEK_SET);
		else
			lseek(File_Descriptor, 0, SEEK_SET);
		write(File_Descriptor, &Course_details, sizeof(struct Course));	
		
		details.Student_Id = Login_Id;
		details.Course_Id = Id;
		details.Enrollment_Status = 1;
		
		File_Descriptor = open("Enroll.txt", O_RDWR);
		if(File_Descriptor == -1)
			perror("Error opening Enroll.txt file");
		
		struct flock lock;
		lock.l_type = F_WRLCK;
		lock.l_whence = SEEK_SET;
		lock.l_start = 0;
		lock.l_len = 0;
		lock.l_pid = getpid();
		fcntl(File_Descriptor, F_SETLKW, &lock);
		//Writing Fetched data to the Enroll.txt file
		write(File_Descriptor, &(details), sizeof(details));
		lock.l_type = F_UNLCK;
		fcntl(File_Descriptor, F_SETLKW, &lock);
		
		bzero(Write_Buffer, sizeof(Write_Buffer));
		strcat(Write_Buffer, "Record inserted successfully!! Press any key to continue..");
		Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
		Check_Write_Status(Write_Status);	
				
		bzero(Read_Buffer, sizeof(Read_Buffer));
		Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));	 //Dummy Read
		
		printf("\nFollowing details have been added to the file : ");
		printf("\nStudentId : %d", details.Student_Id);
		printf("\nCourseId : %d", details.Course_Id);
	}
	else{
		bzero(Write_Buffer, sizeof(Write_Buffer));   
		strcat(Write_Buffer, "Seats Filled! Please check again..");
		Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(Write_Buffer));
		Check_Write_Status(Write_Status);
		bzero(Read_Buffer, sizeof(Read_Buffer));
		Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
	}
	
}

void Unenroll_Course(int Socket_Descriptor, int Login_Id){
	ssize_t Write_Status, Read_Status, Bytes_Read;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	struct Enroll details;
	int Id;
		
	bzero(Write_Buffer, sizeof(Write_Buffer));
	bzero(Read_Buffer, sizeof(Read_Buffer));
	strcat(Write_Buffer, "Enter Course Id : ");
	Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
	Check_Write_Status(Write_Status);
	Read_Status = read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));
	Id = atoi(Read_Buffer);
	
	int File_Descriptor = open("Enroll.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Enroll.txt file");
		
	int position = lseek(File_Descriptor, 0, SEEK_SET);
	Read_Status = read(File_Descriptor, &Buffer, 1);
	if(Read_Status == 0){					//File is Empty
		strcat(Write_Buffer, "File is empty, exiting..");
		Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
		Check_Write_Status(Write_Status);
	}
	
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;
	lock.l_pid = getpid();
	fcntl(File_Descriptor, F_SETLKW, &lock);
	//Writing Fetched data to the Enroll.txt file
	
	int removed = 0;
  
  	lseek(File_Descriptor, 0, SEEK_SET);
	bzero(Read_Buffer, sizeof(Read_Buffer));  
	bzero(Write_Buffer, sizeof(Write_Buffer)); 
	while(Bytes_Read = read(File_Descriptor, &details, sizeof(struct Enroll)) > 0){  
		if(details.Course_Id == Id && details.Student_Id == Login_Id){
			details.Enrollment_Status = 0;
			lseek(File_Descriptor, (-1) * sizeof(struct Enroll), SEEK_CUR);
			write(File_Descriptor, &details, sizeof(struct Enroll));
			bzero(Write_Buffer, sizeof(Write_Buffer));
			removed = 1;
			break;
		}
		bzero(Read_Buffer, sizeof(Read_Buffer));
	}
	lock.l_type = F_UNLCK;
	fcntl(File_Descriptor, F_SETLKW, &lock);
	if(removed == 1){				//Decreasing the seat count
		bzero(Write_Buffer, sizeof(Write_Buffer));
		strcat(Write_Buffer, "Record removed successfully!! Press any key to continue..");
		Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
		Check_Write_Status(Write_Status);
		File_Descriptor = open("Course.txt", O_RDWR);
		if(File_Descriptor == -1)
			perror("Error opening Course.txt file");
		struct Course course_details;
		if(Id != 1)
			lseek(File_Descriptor, (Id-1) * (sizeof(struct Course)), SEEK_SET);
		else
			lseek(File_Descriptor, 0, SEEK_SET);
		read(File_Descriptor, &course_details, sizeof(struct Course));
		course_details.Seats_Left++;
		if(Id != 1)
			lseek(File_Descriptor, (Id-1) * (sizeof(struct Course)), SEEK_SET);
		else
			lseek(File_Descriptor, 0, SEEK_SET);
		write(File_Descriptor, &course_details, sizeof(struct Course));
	}
	else{
		bzero(Write_Buffer, sizeof(Write_Buffer));
		strcat(Write_Buffer, "Record not found!! Press any key to continue..");
		Write_Status = write(Socket_Descriptor, &Write_Buffer, sizeof(Write_Buffer));
		Check_Write_Status(Write_Status);	
		
		read(Socket_Descriptor, Write_Buffer, sizeof(Write_Buffer));     //Dummy Read
	}
}

void View_Enrolled_Courses(int Socket_Descriptor, int Login_Id){
	ssize_t Write_Status, Read_Status;
	char Read_Buffer[1000], Write_Buffer[1000];	
	struct Enroll details;
	
	int File_Descriptor = open("Enroll.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Enroll.txt file");
	
	struct flock lock1;
	lock1.l_type = F_RDLCK;
	lock1.l_whence = SEEK_SET;
	lock1.l_start = 0;
	lock1.l_len = 0;
	lock1.l_pid = getpid();
	fcntl(File_Descriptor, F_SETLKW, &lock1);
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "COURSE ID  STUDENT ID");
	Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(Write_Buffer));
	Check_Write_Status(Write_Status);
	
	read(Socket_Descriptor, Write_Buffer, 1000);    //Dummy Read
	while((Read_Status = read(File_Descriptor, &details, sizeof(struct Enroll)))>0){
		if(Login_Id == details.Student_Id && details.Enrollment_Status == 1){
			bzero(Write_Buffer, sizeof(Write_Buffer));
			snprintf(Write_Buffer, sizeof(struct Course),"%d  %d\n", details.Course_Id, details.Student_Id);
			Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(Write_Buffer));
			read(Socket_Descriptor, Read_Buffer, sizeof(Write_Buffer));      //Dummy Read
			Check_Write_Status(Write_Status);
		}
	}	
	lock1.l_type = F_UNLCK;
	fcntl(File_Descriptor, F_SETLKW, &lock1);
}

void Password_Change(int Socket_Descriptor, int Login_Id){
	char Password[100], Write_Buffer[1000], Read_Buffer[1000];
	struct Student details;

	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "\nEnter new Password : ");
	write(Socket_Descriptor, Write_Buffer, sizeof(struct Faculty));
	bzero(Read_Buffer, sizeof(Read_Buffer));
	read(Socket_Descriptor, Read_Buffer, 1000);
	strcpy(Password, Read_Buffer);
	
	int File_Descriptor = open("Student.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Student.txt file");
	if(Login_Id != 1)
		lseek(File_Descriptor, (Login_Id-1) * (sizeof(struct Student)), SEEK_SET);
	else
		lseek(File_Descriptor, 0, SEEK_SET);
	read(File_Descriptor, &details, sizeof(struct Student));
	strcpy(details.Student_Password, Password);
	
	struct flock lock1;
	lock1.l_type = F_WRLCK;
	lock1.l_whence = SEEK_SET;
	lock1.l_start = (Login_Id-1)*(sizeof(struct Student));
	lock1.l_len = (sizeof(struct Student));
	lock1.l_pid = getpid();
	fcntl(File_Descriptor, F_SETLKW, &lock1);
	if(Login_Id != 1)
		lseek(File_Descriptor, (Login_Id-1) * (sizeof(struct Student)), SEEK_SET);
	else
		lseek(File_Descriptor, 0, SEEK_SET);
	write(File_Descriptor, &details, sizeof(struct Student));
	lock1.l_type = F_UNLCK;
	fcntl(File_Descriptor, F_SETLKW, &lock1);	

	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Password Updated Successfully!! ");
	write(Socket_Descriptor, Write_Buffer, sizeof(Write_Buffer));
	bzero(Read_Buffer, sizeof(Read_Buffer));
	read(Socket_Descriptor, &Read_Buffer, sizeof(Read_Buffer));   //Dummy Read
}

