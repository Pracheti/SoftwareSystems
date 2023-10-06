/* 
NAME : PRACHETI BHALE
ROLL NO : MT2023155

23) Write a program to print the maximum number of files can be opened within a process and size of a pipe (circular buffer).
*/

/*
The RLIMIT_NOFILE limit specifies a number one greater than the maximum file descriptor number that a process may allocate. Attempts (e.g., open(), pipe(), socket(), accept(), shm_open(), dup(), dup2(), fcntl(F_DUPFD), and epoll_create()) to allocate descriptors beyond this limit fail. Changes to the RLIMIT_NOFILE limit are reflected in the value returned by sysconf(_SC_OPEN_MAX).
_PC_PIPE_BUF : Maximum number of bytes that can be written atomically to a pipe or FIFO.
*/

#include <sys/types.h> 
#include <sys/stat.h>  
#include <fcntl.h>     
#include <unistd.h>    
#include <stdio.h> 

int main()
{
	char file[] ="./file_23_code";
	int maxFileSize = sysconf(_SC_OPEN_MAX);
	int maxPipeSize =pathconf(file, _PC_PIPE_BUF);    //long pathconf(const char * pathname , int name );
	printf("Maximum number of files that can be opened within the process: %d\n", maxFileSize);
	printf("Maximum size of a FIFO file: %d\n", maxPipeSize);
	return 0;
}
