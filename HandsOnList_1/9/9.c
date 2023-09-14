/*
Name : Pracheti Bhale
Roll No : MT2023155

9) Write a program to print the following information about a given file.
a) Inode
b) Number of hard links
c) Uid
d) Gid
e) Size
f) Block Size
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main(int argc, char *argv[]){
	struct stat fileInfo;
	//int stat(const char * pathname , struct stat * statbuf );
	//stat() system call takes 2 parameters : File name and pointer to stat struct
	if(stat(argv[1], &fileInfo) == -1)
		printf("\nError");
	else{
		printf("\n 1) Inode : %d", fileInfo.st_ino);
		printf("\n 2) Number of hard links : %d", fileInfo.st_nlink);  //No. of links to the file
		printf("\n 3) UID : %d", fileInfo.st_uid);
		printf("\n 4) GID : %d", fileInfo.st_gid);
		printf("\n 5) Size : %d", fileInfo.st_size);
		printf("\n 6) Block Size : %d", fileInfo.st_blocks);
				
		printf("\n");s
	}
	return 0;
}
