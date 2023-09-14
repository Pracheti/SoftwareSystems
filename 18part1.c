/*
Name : Pracheti Bhale
Roll No : MT2023155

18. Write a program to perform Record locking.
a. Implement write lock
b. Implement read lock
Create three records in a file. Whenever you access a particular record, first lock it then modify/access to avoid race condition.
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main(){
	int i, fd;
	struct ticket{
		int train_num;
		int ticket_count;
	}db[3];
	
	for(i=0; i<3; i++){
		db[i].train_num = i+1;
		db[i].ticket_count = 0;
	}
	
	fd = open("Record.txt", O_RDWR);
	write(fd, db, sizeof(db));
	return 0;
}
