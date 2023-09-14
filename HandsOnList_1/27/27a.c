/*
Name : Pracheti Bhale
Roll No : MT2023155

27) Write a program to execute ls -Rl by the following system call (execl).
*/
#include <unistd.h>

//int execl(const char * pathname , const char * arg , .../* , (char *) NULL */);
int main(){
	execl("/bin/ls", "ls", "-lr", NULL);
	return 0;
}
