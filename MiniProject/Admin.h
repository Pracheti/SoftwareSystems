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
	char WriteBuffer[1000], choice[10];
	Login_Check(Socket_Descriptor, 1);
	
	bzero(WriteBuffer, sizeof(WriteBuffer));
	while(1){
	/* char *strcat(char *destination, const char *source) */
		strcat(WriteBuffer, "\n*************WELCOME TO ADMIN PORTAL*************");
		strcat(WriteBuffer, "\n1. Add new Student");
		strcat(WriteBuffer, "\n2. Add new Faculty");
		strcat(WriteBuffer, "\n3. Activate Student");
		strcat(WriteBuffer, "\n4. Deactivate Student");
		strcat(WriteBuffer, "\n5. Update Student details");
		strcat(WriteBuffer, "\n6. Update Faculty details");
		strcat(WriteBuffer, "\n7. Exit");
		strcat(WriteBuffer, "\nEnter Your Choice : ");
		
		Write_Status = write(Socket_Descriptor, WriteBuffer, strlen(WriteBuffer));
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
				/*case 3:
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
					break; */
				default:  
					printf("\nEnter valid choice"); 
			}
		}
	}
}

void Add_New_Student(int Socket_Descriptor){
	ssize_t Write_Status, Read_Status;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	struct Student details, previous_details;
	
	int File_Descriptor = open("Student.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Student.txt file");
		
	//Checking if file is empty & fetching value of Id
	int position = lseek(File_Descriptor, 0, SEEK_SET);
	Read_Status = read(File_Descriptor, &Buffer, 1);
	if(Read_Status == 0)					//File is Empty
		details.Student_Id = 1;
	else{
		lseek(File_Descriptor, -1 * (sizeof(struct Student)), SEEK_END);
		read(File_Descriptor, &(previous_details), sizeof(struct Student));
		details.Student_Id = previous_details.Student_Id + 1;
	}
		
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Student Name : ");
	Write_Status = write(Socket_Descriptor, Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
	strcpy(details.Student_Name, Read_Buffer);

	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Student Age : ");
	Write_Status = write(Socket_Descriptor, Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
	details.Age = atoi(Read_Buffer);
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Student Year : ");
	Write_Status = write(Socket_Descriptor, Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
	details.Year = atoi(Read_Buffer);
	
	strcpy(details.Student_Password, "iiitb");
	
	details.Status = 1;
	
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = (details.Student_Id-1) * (sizeof(struct Student));
	lock.l_len = (sizeof(struct Student));
	lock.l_pid = getpid();
	fcntl(File_Descriptor, F_SETLKW, &lock);
	//Writing Fetched data to the Student.txt file
	lseek(File_Descriptor, 0, SEEK_END);
	write(File_Descriptor, &(details), sizeof(details));
	lock.l_type = F_UNLCK;
	fcntl(File_Descriptor, F_SETLKW, &lock);
	
	printf("\nFollowing details have been added to the file : ");
	printf("\nId : %d", details.Student_Id);
	printf("\nName : %s", details.Student_Name);
	printf("\nPassword : %s", details.Student_Password);
	printf("\nAge : %d", details.Age);
	printf("\nYear : %d", details.Year);
	printf("\nActivation Status : %d", details.Status);
}

void Add_New_Faculty(int Socket_Descriptor){
	ssize_t Write_Status, Read_Status;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	struct Faculty details, previous_details;
	
	int File_Descriptor = open("Faculty.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Faculty.txt file");
		
	//Checking if file is empty & fetching value of Id
	Read_Status = read(File_Descriptor, &Buffer, 1);
	if(Read_Status == 0)					//File is Empty
		details.Faculty_Id = 1;
	else{
		lseek(File_Descriptor, -1 * (sizeof(struct Faculty)), SEEK_END);
		details.Faculty_Id = read(File_Descriptor, &previous_details, sizeof(struct Faculty));
		details.Faculty_Id = previous_details.Faculty_Id + 1;
	}
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Faculty Name : ");
	Write_Status = write(Socket_Descriptor, Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, Read_Buffer, 1000);
	strcpy(details.Faculty_Name, Read_Buffer);
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Faculty Age : ");
	Write_Status = write(Socket_Descriptor, Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
	details.Age = atoi(Read_Buffer);
	
	details.Status = 1;
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "Enter Course taught : ");
	Write_Status = write(Socket_Descriptor, Write_Buffer, strlen(Write_Buffer));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, Read_Buffer, 1000);
	strcpy(details.Course, Read_Buffer);
	
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = (details.Faculty_Id-1) * (sizeof(struct Faculty));
	lock.l_len = (sizeof(struct Faculty));
	lock.l_pid = getpid();
	fcntl(File_Descriptor, F_SETLKW, &lock);
	//Writing Fetched data to the Faculty.txt file
	lseek(File_Descriptor, 0, SEEK_END);
	write(File_Descriptor, &(details), sizeof(details));
	lock.l_type = F_UNLCK;
	fcntl(File_Descriptor, F_SETLKW, &lock);
	
	printf("\nFollowing details have been added to the file : ");
	printf("\nId : %d", details.Faculty_Id);
	printf("\nName : %s", details.Faculty_Name);
	printf("\nAge : %d", details.Age);
	printf("\nCourse : %s", details.Course);
	printf("\nActivation Status : %d", details.Status);
}
/*
void Activate_Student(int Socket_Descriptor){
	ssize_t Write_Status, Read_Status;
	char Read_Buffer[1000], Write_Buffer[1000], Buffer;
	int id;
	struct Student details;
	
	int File_Descriptor = open("Student.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Student.txt file");

	int position = lseek(File_Descriptor, 0, SEEK_SET);
	Read_Status = read(File_Descriptor, &Buffer, 1);
	if(Read_Status == 0){					//File is Empty
		strcat(Write_Buffer, "File is empty, exiting..");
		close(Socket_Descriptor);
	}
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "\nEnter Student Id that needs to be activated : ");
	Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(struct Student));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));  //Collect Student ID from Client
	id = atoi(Read_Buffer);
	
	File_Descriptor = open("Student.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Student.txt file");
		
	position = lseek(File_Descriptor, 0, SEEK_SET);
	int reached = 0;
	do{
		Read_Status = read(File_Descriptor, &details, sizeof(struct Student));
		if(details.Student_Id == id){
			if(details.Status == 0){
				details.Status == 1;
				bzero(Write_Buffer, sizeof(Write_Buffer));
				strcat(Write_Buffer, "\nThe activation status of student is now activated!!");	
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
	write(Socket_Descriptor, Write_Buffer, strlen(Write_Buffer));
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
	Read_Status = read(File_Descriptor, &Buffer, 1);
	if(Read_Status == 0){					//File is Empty
		strcat(Write_Buffer, "File is empty, exiting..");
		close(Socket_Descriptor);
	}
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "\nEnter Student Id that needs to be deactivated : ");
	Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(struct Student));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));  //Collected Student ID from Client
	id = atoi(Read_Buffer);
	
	File_Descriptor = open("Student.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Student.txt file");
		
	position = lseek(File_Descriptor, 0, SEEK_SET);
	int reached = 0;
	do{
		Read_Status = read(File_Descriptor, &details, sizeof(struct Student));
		if(details.Student_Id == id){
			if(details.Status == 1){
				bzero(Write_Buffer, sizeof(Write_Buffer));
				strcat(Write_Buffer, "\nThe student is now deactivated!!");	
				details.Status == 0;
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
	
	if(reached == 0)
		strcat(Write_Buffer, "\nId not found, Enter valid ID");	
	bzero(Write_Buffer, sizeof(Write_Buffer));
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
	Read_Status = read(File_Descriptor, &Buffer, 1);
	if(Read_Status == 0){					//File is Empty
		strcat(Write_Buffer, "File is empty, exiting..");
		close(Socket_Descriptor);
	}
	
	bzero(Write_Buffer, sizeof(Write_Buffer));
	strcat(Write_Buffer, "\nEnter ID of student that needs to be updated : ");
	Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(struct Student));
	Check_Write_Status(Write_Status);
	bzero(Read_Buffer, sizeof(Read_Buffer));
	Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));  //Collected Student ID from Client
	id = atoi(Read_Buffer);
	
	File_Descriptor = open("Student.txt", O_RDWR);
	if(File_Descriptor == -1)
		perror("Error opening Student.txt file");
		
	position = lseek(File_Descriptor, 0, SEEK_SET);
	int reached = 0;
	do{
		bzero(Read_Buffer, sizeof(Read_Buffer));
		Read_Status = read(File_Descriptor, &details, sizeof(struct Student));
		if(details.Id == id){
			reached = 1;
			bzero(Write_Buffer, sizeof(Write_Buffer));
			strcat(Write_Buffer, "\n1. Name\n2. Age\n3. Year\n4. Status");
			strcat(Write_Buffer, "\n Enter your choice : ");
			Write_Status = write(Socket_Descriptor, Write_Buffer, sizeof(struct Student));
				
			int User_choice;
			ssize_t Bytes_Read;
			char choice[100];
	
			bzero(choice, sizeof(choice));
			Bytes_Read = read(Socket_Descriptor, choice, sizeof(choice));
			Check_Write_Status(Write_Status);	
			else{
				User_choice = atoi(choice);
				switch(User_choice){
					case 1: 
						bzero(Write_Buffer, sizeof(Write_Buffer));
						strcat(Write_Buffer, "Enter Student Name : ");
						Write_Status = write(Socket_Descriptor, Write_Buffer, strlen(Write_Buffer));
						Check_Write_Status(Write_Status);
						bzero(Read_Buffer, sizeof(Read_Buffer));
						Read_Status = read(Socket_Descriptor, &Read_Buffer, 1000);
						strcpy(details.Name, Read_Buffer);
						break;
					case 2: 
						bzero(Write_Buffer, sizeof(Write_Buffer));
						strcat(Write_Buffer, "\n Enter new Age : ");
						write(Socket_Descriptor, Write_Buffer, sizeof(struct Student));
						Check_Write_Status(Write_Status);
						bzero(Read_Buffer, sizeof(Read_Buffer));
						Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
						details.Age = atoi(Read_Buffer);
						break;
					case 3:
						bzero(Write_Buffer, sizeof(Write_Buffer));
						strcat(Write_Buffer, "\n Enter new Year : ");
						write(Socket_Descriptor, Write_Buffer, sizeof(struct Student));
						Check_Write_Status(Write_Status);
						bzero(Read_Buffer, sizeof(Read_Buffer));
						Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
						details.Year = atoi(Read_Buffer);
						break;
					case 4:
						bzero(Write_Buffer, sizeof(Write_Buffer));   //To be Verified
						strcat(Write_Buffer, "\n Enter new Status : ");
						write(Socket_Descriptor, Write_Buffer, sizeof(struct Student));
						Check_Write_Status(Write_Status);
						bzero(Read_Buffer, sizeof(Read_Buffer));
						Read_Status = read(Socket_Descriptor, Read_Buffer, sizeof(Read_Buffer));
						details.Status = atoi(Read_Buffer);        
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
	Read_Status = read(File_Descriptor, &Buffer, 1);
	if(Read_Status == 0){					//File is Empty
		strcat(Write_Buffer, "File is empty, exiting..");
		close(Socket_Descriptor);
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
			Check_Write_Status(Write_Status);	
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
*/


