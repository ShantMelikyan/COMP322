#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/times.h>

void report(pid_t child, int status);

int main()
{
    pid_t pid;
    int status;
    time_t start;

    time(&start);
    pid = fork(); // forking programm and creating pid process
    struct tms st_cpu;

    if (pid == -1) {               // checking if the fork was made 
        printf("Can't create a fork :( ");
        exit(0);
    }
    if (pid == 0){ 
        printf("START: %d",(int) start);  
        report(-1, -1);   
        exit(EXIT_SUCCESS);
    }
    else{
        pid_t child;
        child = waitpid(pid, &status, WUNTRACED); // the parent waits for all the child processes 
        report(child, status);   
        times(&st_cpu);
        printf("USER: %d, SYS: %d\nCUSER: %d, CSYS: %d\n",  (int)(st_cpu.tms_utime ), (int)(st_cpu.tms_stime ), (int)(st_cpu.tms_cutime ), (int)(st_cpu.tms_cstime ) );

    }
   
    time(&start);
    printf("STOP: %ld\n", start);

    return 0;

}

void report(pid_t child, int status)
{

    if (child == -1 && status == -1)
        printf("\nPPID: %d, PID: %d" , (int) getppid(), (int) getpid() );
    else
        printf("\nPPID: %d, PID: %d, CPID: %d, RETVAL: %d\n", (int) getppid(), (int) getpid(), child, status);

}