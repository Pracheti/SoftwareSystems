/*
NAME : PRACHETI BHALE
ROLL NO. : MT2023155

27) Write a program to receive messages from the message queue.
a. with 0 as a flag
b. with IPC_NOWAIT as a flag
*/

/*IPC_NOWAIT : Perform a nonblocking send. Normally, if a message queue is full, msgsnd() blocks until enough space has become available to allow the message to be placed on the queue. However, if this flag is specified, then msgsnd() returns immediately with the error EAGAIN .

ssize_t msgrcv(int msqid , void * msgp , size_t maxmsgsz , long msgtyp , int msgflg );
*/

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
	//Sending message 1 (for 27(a))
	struct mymsg message1;
	
	message1.mtype = 1;
	message1.mtext = "Have a Good day!!";
	
	int key = ftok("./myfile", 1);
	int id = msgget(key, IPC_CREAT | 0777);
	if (id == -1)
		perror("msgget");
	int status = msgsnd(id, &message1, 1000, 0);
	if(status == -1)
		perror("Error sending message into message queue");
	printf("\nKey: %d", key);
    printf("\nMessage Queue Identifier for Message1 : %d\n", id);
    
    msgrcv(id, &message1, 100, 1, IPC_NOWAIT);
    printf("Message with IPC_NOWAIT flag : %s", message1.mtext);
	
	//Sending message 2 (for 27(b)
	struct mymsg message2;
	
	message2.mtype = 2;
	message2.mtext = "Have a Good day!!";
	
	key = ftok("./myfile", 1);
	id = msgget(key, IPC_CREAT | 0777);
	if (id == -1)
		perror("msgget");
	status = msgsnd(id, &message2, 1000, 0);
	if(status == -1)
		perror("Error sending message into message queue");
	printf("\nKey: %d", key);
    printf("\nMessage Queue Identifier for Message 2: %d\n", id);
	
	msgrcv(id, &message1, 100, 2, 0);
	printf("Message with 0 flag : %s\n", message2.mtext);
	
	return 0;
}
