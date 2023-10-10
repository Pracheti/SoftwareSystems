/*
NAME : PRACHETI BHALE
ROLL NO. : MT2023155

27) Write a program to change the exiting message queue permission. (use msqid_ds structure)
*/

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
	printf("\nKey : %d", key);
  	printf("\nMessage Queue Identifier : %d", id);
	int msg_qstat = msgctl(id, IPC_STAT, &Info);  /* IPC_STAT : Place a copy of the msqid_ds data structure associated with this message queue in the buffer pointed to by buf. */
	 
    printf("\nInitial Access Permissions : %d", Info.msg_perm.mode);
    
    Info.msg_perm.mode = 0111;
    msgctl(id, IPC_SET, &Info);  /* Update selected fields of the msqid_ds data structure associated with this message queue using values provided in the buffer pointed to by buf. */
    
    printf("\nFinal Access Permissions : %d\n", Info.msg_perm.mode);
    
    return 0;
}
