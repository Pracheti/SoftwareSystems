/* 
NAME : PRACHETI BHALE
ROLL NO. : MT2023155

30) Write a program to create a shared memory.
a. write some data to the shared memory
b. attach with O_RDONLY and check whether you are able to overwrite.
c. detach the shared memory
d. remove the shared memory
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
	//a) Creating Shared Memory & writing some data into it.
	int key = ftok("./mySharedMem_30", 1);
	int id = shmget(key, 100, IPC_CREAT | 0777);    /* int shmget(key_t key , size_t size , int shmflg ); */
	 
	/* void *shmat(int shmid , const void * shmaddr , int shmflg ); 
	   Returns address at which shared memory is attached on success, or (void *) –1 on error*/
	
	char *addr_1 = shmat(id, (void *)0, 0);  /* If shmaddr is NULL , then the segment is attached at a suitable address selected by the kernel. This is the preferred method of attaching a segment. */
 
    sprintf(addr_1, "Have a Good Day!");  //sprintf() or snprintf() can be used
    
    //b) attach with O_RDONLY and check whether you are able to overwrite.
    char *addr_2 = shmat(id, (void *)0, SHM_RDONLY);
    perror("snprintf");
    //sprintf(addr_2, "Hello, Again!");   --> Attempting to overwrite will give "Segmentation Fault"
    perror("snprintf");
    
    //c) detach the shared memory
    shmdt(addr_1);
	shmdt(addr_2);
	
	//d) remove the shared memory
	shmctl(id , IPC_RMID, NULL);
	
	return 0;
}
