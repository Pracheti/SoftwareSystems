/*
Name : Pracheti Bhale
Roll No : MT2023155

27) Write a program to execute ls -Rl by the following system call (execlp)
*/

#include <unistd.h>

//int execlp(const char * filename , const char * arg , .../* , (char *) NULL */);
int main(){
	execlp("ls", "ls", "-lr", NULL);
	return 0;
}
