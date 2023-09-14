/*
Name : Pracheti Bhale
Roll No : MT2023155

10) Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10 bytes (use lseek) & write again 10 bytes.
a) check the return value of lseek
b) open the file with od & check the empty spaces in between the data
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	int fd_write = open(argv[1], O_WRONLY|O_CREAT, 777);
	if(fd_write==-1){
		printf("The file doesn't exist\n");
		return 0;
	}
	
	//Writing 10 bytes into the file
	char buff[10];
	printf("\nEnter 10 Bytes : ");
	for(int i=0; i<10; i++){
		scanf("%c", &buff[i]);
	}
	int char_written = write(fd_write, &buff, 10);
	
	//Moving 10 Bytes ahead
	//off_t lseek(int fd , off_t offset , int whence );
	int position = lseek(fd_write, 10, SEEK_CUR);
	
	//Writing 10 bytes into the file
	printf("\nEnter 10 Bytes : ");
	for(int i=0; i<10; i++){
		scanf("%c", &buff[i]);
	}
	char_written = write(fd_write, &buff, 10);
	
	//Return Value of lseek
	printf("\nValue of lseek : %d\n", position);
	 
}
