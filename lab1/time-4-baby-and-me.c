#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/times.h>
#include <inttypes.h>

void report(pid_t child, int status);

int main(/*int agrc, char** agrv*/)
{

    pid_t pid;
    int status;
    
    time_t start;
    time(&start);
    printf("\nSTART: %ld\n", start);

    sleep(1); // sleep for 1 sec 
    for(int i = 0, k = 0; i < 99999999; i++) // making cpu busy
        k=k*i;
   
    pid = fork(); // create pid process
    struct tms st_cpu;  
    times(&st_cpu);  

    long k = 0;

    for(int i = 0, k = 0; i < 99999999; i++)
        k=k*i;
    sleep(2);
    
    if (pid == -1) {               // checking if the fork was made 
        printf("cant create a fork :( ");
        exit(0);
    }
   

    if (pid == 0){    
        
        report(-1, -1);   
        exit(EXIT_SUCCESS);
    }
    else{
        
        pid_t child;
        child = waitpid(pid, &status, WUNTRACED); // the parent waits for all the child processes 
        times(&st_cpu);

        report(child, status);   
    }
   
    

    printf("USER: %d, SYS: %d\nCUSER: %d, CSYS: %d\n",  (int)(st_cpu.tms_utime ),
                                                        (int)(st_cpu.tms_stime ), 
                                                        (int)(st_cpu.tms_cutime ),  
                                                        (int)(st_cpu.tms_cstime ) );
    time(&start);
    printf("\nSTOP: %ld\n", start);

    printf("%ld", k);
    return 0;
}

void report(pid_t child, int status)
{

    if (child == -1 && status == -1)
        printf("\nPPID: %d, PID: %d" , (int) getppid(), (int) getpid() );
    else
        printf("\nPPID: %d, PID: %d, CPID: %d, RETVAL: %d\n", (int) getppid(), (int) getpid(), child, status);

}