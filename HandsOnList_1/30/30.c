/*
Name : Pracheti Bhale
Roll No : MT2023155

30) Write a program to run a script at a specific time using a Daemon process.
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>

// Argument to be passed as hour minute second
void main(int argc, char *argv[]) {

    // current time and deadline time
    time_t curr, d;
    // User readable format
    struct tm *deadLine;

    pid_t childPID;

    if (argc < 2)
        printf("Pass at least one argument\n");
    else {
        time(&curr); 						//current time
        deadLine = localtime(&curr);     	//user readable format

        deadLine->tm_hour = atoi(argv[1]);
        deadLine->tm_min = argv[2] == NULL ? 0 : atoi(argv[2]);
        deadLine->tm_sec = argv[3] == NULL ? 0 : atoi(argv[3]);

        d = mktime(deadLine);

        if ((childPID = fork()) == 0) {
            //child area
            setsid();
            chdir("/");
            umask(0);
            do{
                time(&curr);
            }while (difftime(d, curr) > 0);
            
            printf("Done!\n");
            exit(0);
        }
        exit(0);
    }
}
	
