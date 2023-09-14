/*
Name : Pracheti Bhale
Roll No : MT2023155

17. Write a program to simulate online ticket reservation. Implement write lock.
Write a program to open a file, store a ticket number and exit. Write a separate program, to open the file, implement write lock, read the ticket number, increment the number and print the new ticket number then close the file.
*/

#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>

int main(){
	struct flock lock;
	int fd = open("db", O_RDWR);
	
	struct ticket{
		int ticket_no;
	}db;
	
	
	printf("\nBefore entering into critical section");
	fcntl(fd, F_SETLKW, &lock);
	printf("\nInside the critical section");
	read(fd, &db, sizeof(db));
	printf("\nCurrent ticket number : %d\n", db.ticket_no);
	db.ticket_no++;
	
	lseek(fd, 0, SEEK_SET);
	write(fd, &db, sizeof(db));
	
	printf("\nPress enter to unlock");
	getchar();
	
	lock.l_type = F_UNLCK;
	fcntl(fd, F_SETLK, &lock);
	printf("\nExited the critical section");
	return 0;
	
}
