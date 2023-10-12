//Structure Declaration
struct Student{
	int Id, Age, Year;
	bool Status;  //True=Activate, False=Deactivate
	char Name[100];
};

struct Faculty{
	int Id, Age;
	bool Status;
	char Name[100], Course[100];
};

struct Enroll{
	int CourseId, StudentId, EnrollId;
};

//Function Declaration
void Check_Read_Status(int Write_Status){
	if(Write_Status == -1){
		perror("Error while reading data sent by Client, Exiting");
		exit(0);
	}
}
