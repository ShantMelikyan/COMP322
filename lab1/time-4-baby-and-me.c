#include<stdio.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

void report(int child);

int main(/*int agrc, char** agrv*/)
{
    printf("hello world");
    time_t start, stop; 
    pid_t child;
    int status;

    start = time(NULL); 
    printf("\nSTART: %ld\n", start);
    child = fork(); // create child process

    if (child == -1) {               // checking if the fork was made 
        perror("fork");
       exit(0);
    }

    report(child); 
     
    if (child == 0){          /* Code executed by child */
        report(child);   
        return 0;
    }
    
       
    while ((child = waitpid(-1, &status, 0)) > 0); // this way, the father waits for all the child processes 

    stop = time(NULL); 
    printf("\nSTOP: %ld\n", stop);
    
    return 0;
}

void report(int child)
{
    
    if (child == 0)
        printf("\nPPID: %ld, PID: %ld, RETVAL: %d\n", (long) getppid(), (long) getpid(), child);
    else
         printf("\nPPID: %ld, PID: %ld" , (long) getppid(), (long) getpid() );


}