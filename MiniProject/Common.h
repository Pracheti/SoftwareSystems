//Structure Declaration
struct Student{
	int Student_Id, Age, Year, Status;  //1=Activate, 0=Deactivate
	char Name[100];
};

struct Faculty{
	int Faculty_Id, Age;
	bool Status;
	char Name[100], Course[100];   //Course needs to be removed
};

struct Enroll{
	int Course_Id, Student_Id;    //EnrollId needs to be removed
};

struct Course{
	int Course_Id;
	char Course_Name[100];
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
