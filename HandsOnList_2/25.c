/*
NAME : PRACHETI BHALE
ROLL NO : MT2023155

25) Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
	a. access permission
	b. uid, gid
	c. time of last message sent and received
	d. time of last change in the message queue
	d. size of the queue
	f. number of messages in the queue
	g. maximum number of bytes allowed
	h. pid of the msgsnd and msgrcv
*/

//int msgctl(int msqid , int cmd , struct msqid_ds * buf );

#include <sys/types.h> 
#include <sys/ipc.h>   
#include <sys/msg.h>   
#include <stdio.h>   
#include <unistd.h>    
#include <errno.h>

int main(){

	struct msqid_ds Info;
	int key = ftok("./myfile", 1);
	int id = msgget(key, IPC_CREAT | 0777);
	if (id == -1)
		perror("msgget");
	printf("\nKey: %d", key);
    printf("\nMessage Queue Identifier: %d", id);
	int msg_qstat=  msgctl(id, IPC_STAT, &Info);  /* IPC_STAT :Place a copy of the msqid_ds data structure associated with this message queue in the buffer pointed to by buf. */
	 
    printf("\nAccess Permission: %d", Info.msg_perm.mode);
    printf("\nUID: %d", Info.msg_perm.uid);
    printf("\nGID: %d", Info.msg_perm.gid);
    printf("\nTime of last message sent: %ld", Info.msg_stime);
    printf("\nTime of last message received: %ld", Info.msg_rtime);
    printf("\nSize of queue: %ld", Info.__msg_cbytes);
    printf("\nNumber of messages in the queue: %ld", Info.msg_qnum);
    printf("\nMaximum number of bytes allowed in the queue: %ld", Info.msg_qbytes);
    printf("\nPID of last sent message: %d", Info.msg_lspid);
    printf("\nPID of last received message: %d\n", Info.msg_lrpid);
    
    return 0;
}
