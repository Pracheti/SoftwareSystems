/*
Name : Pracheti Bhale
Roll no : MT2023155

18) Write a program to find out total number of directories on the pwd. Execute ls -l | grep ^d | wc ? Use only dup2.
*/

/*
         pipe(fd1)                 pipe(fd2)   
ls -l ----------------> grep ^d ----------------> wc 
close(1)			  close(0)				   
close(fd1[0])		  close(fd1[1])			   
					  close(1)				   close(0)	
					  close(fd2[0]) 		   close(fd2[1])
*/

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main(){
	int fd1[2], fd2[2];
	pipe(fd1);				//Allocates file descriptors 3 and 4 for pipe 
	pipe(fd2);				//Allocates file descriptors 4 and 5 for pipe 
	
	
	if(fork() == 0){  		//Child Process 1 : executes grep ^d
	
		close(0); 			//Close STDIN
		close(fd1[1]);		//Close write-end of the pipe 1
		dup2(fd1[0], 0);
		
		close(1);			//Close STDOUT
		close(fd2[0]);		//Close read-end of pipe 2
		dup2(fd2[1], 1);
		
		execl("/usr/bin/grep","grep","^d",NULL);
	}
	else{
		if(fork() == 0){	//Child Process 2 : executes wc
		
			close(0); 			//Close STDIN
			close(fd2[1]);		//Close write-end of the pipe 2
			close(fd1[0]);		//Close read-end of the pipe 1 : Important
			close(fd1[1]);		//Close write-end of the pipe 1 : Important
			dup2(fd2[0], 0);
			execl("/usr/bin/wc", "wc", NULL);
		}
		else{					//Parent Process : executes ls -l
		
			close(fd1[0]);  	//Close read-end of the pipe 1
			close(fd2[0]);		//Close read-end of the pipe 2 : Important
			close(fd2[1]);		//Close write-end of the pipe 2 : Important
			close(1);	 		//Close STDOUT
			dup2(fd1[1], 1);	 
			execl("/usr/bin/ls", "ls", "-l", NULL);	
		}
	}
	return 0;
}
