/*
Name : Pracheti Bhale
Roll No : MT2023155

11) Write a program to open a file, duplicate the file descriptor and append the file with both the descriptors and check whether the file is updated properly or not. (Use dup, dup2, fcntl)
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	int fd_original = open(argv[1], O_RDWR|O_CREAT, 777);
	if(fd_original == -1){
		printf("The file doesn't exist\n");
		return 0;
	}
	//int fcntl(int fd , int cmd , ...);
	//Return on success depends on cmd, or –1 on error
	//cmd = F_DUPFD duplicates the fd; F_GETFD returns the fd flags, F_SETFD sets the fd flags, F_GETFL returns the file status flags etc.
	int fd_duplicated = fcntl(fd_original, F_DUPFD, 0);
	if(fd_duplicated == -1){
		printf("The file doesn't exist\n");
		return 0;
	}
	
	// 11(c)
	struct stat info;
	fstat(fd_original, &info);
	printf("The inode of fd %d is %d\n", fd_original, (int) info.st_ino);
	fstat(fd_duplicated, &info);
	printf("The inode of fd %d is %d\n", fd_duplicated, (int) info.st_ino);
		
	printf("Using FD 1 :\n");
	printf("Enter some data (Enter '0' to break) :\n");
	while(1){
		char buff;
		scanf("%c", &buff);
		if(buff == '0')
			break;	
		else{
			int char_write = write(fd_original, &buff, 1);
		}
	}
	
	printf("Using FD 2 :\n");
	printf("Enter some data (Enter '0' to break) :\n");
	while(1){
		char buff;
		scanf("%c", &buff);
		if(buff == '0')
			break;	
		else{
			int char_write = write(fd_duplicated, &buff, 1);
		}
	}
	return 0;
}	

