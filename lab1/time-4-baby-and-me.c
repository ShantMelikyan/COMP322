#include<stdio.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

void report(pid_t pid, pid_t child, int status);

int main(/*int agrc, char** agrv*/)
{
    printf("hello world");
    time_t start, stop; 
    pid_t pid;
    int status;

    start = time(NULL); 
    printf("\nSTART: %ld\n", start);
    pid = fork(); // create pid process

    if (pid == -1) {               // checking if the fork was made 
        printf("cant create a fork :( ");
        exit(0);
    }


    if (pid == 0){    
   
        report(pid, 0, 0);   
        return 0;
    }
    else{
        pid_t child;
        child = waitpid(pid, &status, 0); // this way, the parent waits for all the pid processes 
        report(pid, child, status);   
    }
    
    stop = time(NULL); 
    printf("\nSTOP: %ld\n", stop);
    
    return 0;
}

void report(pid_t pid, pid_t child, int status)
{
    
    if (pid == 0)
        printf("\nPPID: %d, PID: %d, CPID: %d, RETVAL: %d\n", (int) getppid(), (int) getpid(), child, status);
    else
         printf("\nPPID: %d, PID: %d" , (int) getppid(), (int) getpid() );


}