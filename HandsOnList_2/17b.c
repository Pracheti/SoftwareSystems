/*
Name : Pracheti Bhale
Roll no : MT2023155

17) Write a program to execute ls -l | wc.
	a) Use dup
	b) Use dup2
	c) use fcntl
*/

/*
Steps in 17a.c depend on the assumption that file descriptors 0, 1, and 2 for a process are already open. (The shell normally ensures this for each program it executes.) If file descriptor 0 was already closed prior to the above steps, then we would erroneously bind the process’s standard input to the write end of the pipe. To avoid this possibility, we can replace the calls to close() and dup() with the following dup2() call, which allows us to explicitly specify the descriptor to be bound to the pipe end
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
		dup2(fd[0], 0);
		execl("/bin/wc", "wc", NULL);
	}
	else{				//Parent Process
		close(fd[0]);  	//Close read-end of the pipe
		close(1);	 	//Close STDOUT
		dup2(fd[1], 1);	 
		/* "ls -l" will print to STDOUT but we want to redirect its output to the write-end of pipe. So we close STDOUT fd for the process &	then call dup(old_fd)*/
		execl("/bin/ls", "ls", "-l", NULL);
	}
	return 0;
}
