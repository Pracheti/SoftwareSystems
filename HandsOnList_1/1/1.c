/*
Name : Pracheti Bhale
Roll No : MT2023155

1) Create the following types of files using (i) Shell Command (ii) System Call
a) Soft Link (symlink system call)
b) Hard Link (link system call)
c) FIFO (mknod Library Function or mkfifo system call)
*/

#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(){
	//int symlink (const char *oldname, const char *newname) ;: Returns 0 on success, or –1 on error
	int result1 = symlink("SourceFile", "DestinationFile");
	if(result1<0){
		perror("Failed");
		return 1;
	}
	//int link(const char *oldpath, const char *newpath);  : Returns 0 on success, or –1 on error
	int result2 = link("SourceFile", "DestinationFile1");
	if(result2<0){
		perror("Failed");
		return 1;
	}
	//int mknod(const char *pathname, mode_t mode, dev_t dev);  : Returns 0 on success, or –1 on error
	int result3 = mknod("File", S_IFIFO, 0);
	if(result3<0)
		perror("Failed");
	return 0;
}

