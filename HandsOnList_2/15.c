/*
Name : Pracheti Bhale
Roll no : MT2023155

15) Write a program to send some data from parent to the child process.
*/

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>		`
#include<unistd.h>

int main(){
	int filedes[2];
	char buff[100];
	pipe(filedes);   		//Returns 0 on success, or –1 on error
	if(fork() == 0){		//Child Process
		close(filedes[1]);	
		read(filedes[0], buff, 100); //Could also be written as : read(filedes[0], buff, sizeof(buff));
		printf("\nData sent from parent : %s", buff);
	}
	else{					//Parent Process
		close(filedes[0]);	//Close read-end of the pipe 
		printf("\nEnter some data that needs to be send to child : ");
		scanf("%s", buff);
		write(filedes[1], buff, 100);  //Could also be written as : write(filedes[1], buff, sizeof(buff));
	}
	return 0;
}
