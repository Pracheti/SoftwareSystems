/*
Name : Pracheti Bhale
Roll no : MT2023155

17) Write a program to execute ls -l | wc.
	a) Use dup
	b) Use dup2
	c) use fcntl
	
newfd = fcntl(oldfd, F_DUPFD, startfd); --> This call makes a duplicate of oldfd by using the lowest unused file descriptor greater than or equal to startfd.
*/

#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main(){
	
	int fd[2];
	pipe(fd);			// Allocates file descriptors 3 and 4 for pipe 
	printf("%d %d",fd[0], fd[1]);   //Output : fd[0] = 3, fd[1] = 4
	
	if(fork() == 0){	//Child Process
		close(0); 		//Close STDIN
		close(fd[1]);	//Close write-end of the pipe
		fcntl(fd[0], F_DUPFD, 0);   //newfd = fcntl(oldfd, F_DUPFD, startfd);
		execl("/bin/wc", "wc", NULL);
	}
	else{				//Parent Process
		close(fd[0]);  	//Close read-end of the pipe
		close(1);	 	//Close STDOUT
		fcntl(fd[1], F_DUPFD, 1);	 //newfd = fcntl(oldfd, F_DUPFD, startfd);
		/* "ls -l" will print to STDOUT but we want to redirect its output to the write-end of pipe. So we close STDOUT fd for the process &	then call dup(old_fd)*/
		execl("/bin/ls", "ls", "-l", NULL);
	}
	return 0;
}
