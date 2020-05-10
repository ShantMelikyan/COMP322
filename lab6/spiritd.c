#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <signal.h>

static int exit_flag = 0;

void signal_handler(int signal);
/*
void new_mole()
{


}
*/

int main(/*int argc, char **argv*/)
{
    
    pid_t pid;
    umask(0);
    pid = fork();
    struct rlimit rlimit;
    int dev_null;

    if(pid == -1){
        printf("Can't create a process.");
        exit(EXIT_FAILURE);
    }
    /* child */
    if(pid == 0){
        printf("Child working\n");
        if(signal(SIGTERM, signal_handler) == SIG_ERR )
            fprintf(stderr, "Can't handle signal");
        pid_t session;
        session = setsid();
        printf("PID: %d\n", getpid() );
        if(session == -1){
            printf("Can't create a new session.");
            exit(EXIT_FAILURE);
        }
        else
            printf("session created\n");

        int change_check; 
        change_check = chdir("/");

        if(change_check == -1){
            printf("Can't changed directory!");
            exit(EXIT_FAILURE);
        }
        
        getrlimit(RLIMIT_NOFILE, &rlimit);
        if (rlimit.rlim_max == RLIM_INFINITY)
            rlimit.rlim_max = 1024;
        for (unsigned int i = 0; i < rlimit.rlim_max; i++)
            close(i);
        dev_null=open("/dev/null", O_RDONLY);
        dup2(dev_null,0);
        dup2(dev_null,1);
        dup2(dev_null,2);
        do{
            sleep(1);
        }while (exit_flag == 0);
    }
    /* parent */
    else{
        printf("Termintaing parent\n");
        exit(EXIT_SUCCESS);
    }

    return 0;

}

void signal_handler(int sig)
{
    signal(SIGTERM, signal_handler);
    if (sig == SIGTERM){
        exit_flag = 1;
    }

    fprintf(stderr, "signal catched!\n Killing daemon!\n");

}