#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <errno.h>
#include <sys/stat.h>

char PATH[1024];
pid_t mole = 0;


void signal_handler(int signal);
void create_mole_process();

int main(/*int argc, char **argv*/)
{
    pid_t pid;
    pid_t session; 
    struct rlimit rlimit;
    int dev_null; 
    int change_check; 
    

    getcwd(PATH, 1024 );
	strcat(PATH, "/mole");

    pid = fork();
    if(pid == -1){
        printf("Can't create a process.");
        exit(EXIT_FAILURE);
    }
    /* child */
    if(pid == 0){
        printf("Child working\n");
        printf("PID: %d\n", getpid() );
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
      
        dev_null = open("/dev/null", O_RDWR);
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
            pause();
        }while(1);

    }
    else{
        fprintf(stderr, "Termintaing parent\n");
        exit(EXIT_SUCCESS);
    }

    return 0;

}

void signal_handler(int sig)
{
    
    if (sig == SIGTERM){
        if(mole != 0){
            kill(mole, SIGKILL);  
        }
        kill(getpid(), SIGKILL);
    }
    else if(sig == SIGUSR1 || sig == SIGUSR2){
        signal(sig, signal_handler);
        if(mole != 0)
            kill(mole, SIGKILL);

        create_mole_process();
    }
    else{
        fprintf(stderr,"unknnown sig\n");
    }
    
}

void create_mole_process()
{
    char *newArgv[3];  // create arguments list for execv
	char* mole_num_str;

	mole = fork();

	if(mole == 0)  {

		srand(time(NULL));
        int rand_num = (rand() & 1);
		if(rand_num == 0)
            mole_num_str = "mole1";
        else
            mole_num_str = "mole2";
        
        newArgv[0] = PATH;	
	    newArgv[1] = mole_num_str;		
	    newArgv[2] = NULL;
        
        execv(PATH, newArgv);
	}
}
