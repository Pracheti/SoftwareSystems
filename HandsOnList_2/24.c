/*
NAME : PRACHETI BHALE
ROLL NO : MT2023155

24) Write a program to create a message queue and print the key and message queue id.
*/

#include <sys/types.h>
#include <sys/ipc.h>   
#include <sys/msg.h>  
#include <stdio.h>     
#include <unistd.h> 

int main(){
	key_t key;
	int id;
	
	key = ftok("./myfile", 'x');
	if (key == -1)
		perror("ftok");
	id = msgget(key, IPC_CREAT | 0777);
	if (id == -1)
		perror("msgget");
		
	printf("\nKey: %d", key);
    printf("\nMessage Queue Identifier: %d\n", id);		
}
