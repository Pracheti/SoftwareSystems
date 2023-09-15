/*
Name : Pracheti Bhale
Roll no : MT2023155

16) Write a program to send and receive data from parent to child vice versa. Use two way communication.

	Child<---------------fd_p_to_c[2]---------------Parent
	read(fd_p_to_c[0]) 								write(fd_p_to_c[1])
	close(fd_p_to_c[1])								close(fd_p_to_c[0])

	Child---------------fd_c_to_p[2]--------------->Parent
	write(fd_c_to_p[1]) 							read(fd_c_to_p[0])
	close(fd_c_to_p[0])								close(fd_c_to_p[1])

*/
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main(){
	int fd_p_to_c[2], fd_c_to_p[2];
	char buff1[100], buff2[100];
	pipe(fd_p_to_c);
	pipe(fd_c_to_p);
	
	if(fork() == 0){  //Child Process
		close(fd_p_to_c[1]);
		close(fd_c_to_p[0]);
		
		printf("\n From Child Process - Enter data that needs to be sent to Parent : ");
		scanf("%s", buff1);
		write(fd_c_to_p[1], buff1, 100);  //Could also be written as : write(fd_c_to_p[1], buff, sizeof(buff));
		
		read(fd_p_to_c[0], buff2, 100);   //Could also be written as : read(filedes[0], buff, sizeof(buff));
		printf("\n From Child Process - Data received from Parent : %s", buff2);
	}
	else{			  //Parent Process
		close(fd_p_to_c[0]);
		close(fd_c_to_p[1]);
		
		printf("\n From Parent Process - Enter data that needs to be sent to Child : ");
		scanf("%s", buff2);
		write(fd_p_to_c[1], buff2, 100);  //Could also be written as : write(fd_c_to_p[1], buff, sizeof(buff));
		
		read(fd_c_to_p[0], buff1, 100);   //Could also be written as : read(fd_c_to_p[0], buff, sizeof(buff));
		printf("\n From Child Process - Data received from Parent : %s", buff1);
	}
	return 0;
}
