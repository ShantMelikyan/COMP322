#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>
/*
void new_mole()
{


}

void signalHandler()
{


}
*/
int main(int argc, char **argv)
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
        pid_t session;
        session = setsid();

        if(session == -1){
            printf("Can't create a new session.");
            exit(EXIT_FAILURE);
        }

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
    }
    /* parent */
    else{
        exit(EXIT_SUCCESS);
    }

    return 0;
}