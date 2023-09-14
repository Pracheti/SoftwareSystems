/*
Name : Pracheti Bhale
Roll No : MT2023155

8) Write a program to open a file in read only mode, read line by line & display each line as it is read. Close the file when end is reached.
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	if(argc != 2 ){
		printf("\nPlease provide file names");
		return 0;
	}
	int fd_read = open(argv[1], O_RDONLY);
	int line_no=0;
	printf("\n %d ", line_no);
	line_no++;
	
	if(fd_read==-1){
		printf("\nThe file doesn't exist");
		return 0;
	}
	
	while(1){
		char buff;
		int char_read = read(fd_read, &buff, 1);
		if(buff != 10){
			printf("%c", buff);
		}
		else if(char_read == 0)
			break;
		else{
			line_no++;
			printf("\n %d ", line_no);
		}
	}
	int fd_read_close = close(fd_read);
	//int fd_write_close = close(fd_write);
	if(fd_read==-1)
		printf("\nThe file doesn't exist");
	
	return 0;
}	

