/*
NAME : PRACHETI BHALE
ROLL NO. : MT2023155

26) Write a program to send messages to the message queue. Check $ipcs -q
*/

// int msgsnd(int msqid , const void * msgp , size_t msgsz , int msgflg );

#include <sys/types.h> 
#include <sys/ipc.h>   
#include <sys/msg.h>   
#include <stdio.h>   
#include <unistd.h>    
#include <errno.h>

struct mymsg {
    long mtype;
    char *mtext;
};
int main(){
	struct mymsg message;
	
	message.mtype = 1;
	message.mtext = "Have a Good day!!";
	
	int key = ftok("./myfile", 1);
	int id = msgget(key, IPC_CREAT | 0777);
	if (id == -1)
		perror("msgget");
	int status = msgsnd(id, &message, 1000, 0);
	if(status == -1)
		perror("Error sending message into message queue");
	printf("\nKey: %d", key);
    printf("\nMessage Queue Identifier : %d\n", id);
	return 0;
}
