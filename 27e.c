/*
Name : Pracheti Bhale
Roll No : MT2023155

27) Write a program to execute ls -Rl by the following system call (execl, execlp, execle, execv, execvp)
*/

#include <unistd.h>

//int execvp(const char * filename , char *const argv []);
int main(){
	char *args[] = {"ls", "-lr", NULL};
	execvp("/bin/ls", args);
	return 0;
}
