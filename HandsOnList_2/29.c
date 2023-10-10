/*
NAME : PRACHETI BHALE
ROLL NO. : MT2023155

29) Write a program to remove the message queue.
*/

#include <sys/types.h> 
#include <sys/ipc.h>   
#include <sys/msg.h>   
#include <stdio.h>   
#include <unistd.h>    
#include <errno.h>

int main(){
	struct msqid_ds Info;
	int key = ftok("./myfile_29", 1);
	int id = msgget(key, IPC_CREAT | 0777);
	if (id == -1)
		perror("msgget");
	printf("\nKey : %d", key);
  	printf("\nMessage Queue Identifier : %d", id);
	int msg_qstat = msgctl(id, IPC_RMID, &Info);   /* Immediately remove the message queue object and its associated msqid_ds data structure. All messages remaining in the queue are lost, and any blocked reader or writer processes are immediately awakened, with msgsnd()
or msgrcv() failing with the error EIDRM . The third argument to msgctl() is ignored for this operation. */
	printf("\nKey : %d", key);
  	printf("\nMessage Queue Identifier : %d", id);
	return 0;
}
