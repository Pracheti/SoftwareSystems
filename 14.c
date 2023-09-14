/*
Name : Pracheti Bhale
Roll No : MT2023155

14) Write a program to find the type of a file. 
a)Input should be taken from command line. 
b)Program should be able to identify any type of a file.
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

/*
  1.  Regular files ('-')
  2.  Directory files ('d')
  3.  Special files (Actually, this one has 5 types in it.)
    a.    Block file('b')
    b.    Character device file('c')
    c.    Named pipe file or just a pipe file('p')
    d.    Symbolic link file('l')
    e.    Socket file('s') 
*/

//File name to be taken as arguments.

int main(int argc, char *argv[]){
	struct stat sb;
	
	stat(argv[1], &sb);
	//int stat(const char * pathname , struct stat * statbuf );
	switch (sb.st_mode & S_IFMT) {
		case S_IFREG: printf("regular file\n"); break;
		case S_IFDIR: printf("directory\n"); break;
		case S_IFCHR: printf("character device\n"); break;
		case S_IFBLK: printf("block device\n"); break;
		case S_IFLNK: printf("symbolic (soft) link\n"); break;
		case S_IFIFO: printf("FIFO or pipe\n"); break;
		case S_IFSOCK: printf("socket\n"); break;
		default:
		printf("unknown file type?\n");
	}
	return 0;
}
