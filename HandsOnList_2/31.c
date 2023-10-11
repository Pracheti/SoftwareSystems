/* 
NAME : PRACHETI BHALE
ROLL NO. : MT2023155

31. Write a program to create a semaphore and initialize value to the semaphore.
a. create a binary semaphore
b. create a counting semaphore
*/

#include <sys/types.h>
#include <sys/ipc.h>   
#include <sys/sem.h>   
#include <unistd.h>    
#include <stdio.h>   

union semun{
	int val;
	struct semid_ds *buf;        
	unsigned short int * array;
};

int main(){
	int key = ftok("./semaphore_31", 1);
	int id = semget(key, 100, IPC_CREAT | 0777);
	
	union semun arg_1;
	arg_1.val = 1;  //1 for binary else >1 for counting semaphore
	// int semctl(int semid , int semnum , int cmd , ... /* union semun arg */); 
	semctl(id, 0, SETVAL, arg_1);
	
	union semun arg_2;
	arg_2.val = 2;  //1 for binary else >1 for counting semaphore
	// int semctl(int semid , int semnum , int cmd , ... /* union semun arg */); 
	semctl(id, 0, SETVAL, arg_2);
	
	return 0;
}
