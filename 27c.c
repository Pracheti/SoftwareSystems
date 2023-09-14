/*
Name : Pracheti Bhale
Roll No : MT2023155

27) Write a program to execute ls -Rl by the following system call (execle)
*/

#include <unistd.h>

//int execle(const char * pathname , const char * arg , .../* , (char *) NULL, char *const envp [] */ );
int main(){
	execle("/bin/ls", "ls", "-lr", NULL, NULL);
	return 0;
}
