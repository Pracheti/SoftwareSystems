/*
Name : Pracheti Bhale
Roll No : MT2023155

7) Write a program to copy file1 into file2 ($cp file1 file2).
*/
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	//printf("%d", argc);
	//printf("%s, argv[0]);
	if(argc !=3 ){
		printf("\nPlease provide file names");
		return 0;
	}
	int fd_read = open(argv[1], O_RDONLY);
	int fd_write = open(argv[2], O_WRONLY|O_CREAT, 777);
	if(fd_read==-1 || fd_write==-1){
		printf("\nThe file doesn't exist");
		return 0;
	}
	while(1){
		char buff;
		int char_read = read(fd_read, &buff, 1);
		if(char_read == 0)
			break;
		int char_written = write(fd_write, &buff, 1);
	}
	int fd_read_close = close(fd_read);
	int fd_write_close = close(fd_write);
	if(fd_read==-1 || fd_write==-1)
		printf("\nThe file doesn't exist");
	
	return 0;
	
}


//gcc 7.c -o mycp 
// curl ip_address/filename.c
