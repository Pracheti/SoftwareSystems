/*
Name : Pracheti Bhale
Roll no : MT2023155

19) Create a FIFO file by
a. mknod command
b. mkfifo command
c. use strace command to find out, which command (mknod or mkfifo) is better.
d. mknod system call
e. mkfifo library function
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(){
	/* a) mknod <file_name> p
		  b      create a block (buffered) special file
  		  c, u   create a character (unbuffered) special file
          p      create a FIFO
          => mknod fifo_a p

       b) We can create a FIFO from the shell using the mkfifo command:
			$ mkfifo [ -m mode ] pathname 
			mkfifo a=rw MYFIFO
			=> mkfifo -m 777 /home/pracheti/SoftwareSystem/HandsOnList_2/fifo_b
			
	*/
			
	mknod("./fifo_d", S_IFIFO|0777, 0);   //d) int mknod( char *pathname, mode_t mode, dev_t dev);
	/* mknod - make block or character special files. The third argument to mknod() is ignored unless we are creating a device file. Both  MAJOR and MINOR must be specified when TYPE is b, c, or u, and they must be omitted when TYPE is p. */
	mkfifo("./fifo_e", 0777);     		//e) int mkfifo(const char * pathname , mode_t mode );
	
	return 0;
}
