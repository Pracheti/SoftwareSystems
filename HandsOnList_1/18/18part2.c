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
	int fd, input;
	struct ticket{
		int train_num;
		int ticket_count;
	}db;
	
	fd = open("Record.txt", O_RDWR);
	printf("\nSelect train number : 1, 2, 3\n");
	scanf("%d", &input);
	
	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = (input-1) * sizeof(db);
	lock.l_len = sizeof(db);
	lock.l_pid = getpid();
	
	lseek(fd, (input-1)*sizeof(db), SEEK_SET);
	read(fd, &db, sizeof(db));
	printf("\nBefore entering critical section");
	fcntl(fd, F_SETLKW, &lock);
	
	printf("\nCurrent ticket count : %d", db.ticket_count);
	
	db.ticket_count++;
	
	lseek(fd, -1*sizeof(db), SEEK_CUR);
	write(fd, &db, sizeof(db));
	
	printf("\nTo book ticket, press enter");
	getchar();
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	printf("\n Ticket booked with number %d\n", db.ticket_count);

}
