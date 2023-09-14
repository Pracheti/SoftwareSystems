/*
Name : Pracheti Bhale
Roll No : MT2023155

27) Write a program to execute ls -Rl by the following system call (execv)
*/

#include <unistd.h>

//int execv(const char * pathname , char *const argv []);
int main(){
	char *args[] = {"ls", "-lr", NULL};
	execv("/bin/ls", args);
	return 0;
}
