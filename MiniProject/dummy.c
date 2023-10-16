#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

struct Student{
	int Student_Id, Age, Year, Status;  //1=Activate, 0=Deactivate
	char Student_Name[100], Student_Password[100];
};

struct Faculty{
	int Faculty_Id, Age;
	char Faculty_Name[100], Faculty_Password[100];   //Course needs to be removed
};

int main(){
	/*struct Faculty detail;
	detail.Faculty_Id = 1;
	detail.Age = 21;
	strcpy(detail.Faculty_Name, "Disha");
	strcpy(detail.Faculty_Password, "iiitb");
	
	int File_Descriptor = open("Faculty.txt", O_RDWR);
	int status = write(File_Descriptor, &detail, sizeof(struct Faculty));
	if(status == -1)
		perror("Error"); */
	
	struct Student details;
	details.Student_Id = 3;
	details.Age = 21;
	details.Year = 2019;
	details.Status = 1;
	strcpy(details.Student_Name, "Gita");
	strcpy(details.Student_Password, "iiitb");
	
	int File_Descriptor = open("Student.txt", O_RDWR);
	write(File_Descriptor, &details, sizeof(struct Student)); 
	return 0;
}
