#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <time.h>

char PATH[256];
static pid_t mole = 0;


static void signal_handler(int signal);
void create_mole_process();

int main(/*int argc, char **argv*/)
{
    pid_t pid;
    pid_t session; // daemon
    struct rlimit rlimit;
    int dev_null; // file desctiptor
    int change_check; 

    pid = fork();
    if(pid == -1){
        printf("Can't create a process.");
        exit(EXIT_FAILURE);
    }
    /* child */
    if(pid == 0){
        printf("Child working\n");
        printf("PID: %d\n", getpid() );
        mole = 0;
        umask(0);

        session = setsid();
        if(session == -1){
            fprintf(stderr, "Can't create a new session.");
            exit(EXIT_FAILURE);
        }
        
        change_check = chdir("/");
        if(change_check == -1){
            fprintf(stderr, "Can't changed directory!");
            exit(EXIT_FAILURE);
        }
       
        getrlimit(RLIMIT_NOFILE, &rlimit);
        if (rlimit.rlim_max == RLIM_INFINITY)
            rlimit.rlim_max = 1024;
        for (unsigned int i = 0; i < rlimit.rlim_max; i++)
            close(i);
      
        dev_null=open("/dev/null", O_WRONLY);
        dup2(dev_null, STDIN_FILENO);
        dup2(dev_null, STDOUT_FILENO);
        dup2(dev_null, STDERR_FILENO);
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        
        
        if(signal(SIGTERM, signal_handler) == SIG_ERR ){
                fprintf(stderr, "Can't handle signal");
        }
        if(signal(SIGUSR1, signal_handler) == SIG_ERR ){
                fprintf(stderr, "Can't handle signal");
        }
        if(signal(SIGUSR2, signal_handler) == SIG_ERR ){
                fprintf(stderr, "Can't handle signal");
                
        }
        
        do{
            sleep(1);
        }while(1);

    }
    /* parent */
    else{
        fprintf(stderr, "Termintaing parent\n");
        exit(EXIT_SUCCESS);
    }

    return 0;

}

static void signal_handler(int sig)
{
    signal(sig, signal_handler);
    
    if (sig == SIGTERM){
        if(mole != 0)
        {
            kill(mole, SIGKILL);  
        }
        kill(getpid(), SIGKILL);
        exit(EXIT_SUCCESS);
    }
    else if(sig == SIGUSR1 || sig == SIGUSR2){
        if(mole != 0)
            kill(mole, SIGKILL);

        create_mole_process();
    }
    else
    {
        fprintf(stderr,"unknnown sig\n");
    }
    
}

 
void create_mole_process()
{
    char* newArgv[3];
    char* mole_num_str = NULL;
    char PATH[1024];
    pid_t new_mole;
    /* setup new argv to pass to mole */
   
    new_mole = fork();
    if(new_mole == 0){

        srand(time(NULL));
        int rand_num = (rand() & 1);
        if(rand_num == 0)
            sprintf(mole_num_str, "%s", "mole1");
        else
            sprintf(mole_num_str, "%s", "mole2");
        newArgv[0] = mole_num_str;
        getcwd(PATH, 1024);
        newArgv[1] = PATH; 
        strcat(PATH, "/mole");
        newArgv[2] = NULL;

        if(execv(PATH, newArgv) == -1){
            perror ("failed to locate mole executable.\n");
        }
      
    }
    

}
