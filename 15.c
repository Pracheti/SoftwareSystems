/*
Name : Pracheti Bhale
Roll No : MT2023155

15) Write a program to display the environment variable of the user (use environ).
*/

#include<stdio.h>
#include<unistd.h>

/*
To set a global ENV  : $ export NAME=Value
To set a local ENV : $ NAME=Value

These variables are set and configured in ~/.bashrc, ~/.bash_profile, ~/.bash_login, ~/.profile files according to the requirement. These variables can be accessed by a particular user and persist through power offs. 

Steps : $ sudo vi ~/.bashrc, export NAME=Value, $ source ~/.bashrc 
*/

int main(int argc, char *argv[], char * envp[]){
	int i;
    for (i = 0; envp[i] != NULL; i++)
        printf("\n%s", envp[i]);
    getchar();
	return 0;
}
